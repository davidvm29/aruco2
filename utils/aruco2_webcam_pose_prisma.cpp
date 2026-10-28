/**
 * @file aruco2_webcam_pose_prisma.cpp
 * @brief Live PRISMarker detection and pose estimation from camera, video or IP stream.
 *
 * Based on the validated webcam_pose_fmarker utility. No detection algorithm
 * is implemented here; the public PrismaDetector API is used.
 */
#include <algorithm>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include "opencv2/objdetect/aruco2.hpp"
namespace {
struct ReprojectionStats
{
    bool valid = false;
    int points = 0;
    double mean = 0.0;
    double rms = 0.0;
    double max = 0.0;
};
std::string getOption(
    int argc,
    char** argv,
    const std::string& name,
    const std::string& defaultValue
)
{
    for (int index = 1; index + 1 < argc; ++index)
    {
        if (argv[index] == name)
            return argv[index + 1];
    }
    return defaultValue;
}
bool getBoolOption(
    int argc,
    char** argv,
    const std::string& name,
    bool defaultValue
)
{
    std::string value =
        getOption(
            argc,
            argv,
            name,
            defaultValue ? "true" : "false"
        );
    std::transform(
        value.begin(),
        value.end(),
        value.begin(),
        [](unsigned char c)
        {
            return static_cast<char>(
                std::tolower(c)
            );
        }
    );
    if (
        value == "true" ||
        value == "1" ||
        value == "yes" ||
        value == "on"
    )
    {
        return true;
    }
    if (
        value == "false" ||
        value == "0" ||
        value == "no" ||
        value == "off"
    )
    {
        return false;
    }
    throw std::runtime_error(
        name + " debe ser true o false"
    );
}
bool isNumber(
    const std::string& source
)
{
    return
        !source.empty() &&
        std::all_of(
            source.begin(),
            source.end(),
            [](unsigned char character)
            {
                return
                    std::isdigit(character) != 0;
            }
        );
}
bool loadCamera(
    const std::string& path,
    cv::Mat& cameraMatrix,
    cv::Mat& distCoeffs,
    cv::Size& calibrationSize
)
{
    cv::FileStorage storage(
        path,
        cv::FileStorage::READ
    );
    if (!storage.isOpened())
        return false;
    storage["camera_matrix"] >>
        cameraMatrix;
    storage["distortion_coefficients"] >>
        distCoeffs;
    if (distCoeffs.empty())
        storage["distortion_coeffs"] >> distCoeffs;
    if (cameraMatrix.empty())
    {
        storage["Camera_Matrix"] >>
            cameraMatrix;
    }
    if (distCoeffs.empty())
    {
        storage["Distortion_Coefficients"] >>
            distCoeffs;
    }
    int width = 0;
    int height = 0;
    storage["image_width"] >>
        width;
    storage["image_height"] >>
        height;
    calibrationSize =
        cv::Size(
            width,
            height
        );
    if (cameraMatrix.empty())
        return false;
    if (distCoeffs.empty())
        distCoeffs = cv::Mat::zeros(1, 5, CV_64F);
    if (cameraMatrix.rows != 3 || cameraMatrix.cols != 3)
        return false;
    cameraMatrix.convertTo(
        cameraMatrix,
        CV_64F
    );
    distCoeffs.convertTo(
        distCoeffs,
        CV_64F
    );
    return true;
}
cv::Mat scaleCamera(
    const cv::Mat& cameraMatrix,
    const cv::Size& calibrationSize,
    const cv::Size& frameSize
)
{
    cv::Mat scaled =
        cameraMatrix.clone();
    if (
        calibrationSize.width <= 0 ||
        calibrationSize.height <= 0 ||
        calibrationSize == frameSize
    )
    {
        return scaled;
    }
    const double scaleX =
        static_cast<double>(
            frameSize.width
        ) /
        calibrationSize.width;
    const double scaleY =
        static_cast<double>(
            frameSize.height
        ) /
        calibrationSize.height;
    scaled.at<double>(0, 0) *=
        scaleX;
    scaled.at<double>(1, 1) *=
        scaleY;
    scaled.at<double>(0, 2) *=
        scaleX;
    scaled.at<double>(1, 2) *=
        scaleY;
    return scaled;
}
bool openVideo(
    cv::VideoCapture& capture,
    const std::string& source
)
{
    if (isNumber(source))
    {
        return capture.open(
            std::stoi(source)
        );
    }
    return
        capture.open(
            source,
            cv::CAP_FFMPEG
        ) ||
        capture.open(
            source
        );
}
cv::Mat toBgr(
    const cv::Mat& image
)
{
    cv::Mat result;
    if (image.channels() == 1)
    {
        cv::cvtColor(
            image,
            result,
            cv::COLOR_GRAY2BGR
        );
    }
    else if (image.channels() == 4)
    {
        cv::cvtColor(
            image,
            result,
            cv::COLOR_BGRA2BGR
        );
    }
    else
    {
        result =
            image.clone();
    }
    return result;
}
cv::Mat fitToScreen(
    const cv::Mat& image,
    int maxWidth = 1280,
    int maxHeight = 720
)
{
    if (image.empty())
        return image;
    const double scaleX =
        static_cast<double>(maxWidth) /
        static_cast<double>(image.cols);
    const double scaleY =
        static_cast<double>(maxHeight) /
        static_cast<double>(image.rows);
    const double scale =
        std::min(
            1.0,
            std::min(scaleX, scaleY)
        );
    if (scale >= 1.0)
        return image;
    cv::Mat resized;
    cv::resize(
        image,
        resized,
        cv::Size(),
        scale,
        scale,
        cv::INTER_AREA
    );
    return resized;
}
std::string makeOverlayLabel(
    const std::string& methodName,
    const std::vector<cv::aruco2::PrismaMarker>& markers
)
{
    std::ostringstream text;
    text << methodName;
    if (markers.empty())
        return text.str();
    if (markers.size() == 1)
    {
        text
            << " | PRISMarker ID: "
            << markers.front().id;
        return text.str();
    }
    text << " | PRISMarker IDs: ";
    for (std::size_t index = 0; index < markers.size(); ++index)
    {
        if (index != 0)
            text << ", ";
        text << markers[index].id;
    }
    return text.str();
}
bool points2DToNx2(
    const cv::Mat& source,
    cv::Mat& result
)
{
    if (source.empty())
        return false;
    cv::Mat converted;
    source.convertTo(
        converted,
        CV_64F
    );
    if (converted.channels() == 2)
    {
        result =
            converted
                .reshape(
                    1,
                    static_cast<int>(
                        converted.total()
                    )
                )
                .clone();
    }
    else if (converted.channels() == 1)
    {
        if (converted.cols == 2)
        {
            result =
                converted.clone();
        }
        else if (converted.rows == 2)
        {
            result =
                converted.t();
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return
        result.rows > 0 &&
        result.cols == 2;
}
bool vector3ToRow64(
    const cv::Mat& source,
    cv::Mat& row
)
{
    if (
        source.empty() ||
        source.total() != 3
    )
    {
        return false;
    }
    cv::Mat converted;
    source.convertTo(
        converted,
        CV_64F
    );
    row =
        converted
            .reshape(
                1,
                1
            )
            .clone();
    return
        row.rows == 1 &&
        row.cols == 3;
}
ReprojectionStats computeReprojectionStats(
    const cv::Mat& objectPoints,
    const cv::Mat& imagePoints,
    const cv::Mat& rotationVector,
    const cv::Mat& translationVector,
    const cv::Mat& cameraMatrix,
    const cv::Mat& distCoeffs
)
{
    ReprojectionStats stats;
    cv::Mat projected;
    try
    {
        cv::projectPoints(
            objectPoints,
            rotationVector,
            translationVector,
            cameraMatrix,
            distCoeffs,
            projected
        );
    }
    catch (const cv::Exception&)
    {
        return stats;
    }
    cv::Mat observedNx2;
    cv::Mat projectedNx2;
    if (
        !points2DToNx2(
            imagePoints,
            observedNx2
        ) ||
        !points2DToNx2(
            projected,
            projectedNx2
        )
    )
    {
        return stats;
    }
    if (
        observedNx2.rows != projectedNx2.rows ||
        observedNx2.rows == 0
    )
    {
        return stats;
    }
    double sum = 0.0;
    double sumSquared = 0.0;
    double maxError = 0.0;
    for (
        int i = 0;
        i < observedNx2.rows;
        ++i
    )
    {
        const double dx =
            observedNx2.at<double>(i, 0) -
            projectedNx2.at<double>(i, 0);
        const double dy =
            observedNx2.at<double>(i, 1) -
            projectedNx2.at<double>(i, 1);
        const double error =
            std::sqrt(
                dx * dx +
                dy * dy
            );
        sum += error;
        sumSquared +=
            error * error;
        maxError =
            std::max(
                maxError,
                error
            );
    }
    stats.valid = true;
    stats.points = observedNx2.rows;
    stats.mean =
        sum /
        static_cast<double>(
            stats.points
        );
    stats.rms =
        std::sqrt(
            sumSquared /
            static_cast<double>(
                stats.points
            )
        );
    stats.max =
        maxError;
    return stats;
}
enum class PoseAxisStatus
{
    SAFE,
    POSE_INVALID,
    AXIS_UNSAFE
};
void printPoseDiagnostic(
    const char* prefix,
    const std::string& reason,
    const ReprojectionStats& reprojection,
    const cv::Mat& rotationVector,
    const cv::Mat& translationVector,
    const std::vector<cv::Point2f>& axis2D
)
{
    cv::Mat rvecRow;
    cv::Mat tvecRow;
    const bool haveRvec =
        vector3ToRow64(
            rotationVector,
            rvecRow
        );
    const bool haveTvec =
        vector3ToRow64(
            translationVector,
            tvecRow
        );
    std::cerr
        << std::fixed
        << std::setprecision(4)
        << "\n[" << prefix << "] "
        << reason
        << '\n';
    if (reprojection.valid)
    {
        std::cerr
            << "  puntos      : "
            << reprojection.points
            << '\n'
            << "  reproy mean : "
            << reprojection.mean
            << " px\n"
            << "  reproy RMS  : "
            << reprojection.rms
            << " px\n"
            << "  reproy max  : "
            << reprojection.max
            << " px\n";
    }
    if (haveTvec)
    {
        std::cerr
            << "  tvec        : ["
            << tvecRow.at<double>(0, 0)
            << ", "
            << tvecRow.at<double>(0, 1)
            << ", "
            << tvecRow.at<double>(0, 2)
            << "]\n";
    }
    if (haveRvec)
    {
        std::cerr
            << "  rvec        : ["
            << rvecRow.at<double>(0, 0)
            << ", "
            << rvecRow.at<double>(0, 1)
            << ", "
            << rvecRow.at<double>(0, 2)
            << "]\n";
    }
    if (axis2D.size() == 4)
    {
        const cv::Point2f& origin = axis2D[0];
        std::cerr
            << "  eje X       : "
            << cv::norm(axis2D[1] - origin)
            << " px\n"
            << "  eje Y       : "
            << cv::norm(axis2D[2] - origin)
            << " px\n"
            << "  eje Z       : "
            << cv::norm(axis2D[3] - origin)
            << " px\n";
    }
    std::cerr << std::endl;
}


PoseAxisStatus checkPoseAndAxis(
    const cv::Mat& image,
    const cv::Mat& objectPoints,
    const cv::Mat& imagePoints,
    const cv::Mat& rotationVector,
    const cv::Mat& translationVector,
    const cv::Mat& cameraMatrix,
    const cv::Mat& distCoeffs,
    float axisLength
)
{
    if (
        image.empty() ||
        rotationVector.empty() ||
        translationVector.empty() ||
        rotationVector.total() != 3 ||
        translationVector.total() != 3 ||
        !cv::checkRange(rotationVector) ||
        !cv::checkRange(translationVector)
    )
    {
        return PoseAxisStatus::POSE_INVALID;
    }
    cv::Mat rotation64;
    cv::Mat translation64;
    rotationVector.convertTo(rotation64, CV_64F);
    translationVector.convertTo(translation64, CV_64F);
    cv::Mat translationRow;
    if (!vector3ToRow64(translation64, translationRow))
        return PoseAxisStatus::POSE_INVALID;
    const double tx = translationRow.at<double>(0, 0);
    const double ty = translationRow.at<double>(0, 1);
    const double tz = translationRow.at<double>(0, 2);
    const ReprojectionStats reprojection =
        computeReprojectionStats(
            objectPoints,
            imagePoints,
            rotation64,
            translation64,
            cameraMatrix,
            distCoeffs
        );
    if (!std::isfinite(tx) ||
        !std::isfinite(ty) ||
        !std::isfinite(tz) ||
        tz <= 1e-6)
    {
        printPoseDiagnostic(
            "POSE INVALIDA",
            "tvec no finito o profundidad <= 0",
            reprojection,
            rotation64,
            translation64,
            {}
        );
        return PoseAxisStatus::POSE_INVALID;
    }
    const std::vector<cv::Point3f> axis3D =
    {
        cv::Point3f(0.f, 0.f, 0.f),
        cv::Point3f(axisLength, 0.f, 0.f),
        cv::Point3f(0.f, axisLength, 0.f),
        cv::Point3f(0.f, 0.f, axisLength)
    };
    cv::Mat rotationMatrix;
    cv::Rodrigues(rotation64, rotationMatrix);
    const double minAxisDepth =
        std::max(1e-6, std::abs(tz) * 0.01);
    for (const cv::Point3f& point : axis3D)
    {
        const double cameraZ =
            rotationMatrix.at<double>(2, 0) * point.x +
            rotationMatrix.at<double>(2, 1) * point.y +
            rotationMatrix.at<double>(2, 2) * point.z +
            tz;
        if (!std::isfinite(cameraZ) || cameraZ <= minAxisDepth)
        {
            static int omittedDepthCount = 0;
            if ((omittedDepthCount++ % 30) == 0)
            {
                printPoseDiagnostic(
                    "AXIS OMITIDO - POSE CONSERVADA",
                    "un extremo del eje original alcanza/cruza el plano de camara",
                    reprojection,
                    rotation64,
                    translation64,
                    {}
                );
            }
            return PoseAxisStatus::AXIS_UNSAFE;
        }
    }
    std::vector<cv::Point2f> axis2D;
    try
    {
        cv::projectPoints(
            axis3D,
            rotation64,
            translation64,
            cameraMatrix,
            distCoeffs,
            axis2D
        );
    }
    catch (const cv::Exception&)
    {
        return PoseAxisStatus::AXIS_UNSAFE;
    }
    if (axis2D.size() != 4)
        return PoseAxisStatus::AXIS_UNSAFE;
    const double maxCoordinateX =
        static_cast<double>(image.cols) * 100.0;
    const double maxCoordinateY =
        static_cast<double>(image.rows) * 100.0;
    for (const cv::Point2f& point : axis2D)
    {
        if (!std::isfinite(point.x) ||
            !std::isfinite(point.y) ||
            std::abs(static_cast<double>(point.x)) > maxCoordinateX ||
            std::abs(static_cast<double>(point.y)) > maxCoordinateY)
        {
            static int omittedProjectionCount = 0;
            if ((omittedProjectionCount++ % 30) == 0)
            {
                printPoseDiagnostic(
                    "AXIS OMITIDO - POSE CONSERVADA",
                    "proyeccion del eje original fuera de rango seguro",
                    reprojection,
                    rotation64,
                    translation64,
                    axis2D
                );
            }
            return PoseAxisStatus::AXIS_UNSAFE;
        }
    }
    const cv::Point2f& origin = axis2D[0];
    const double maxAxisLength =
        static_cast<double>(std::max(image.cols, image.rows)) * 100.0;
    if (cv::norm(axis2D[1] - origin) > maxAxisLength ||
        cv::norm(axis2D[2] - origin) > maxAxisLength ||
        cv::norm(axis2D[3] - origin) > maxAxisLength)
    {
        return PoseAxisStatus::AXIS_UNSAFE;
    }
    return PoseAxisStatus::SAFE;
}
bool drawPose(
    cv::Mat& image,
    const cv::aruco2::PrismaMarker& marker,
    const cv::Mat& cameraMatrix,
    const cv::Mat& distCoeffs,
    float markerSize,
    bool show
)
{
    cv::Mat objectPoints;
    cv::Mat imagePoints;
    cv::aruco2::getSolvePnpPoints(
        marker,
        objectPoints,
        imagePoints,
        markerSize
    );
    if (objectPoints.total() < 4 ||
        objectPoints.total() != imagePoints.total())
    {
        return false;
    }
    cv::Mat rotationVector;
    cv::Mat translationVector;
    const bool solved =
        cv::solvePnP(
            objectPoints,
            imagePoints,
            cameraMatrix,
            distCoeffs,
            rotationVector,
            translationVector,
            false,
            cv::SOLVEPNP_ITERATIVE
        );
    if (!solved ||
        rotationVector.empty() ||
        translationVector.empty() ||
        !cv::checkRange(rotationVector) ||
        !cv::checkRange(translationVector))
    {
        return false;
    }
    const ReprojectionStats reprojection =
        computeReprojectionStats(
            objectPoints,
            imagePoints,
            rotationVector,
            translationVector,
            cameraMatrix,
            distCoeffs
        );
    cv::Mat tvecRow;
    const bool haveTvec =
        vector3ToRow64(
            translationVector,
            tvecRow
        );
    if (!haveTvec ||
        !std::isfinite(tvecRow.at<double>(0, 2)) ||
        tvecRow.at<double>(0, 2) <= 1e-9)
    {
        printPoseDiagnostic(
            "POSE RECHAZADA",
            "tvec no finito o profundidad <= 0",
            reprojection,
            rotationVector,
            translationVector,
            {}
        );
        return false;
    }
    const double warningRms =
        std::max(
            3.0,
            0.005 * static_cast<double>(
                std::max(image.cols, image.rows)
            )
        );
    if (!reprojection.valid ||
        !std::isfinite(reprojection.rms) ||
        reprojection.rms > warningRms)
    {
        static int highRmsWarningCount = 0;
        if ((highRmsWarningCount++ % 30) == 0)
        {
            printPoseDiagnostic(
                "AVISO POSE - RMS ALTO",
                "pose conservada para visualizacion; revisar calibracion/reproyeccion",
                reprojection,
                rotationVector,
                translationVector,
                {}
            );
        }
    }
    if (!show)
        return true;
    const double tz =
        tvecRow.at<double>(0, 2);
    const float axisLength =
        std::max(
            1e-6f,
            std::min(
                markerSize * 0.5f,
                static_cast<float>(tz * 0.25)
            )
        );
    const PoseAxisStatus status =
        checkPoseAndAxis(
            image,
            objectPoints,
            imagePoints,
            rotationVector,
            translationVector,
            cameraMatrix,
            distCoeffs,
            axisLength
        );
    if (status == PoseAxisStatus::POSE_INVALID)
        return false;
    // Si aun asi la proyeccion no es segura, conservamos la pose y no dibujamos.
    if (status == PoseAxisStatus::AXIS_UNSAFE)
        return true;
    cv::aruco2::drawAxis(
        image,
        cameraMatrix,
        distCoeffs,
        rotationVector,
        translationVector,
        axisLength
    );
    return true;
}
void help(
    const char* program,
    const std::string& methodName
)
{
    std::cerr
        << "Uso:\n"
        << "  " << program
        << " <diccionario_predefinido> <camera.yml>"
        << " [camera_id|video|url]"
        << " [-ms markerSize]"
        << " [-every N]"
        << " [-show true|false]\n\n"
        << "Puntos de pose:\n"
        << "  " << methodName << "\n\n"
        << "Pose/ejes:\n"
        << "  getSolvePnpPoints -> solvePnP(ITERATIVE)"
        << " -> drawAxis(eje adaptativo)\n"
        << "  La longitud visual disminuye al acercarse a la camara.\n\n"
        << "Opciones:\n"
        << "  -ms      Tamano real del marcador\n"
        << "  -every   Detectar cada N frames\n"
        << "  -show    Mostrar ventana/dibujos (true por defecto)\n"
        << "           La vista se ajusta automaticamente a 1280x720 como maximo.\n\n"
        << "Diccionarios disponibles:\n";
    for (
        const cv::String& name :
        cv::aruco2::getPrismaNames()
    )
    {
        std::cerr
            << "  "
            << name
            << '\n';
    }
    std::cerr
        << "\nEjemplo webcam:\n"
        << "  " << program
        << " PRISMA_D3_ARUCO_MIP_36H12"
        << " yml/camera.yml 0"
        << " -ms 0.20"
        << " -every 1"
        << " -show true\n"
        << "\nEjemplo video/url:\n"
        << "  " << program
        << " PRISMA_D3_ARUCO_MIP_36H12"
        << " yml/camera.yml detection.mp4"
        << " -ms 1.0"
        << " -every 1"
        << " -show true\n";
}
} // namespace
int main(
    int argc,
    char** argv
)
{
    const std::string methodName =
        "PRISMarker";
    try
    {
        if (argc < 3)
        {
            help(argv[0], methodName);
            return -1;
        }
        const std::string dictionaryName =
            argv[1];
        const cv::aruco2::PrismaDict dictionary =
            cv::aruco2::getPrismaType(
                dictionaryName
            );
        const std::string calibrationPath =
            argv[2];
        std::string source =
            "0";
        if (
            argc >= 4 &&
            std::string(argv[3]).rfind(
                "-",
                0
            ) != 0
        )
        {
            source =
                argv[3];
        }
        const float markerSize =
            std::stof(
                getOption(
                    argc,
                    argv,
                    "-ms",
                    "1.0"
                )
            );
        const int detectEvery =
            std::max(
                1,
                std::stoi(
                    getOption(
                        argc,
                        argv,
                        "-every",
                        "1"
                    )
                )
            );
        const bool show =
            getBoolOption(
                argc,
                argv,
                "-show",
                true
            );
        if (markerSize <= 0.f)
        {
            throw std::runtime_error(
                "-ms debe ser mayor que cero"
            );
        }
        cv::Mat originalCameraMatrix;
        cv::Mat distCoeffs;
        cv::Size calibrationSize;
        if (
            !loadCamera(
                calibrationPath,
                originalCameraMatrix,
                distCoeffs,
                calibrationSize
            )
        )
        {
            throw std::runtime_error(
                "No se pudo cargar la calibracion: " +
                calibrationPath
            );
        }
        cv::VideoCapture capture;
        if (
            !openVideo(
                capture,
                source
            )
        )
        {
            throw std::runtime_error(
                "No se pudo abrir la fuente: " +
                source
            );
        }
        capture.set(
            cv::CAP_PROP_BUFFERSIZE,
            1
        );
        const std::string windowName =
            "Aruco2 PRISMarker pose - " + methodName;
        if (show)
        {
            cv::namedWindow(
                windowName,
                cv::WINDOW_NORMAL
            );
        }
        std::vector<
            cv::aruco2::PrismaMarker
        > markers;
        cv::aruco2::PrismaDetector detector(
            dictionary
        );
        cv::Mat cameraMatrix;
        cv::Size currentFrameSize;
        int frameNumber =
            0;
        for (;;)
        {
            cv::Mat frame;
            const bool readOk =
                capture.read(
                    frame
                );
            if (
                !readOk ||
                frame.empty()
            )
            {
                break;
            }
            if (
                frame.size() !=
                currentFrameSize
            )
            {
                currentFrameSize =
                    frame.size();
                const double frameAspect =
                    static_cast<double>(
                        currentFrameSize.width
                    ) /
                    static_cast<double>(
                        currentFrameSize.height
                    );
                const double calibrationAspect =
                    calibrationSize.height > 0 ?
                    static_cast<double>(calibrationSize.width) /
                    static_cast<double>(calibrationSize.height) : 0.0;
                std::cout
                    << "\n================ CAMARA ================\n"
                    << "Stream      : "
                    << currentFrameSize.width
                    << "x"
                    << currentFrameSize.height
                    << '\n'
                    << "Calibracion : "
                    << calibrationSize.width
                    << "x"
                    << calibrationSize.height
                    << '\n'
                    << "Aspect stream      : "
                    << frameAspect
                    << '\n'
                    << "Aspect calibracion : "
                    << calibrationAspect
                    << '\n'
                    << "========================================\n"
                    << std::endl;
                cameraMatrix =
                    scaleCamera(
                        originalCameraMatrix,
                        calibrationSize,
                        currentFrameSize
                    );
            }
            const bool runDetection =
                frameNumber %
                detectEvery == 0;
            if (runDetection)
            {
                markers =
                    detector.detect(
                        frame,
                        true
                    );
            }
            ++frameNumber;
            cv::Mat output;
            if (show)
            {
                output =
                    toBgr(
                        frame
                    );
                cv::aruco2::drawPrisma(
                    output,
                    markers,
                    cv::Scalar(0, 255, 0),
                    true
                );
            }
            for (
                const cv::aruco2::PrismaMarker&
                    marker :
                markers
            )
            {
                drawPose(
                    output,
                    marker,
                    cameraMatrix,
                    distCoeffs,
                    markerSize,
                    show
                );
            }
            if (show)
            {
                const std::string overlayLabel =
                    makeOverlayLabel(
                        methodName,
                        markers
                    );
                cv::putText(
                    output,
                    overlayLabel,
                    cv::Point(
                        20,
                        40
                    ),
                    cv::FONT_HERSHEY_SIMPLEX,
                    1.0,
                    cv::Scalar(
                        0,
                        255,
                        255
                    ),
                    2,
                    cv::LINE_AA
                );
                const cv::Mat display =
                    fitToScreen(
                        output
                    );
                cv::imshow(
                    windowName,
                    display
                );
                const int key =
                    cv::waitKey(1);
                if (
                    key == 27 ||
                    key == 'q' ||
                    key == 'Q'
                )
                {
                    break;
                }
            }
        }
        if (show)
        {
            cv::destroyAllWindows();
        }
    }
    catch (const cv::Exception& error)
    {
        std::cerr
            << "Error de OpenCV: "
            << error.what()
            << '\n';
        return -1;
    }
    catch (const std::exception& error)
    {
        std::cerr
            << "Error: "
            << error.what()
            << '\n';
        return -1;
    }
    return 0;
}