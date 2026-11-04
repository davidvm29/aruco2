/**
 * @file aruco2_detect_prisma.cpp
 * @brief Detect PRISMarkers in local images, image folders or video files.
 *
 * Usage:
 *   ./aruco2_detect_prisma <image|folder|video> [options]
 *
 * Options:
 *   -dict=<name>  PRISMarker dictionary (default: PRISMA_D3)
 *   -aux=<name>   Auxiliary dictionary (default: DICT_ARUCO_MIP_36h12)
 *   -calib=<file> Camera calibration YAML/XML (enables adaptive pose axes)
 *   -ms=<float>   Outer marker size in metres (default: 0.10)
 *   -show=<bool>  Display annotated images/video (default: true)
 *   -save=<dir>   Save annotated images, or an annotated MP4 for video
 *   --help        Show usage and dictionary names
 */
#include "opencv2/objdetect/aruco2.hpp"
#include "aruco2_prisma_dict.hpp"

#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace fs = std::filesystem;

static std::string lowercase(std::string value)
{
    std::transform(value.begin(), value.end(), value.begin(),
                   [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
    return value;
}

static bool isImage(const fs::path& path)
{
    const std::string ext = lowercase(path.extension().string());
    return ext == ".jpg" || ext == ".jpeg" || ext == ".png";
}

static bool isVideo(const fs::path& path)
{
    const std::string ext = lowercase(path.extension().string());
    return ext == ".mp4" || ext == ".avi" || ext == ".mkv" ||
           ext == ".mov" || ext == ".m4v" || ext == ".webm" ||
           ext == ".mpg" || ext == ".mpeg" || ext == ".wmv";
}

struct DetectedMarker
{
    int id;
    std::vector<int> levels;
};

struct FrameResult
{
    std::vector<DetectedMarker> markers;
    std::vector<int> ids;  // Unique IDs, for video statistics.
    int posesDrawn = 0;
};

// Match the webcam utility: scale camera intrinsics to the actual frame size.
// Distortion coefficients remain unchanged when the image is only resized.
static cv::Mat scaleCameraMatrix(
    const cv::Mat& originalCameraMatrix,
    const cv::Size& calibrationSize,
    const cv::Size& frameSize)
{
    cv::Mat scaled = originalCameraMatrix.clone();
    if (calibrationSize.width <= 0 || calibrationSize.height <= 0 ||
        calibrationSize == frameSize)
        return scaled;

    const double scaleX =
        static_cast<double>(frameSize.width) / calibrationSize.width;
    const double scaleY =
        static_cast<double>(frameSize.height) / calibrationSize.height;
    scaled.at<double>(0, 0) *= scaleX;  // fx
    scaled.at<double>(0, 2) *= scaleX;  // cx
    scaled.at<double>(1, 1) *= scaleY;  // fy
    scaled.at<double>(1, 2) *= scaleY;  // cy
    return scaled;
}

static bool drawAdaptiveAxis(
    cv::Mat& image,
    const cv::Mat& cameraMatrix,
    const cv::Mat& distCoeffs,
    const cv::Mat& rotationVector,
    const cv::Mat& translationVector,
    float markerSize)
{
    if (image.empty() || rotationVector.total() != 3 ||
        translationVector.total() != 3 ||
        !cv::checkRange(rotationVector) || !cv::checkRange(translationVector))
        return false;

    cv::Mat rvec64, tvec64;
    rotationVector.convertTo(rvec64, CV_64F);
    translationVector.convertTo(tvec64, CV_64F);
    const cv::Mat tvecRow = tvec64.reshape(1, 1);
    const double tx = tvecRow.at<double>(0, 0);
    const double ty = tvecRow.at<double>(0, 1);
    const double tz = tvecRow.at<double>(0, 2);
    if (!std::isfinite(tx) || !std::isfinite(ty) ||
        !std::isfinite(tz) || tz <= 1e-9)
        return false;

    // Exactly the scaling used by the old webcam utility:
    // at close range the length is capped at 25% of camera depth.
    const float axisLength = std::max(
        1e-6f,
        std::min(markerSize * 0.5f, static_cast<float>(tz * 0.25)));

    const std::vector<cv::Point3f> axis3D = {
        {0.f, 0.f, 0.f},
        {axisLength, 0.f, 0.f},
        {0.f, axisLength, 0.f},
        {0.f, 0.f, axisLength}
    };

    // Match the webcam's safety checks before calling drawAxis().
    cv::Mat rotationMatrix;
    cv::Rodrigues(rvec64, rotationMatrix);
    const double minimumDepth = std::max(1e-6, tz * 0.01);
    for (const auto& point : axis3D)
    {
        const double cameraZ =
            rotationMatrix.at<double>(2, 0) * point.x +
            rotationMatrix.at<double>(2, 1) * point.y +
            rotationMatrix.at<double>(2, 2) * point.z + tz;
        if (!std::isfinite(cameraZ) || cameraZ <= minimumDepth)
            return false;
    }

    std::vector<cv::Point2f> axis2D;
    try
    {
        cv::projectPoints(axis3D, rvec64, tvec64,
                          cameraMatrix, distCoeffs, axis2D);
    }
    catch (const cv::Exception&)
    {
        return false;
    }
    if (axis2D.size() != axis3D.size())
        return false;

    const double maxX = static_cast<double>(image.cols) * 100.0;
    const double maxY = static_cast<double>(image.rows) * 100.0;
    for (const auto& point : axis2D)
    {
        if (!std::isfinite(point.x) || !std::isfinite(point.y) ||
            std::abs(static_cast<double>(point.x)) > maxX ||
            std::abs(static_cast<double>(point.y)) > maxY)
            return false;
    }

    const double maxAxisPx =
        static_cast<double>(std::max(image.cols, image.rows)) * 100.0;
    for (std::size_t i = 1; i < axis2D.size(); ++i)
        if (cv::norm(axis2D[i] - axis2D[0]) > maxAxisPx)
            return false;

    cv::aruco2::drawAxis(image, cameraMatrix, distCoeffs,
                         rotationVector, translationVector, axisLength);
    return true;
}

static FrameResult detectAndAnnotate(
    cv::Mat& image,
    cv::aruco2::PrismaDetector& detector,
    bool hasCalib,
    const cv::Mat& cameraMatrix,
    const cv::Mat& distCoeffs,
    float markerSize)
{
    const auto markers = detector.detect(image, hasCalib);
    cv::aruco2::drawPrismaMarkers(image, markers);

    FrameResult result;
    result.ids.reserve(markers.size());
    result.markers.reserve(markers.size());

    for (const auto& marker : markers)
    {
        result.ids.push_back(marker.id);
        DetectedMarker detected{marker.id, {}};
        for (const auto level : marker.getLevels())
            detected.levels.push_back(level);
        result.markers.push_back(std::move(detected));

        if (!hasCalib)
            continue;

        cv::Mat objPts, imgPts, rvec, tvec;
        cv::aruco2::getSolvePnpPoints(marker, objPts, imgPts, markerSize);
        if (objPts.total() < 4 || objPts.total() != imgPts.total())
            continue;

        if (cv::solvePnP(objPts, imgPts, cameraMatrix, distCoeffs,
                         rvec, tvec, false, cv::SOLVEPNP_ITERATIVE))
        {
            if (drawAdaptiveAxis(image, cameraMatrix, distCoeffs,
                                 rvec, tvec, markerSize))
                ++result.posesDrawn;
        }
    }

    std::sort(result.ids.begin(), result.ids.end());
    result.ids.erase(std::unique(result.ids.begin(), result.ids.end()), result.ids.end());
    return result;
}

static void printResult(const std::string& label, const FrameResult& result, bool hasCalib)
{
    std::cout << label << " : " << result.markers.size() << " PRISMarker(s) detected";
    for (const auto& marker : result.markers)
    {
        std::cout << " [id=" << marker.id << ", levels=";
        for (std::size_t i = 0; i < marker.levels.size(); ++i)
            std::cout << (i ? "," : "") << marker.levels[i];
        std::cout << "]";
    }
    if (hasCalib)
        std::cout << " [poses=" << result.posesDrawn << "]";
    std::cout << '\n';
}

static cv::Mat resizeForDisplay(const cv::Mat& image)
{
    if (image.cols <= 1280 && image.rows <= 720)
        return image;

    const double scale = std::min(1280.0 / image.cols, 720.0 / image.rows);
    cv::Mat display;
    cv::resize(image, display, cv::Size(), scale, scale);
    return display;
}

int main(int argc, char** argv)
{
    try
    {
        cv::CommandLineParser parser(argc, argv,
            "{@path  |    | local image, folder of images or video file }"
            "{dict   | PRISMA_D3 | predefined PRISMarker dictionary name }"
            "{aux    | DICT_ARUCO_MIP_36h12 | auxiliary ArUco/AprilTag/ALVAR dictionary }"
            "{calib  |    | camera calibration YAML/XML }"
            "{ms     | 0.10 | outer marker side length in metres }"
            "{show   | true | display detections (ESC to exit) }"
            "{save   |    | output directory for annotated images or MP4 }"
            "{help   |    | show help }");

        if (parser.has("help"))
        {
            parser.printMessage();
            std::cout << "Supported input: local JPG/PNG, image folder, MP4/AVI/MKV/MOV/WebM.\n"
                      << "URLs and IP streams are not supported.\n"
                      << "Pose axes adapt to camera distance and frame resolution when -calib is provided.\n"
                      << "Available PRISMarker dictionaries:\n";
            for (const auto& name : cv::aruco2::getPrismaNames())
                std::cout << "  " << name << '\n';
            std::cout << "Available auxiliary dictionaries:\n";
            for (int id = static_cast<int>(cv::aruco2::DICT_4X4_50);
                 id <= static_cast<int>(cv::aruco2::DICT_ALVAR_7X7_1000); ++id)
            {
                std::cout << "  " << cv::aruco2::getDictInfo(
                    static_cast<cv::aruco2::DictionaryType>(id)).name << '\n';
            }
            return 0;
        }
        if (!parser.check())
        {
            parser.printErrors();
            return 1;
        }

        const std::string input = parser.get<std::string>("@path");
        const std::string dictName = parser.get<std::string>("dict");
        const std::string auxName = parser.get<std::string>("aux");
        const std::string calibFile = parser.get<std::string>("calib");
        const std::string saveDir = parser.get<std::string>("save");
        const bool show = parser.get<bool>("show");
        float markerSize = parser.get<float>("ms");

        if (input.empty())
        {
            parser.printMessage();
            return 1;
        }
        if (input.find("://") != std::string::npos)
            throw std::runtime_error("Only local image/video files are supported (no IP/URL streams)");
        if (!fs::exists(input))
            throw std::runtime_error("Path does not exist: " + input);

        const auto dictionary = cv::aruco2::getPrismaType(dictName);
        const auto auxiliaryDictionary = cv::aruco2::getDictInfo(auxName).type;

        cv::Mat cameraMatrix, distCoeffs;
        cv::Size calibrationSize;
        const bool hasCalib = !calibFile.empty();
        if (hasCalib)
        {
            cv::FileStorage storage(calibFile, cv::FileStorage::READ);
            if (!storage.isOpened())
                throw std::runtime_error("Cannot open calibration file: " + calibFile);

            storage["camera_matrix"] >> cameraMatrix;
            storage["distortion_coeffs"] >> distCoeffs;
            if (distCoeffs.empty())
                storage["distortion_coefficients"] >> distCoeffs;
            if (!parser.has("ms") && !storage["marker_size_m"].empty())
                storage["marker_size_m"] >> markerSize;
            if (cameraMatrix.empty() || cameraMatrix.rows != 3 || cameraMatrix.cols != 3)
                throw std::runtime_error("Calibration file missing a valid 3x3 camera_matrix");

            int calibrationWidth = 0;
            int calibrationHeight = 0;
            storage["image_width"] >> calibrationWidth;
            storage["image_height"] >> calibrationHeight;
            calibrationSize = cv::Size(calibrationWidth, calibrationHeight);

            cameraMatrix.convertTo(cameraMatrix, CV_64F);
            if (distCoeffs.empty())
                distCoeffs = cv::Mat::zeros(1, 5, CV_64F);
            else
                distCoeffs.convertTo(distCoeffs, CV_64F);
        }
        if (markerSize <= 0.f)
            throw std::runtime_error("ms must be positive");
        if (!saveDir.empty())
            fs::create_directories(saveDir);

        // Construct once, then reuse for every image/frame.
        cv::aruco2::PrismaDetector detector(dictionary, auxiliaryDictionary);
        std::cout << "PRISMarker dict=" << dictName << ", aux=" << auxName
                  << (hasCalib ? ", pose estimation ON" : "") << '\n';

        if (fs::is_regular_file(input) && isVideo(input))
        {
            cv::VideoCapture capture(input);
            if (!capture.isOpened())
                throw std::runtime_error("Cannot open local video: " + input);

            double fps = capture.get(cv::CAP_PROP_FPS);
            if (!std::isfinite(fps) || fps <= 0.0 || fps > 240.0)
                fps = 30.0;

            cv::VideoWriter writer;
            std::size_t frames = 0;
            std::size_t framesWithDetections = 0;
            std::map<int, std::size_t> framesById;
            std::vector<int> lastIds;
            const std::string windowName = "aruco2_detect_prisma";
            cv::Mat frameCameraMatrix;
            cv::Size currentFrameSize;

            cv::Mat frame;
            while (true)
            {
                const auto start = std::chrono::steady_clock::now();
                if (!capture.read(frame) || frame.empty())
                    break;
                ++frames;

                // Video output is created from the first decoded frame, using its real size.
                if (!saveDir.empty() && !writer.isOpened())
                {
                    const fs::path out = fs::path(saveDir) /
                        (fs::path(input).stem().string() + "_detected.mp4");
                    writer.open(out.string(), cv::VideoWriter::fourcc('m', 'p', '4', 'v'),
                                fps, frame.size(), true);
                    if (!writer.isOpened())
                        throw std::runtime_error("Cannot create annotated MP4: " + out.string());
                    std::cout << "Saving annotated video: " << out << '\n';
                }

                if (hasCalib && (frameCameraMatrix.empty() ||
                                 currentFrameSize != frame.size()))
                {
                    frameCameraMatrix = scaleCameraMatrix(
                        cameraMatrix, calibrationSize, frame.size());
                    currentFrameSize = frame.size();
                }
                const FrameResult result = detectAndAnnotate(
                    frame, detector, hasCalib, frameCameraMatrix, distCoeffs, markerSize);
                if (!result.ids.empty())
                    ++framesWithDetections;
                for (int id : result.ids)
                    ++framesById[id];

                // Avoid writing thousands of log lines during long videos.
                if (frames == 1 || frames % 30 == 0 || result.ids != lastIds)
                    printResult("frame " + std::to_string(frames), result, hasCalib);
                lastIds = result.ids;

                if (writer.isOpened())
                    writer.write(frame);

                if (show)
                {
                    cv::imshow(windowName, resizeForDisplay(frame));
                    const double elapsedMs = std::chrono::duration<double, std::milli>(
                        std::chrono::steady_clock::now() - start).count();
                    const int delayMs = std::max(1, static_cast<int>(
                        std::lround(1000.0 / fps - elapsedMs)));
                    const int key = cv::waitKey(delayMs);
                    if (key == 27 || key == 'q' || key == 'Q')
                        break;
                }
            }
            if (show)
                cv::destroyWindow(windowName);
            capture.release();
            writer.release();

            if (frames == 0)
                throw std::runtime_error("The video contains no decodable frames: " + input);

            std::cout << "\nVideo summary: " << frames << " frames processed, "
                      << framesWithDetections << " frames with PRISMarkers.\n";
            for (const auto& [id, count] : framesById)
                std::cout << "  ID " << id << ": " << count << " frames\n";
            return 0;
        }

        std::vector<fs::path> images;
        if (fs::is_directory(input))
        {
            for (const auto& entry : fs::directory_iterator(input))
                if (entry.is_regular_file() && isImage(entry.path()))
                    images.push_back(entry.path());
        }
        else if (fs::is_regular_file(input) && isImage(input))
        {
            images.emplace_back(input);
        }
        else
        {
            throw std::runtime_error(
                "Unsupported input: use a local image, image folder or video file");
        }

        std::sort(images.begin(), images.end());
        if (images.empty())
            throw std::runtime_error("No JPG/JPEG/PNG images found in: " + input);
        std::cout << "Found " << images.size() << " image(s).\n";

        for (const auto& path : images)
        {
            cv::Mat image = cv::imread(path.string(), cv::IMREAD_COLOR);
            if (image.empty())
            {
                std::cerr << "Cannot read: " << path << '\n';
                continue;
            }

            const cv::Mat frameCameraMatrix = hasCalib
                ? scaleCameraMatrix(cameraMatrix, calibrationSize, image.size())
                : cv::Mat();
            const FrameResult result = detectAndAnnotate(
                image, detector, hasCalib, frameCameraMatrix, distCoeffs, markerSize);
            printResult(path.filename().string(), result, hasCalib);

            if (!saveDir.empty())
            {
                const fs::path output = fs::path(saveDir) / path.filename();
                if (!cv::imwrite(output.string(), image))
                    std::cerr << "Cannot write: " << output << '\n';
            }
            if (show)
            {
                cv::imshow("aruco2_detect_prisma", resizeForDisplay(image));
                if (cv::waitKey(0) == 27)
                    break;
            }
        }
        if (show)
            cv::destroyAllWindows();
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << '\n';
        return 1;
    }
}