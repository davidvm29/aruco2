/**
 * @file aruco2_detect_prisma.cpp
 * @brief Detect PRISMarkers in an image or a folder of images.
 *
 * Usage:
 *   ./aruco2_detect_prisma <image_or_folder> [options]
 *
 * Options:
 *   -dict=<name>  PRISMarker dictionary (default: PRISMA_D3_ARUCO_MIP_36H12)
 *   -calib=<path> Camera calibration YAML/XML
 *   -ms=<float>   Outer marker side length in metres (default: 0.10)
 *   -show=<bool>  Show each annotated image (default: true)
 *   -save=<path>  Directory for annotated images
 *   --help        Show usage and dictionary names
 */
#include "opencv2/objdetect/aruco2.hpp"
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

static bool isImage(const fs::path& path)
{
    std::string ext = path.extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(),
                   [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
    return ext == ".jpg" || ext == ".jpeg" || ext == ".png";
}

int main(int argc, char** argv)
{
    try
    {
        cv::CommandLineParser parser(argc, argv,
            "{@path  |    | image or folder with images (jpg/jpeg/png) }"
            "{dict   | PRISMA_D3_ARUCO_MIP_36H12 | predefined PRISMarker dictionary name }"
            "{calib  |    | camera calibration YAML/XML }"
            "{ms     | 0.10 | outer marker side length in metres }"
            "{show   | true | show detections (ESC to exit) }"
            "{save   |    | folder for annotated images }"
            "{help   |    | show help }");

        if (parser.has("help"))
        {
            parser.printMessage();
            std::cout << "Available dictionaries:\n";
            for (const auto& name : cv::aruco2::getPrismaNames())
                std::cout << "  " << name << '\n';
            return 0;
        }
        if (!parser.check())
        {
            parser.printErrors();
            return 1;
        }

        const std::string input = parser.get<std::string>("@path");
        const std::string calibFile = parser.get<std::string>("calib");
        const std::string saveDir = parser.get<std::string>("save");
        const bool show = parser.get<bool>("show");
        float markerSize = parser.get<float>("ms");
        const std::string dictName = parser.get<std::string>("dict");

        if (input.empty())
        {
            parser.printMessage();
            return 1;
        }
        const auto dictionary = cv::aruco2::getPrismaType(dictName);

        cv::Mat cameraMatrix, distCoeffs;
        const bool hasCalib = !calibFile.empty();
        if (hasCalib)
        {
            cv::FileStorage storage(calibFile, cv::FileStorage::READ);
            if (!storage.isOpened())
            {
                std::cerr << "Cannot open calibration file: " << calibFile << '\n';
                return 1;
            }
            storage["camera_matrix"] >> cameraMatrix;
            storage["distortion_coeffs"] >> distCoeffs;
            if (distCoeffs.empty())
                storage["distortion_coefficients"] >> distCoeffs;
            if (!parser.has("ms") && !storage["marker_size_m"].empty())
                storage["marker_size_m"] >> markerSize;

            if (cameraMatrix.empty())
            {
                std::cerr << "Calibration file missing camera_matrix\n";
                return 1;
            }
        }
        if (markerSize <= 0.f)
        {
            std::cerr << "ms must be positive\n";
            return 1;
        }
        if (!fs::exists(input))
        {
            std::cerr << "Path does not exist: " << input << '\n';
            return 1;
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
        std::sort(images.begin(), images.end());
        if (images.empty())
        {
            std::cerr << "No jpg/jpeg/png images found in: " << input << '\n';
            return 1;
        }
        if (!saveDir.empty())
            fs::create_directories(saveDir);

        cv::aruco2::PrismaDetector detector(dictionary);
        std::cout << "Found " << images.size() << " images, dict=" << dictName
                  << (hasCalib ? ", pose estimation ON" : "") << '\n';

        for (const auto& path : images)
        {
            cv::Mat image = cv::imread(path.string(), cv::IMREAD_COLOR);
            if (image.empty())
            {
                std::cerr << "Cannot read: " << path << '\n';
                continue;
            }

            const auto markers = detector.detect(image, hasCalib);
            cv::aruco2::drawPrisma(image, markers);

            std::cout << path.filename().string() << " : " << markers.size()
                      << " PRISMarker(s) detected";
            for (const auto& marker : markers)
            {
                std::cout << " [id=" << marker.id << ", levels=";
                const auto levels = marker.getLevels();
                for (std::size_t i = 0; i < levels.size(); ++i)
                    std::cout << (i ? "," : "") << levels[i];
                std::cout << "]";
            }

            int posesDrawn = 0;
            if (hasCalib)
            {
                for (const auto& marker : markers)
                {
                    cv::Mat objPts, imgPts, rvec, tvec;
                    cv::aruco2::getSolvePnpPoints(marker, objPts, imgPts, markerSize);
                    if (objPts.total() < 4 || objPts.total() != imgPts.total())
                        continue;

                    if (cv::solvePnP(objPts, imgPts, cameraMatrix, distCoeffs,
                                     rvec, tvec))
                    {
                        cv::aruco2::drawAxis(image, cameraMatrix, distCoeffs,
                                             rvec, tvec, markerSize * 0.5f);
                        ++posesDrawn;
                    }
                }
                std::cout << "  [poses=" << posesDrawn << "]";
            }
            std::cout << '\n';

            if (!saveDir.empty())
            {
                const fs::path output = fs::path(saveDir) / path.filename();
                if (!cv::imwrite(output.string(), image))
                    std::cerr << "Cannot write: " << output << '\n';
            }
            if (show)
            {
                cv::Mat display = image;
                if (display.cols > 1280 || display.rows > 720)
                {
                    const double scale = std::min(1280.0 / display.cols,
                                                  720.0 / display.rows);
                    cv::resize(display, display, cv::Size(), scale, scale);
                }
                cv::imshow("aruco2_detect_prisma", display);
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
        std::cerr << e.what() << '\n';
        return 1;
    }
}
