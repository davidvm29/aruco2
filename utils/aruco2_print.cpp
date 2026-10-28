/**
 * @file aruco2_print.cpp
 * @brief Utility to generate and save images of various ArUco2 markers and boards.
 *
 * This program generates and saves an image of a standard marker, diamond,
 * grid board, RAruco marker, or PRISMarker.
 *
 * Usage:
 *   Legacy modes:
 *     ./aruco2_print <type> <out.png>
 *
 *   PRISMarker single mode:
 *     ./aruco2_print p <out.png> <dict> <id> [bitSize]
 *
 *   PRISMarker batch mode:
 *     ./aruco2_print p <out_dir> <dict> all [bitSize]
 *
 * Arguments:
 *   type           Type of pattern to generate:
 *                    m : Single standard fiducial marker
 *                    d : Diamond marker
 *                    b : Grid board
 *                    r : RAruco marker
 *                    p : PRISMarker
 */
#include "opencv2/objdetect/aruco2.hpp"

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect/aruco_board.hpp>

using namespace std;
namespace fs = std::filesystem;

static void printUsage()
{
    cerr
        << "Usage:\n"
        << "  ./aruco2_print <type> <out.png>\n"
        << "  ./aruco2_print p <out.png> <dict> <id> [bitSize]\n"
        << "  ./aruco2_print p <out_dir> <dict> all [bitSize]\n\n"
        << "Types:\n"
        << "  m : standard fiducial marker\n"
        << "  d : diamond marker\n"
        << "  b : grid board\n"
        << "  r : RAruco marker\n"
        << "  p : PRISMarker\n";
}

static cv::Mat renderSinglePrisma(
    cv::aruco2::PrismaDict dict,
    int id,
    int bitSize)
{
    std::vector<cv::Mat> images =
        cv::aruco2::printPrisma(dict, id, bitSize);

    if (images.empty())
        throw std::runtime_error("printPrisma returned no images");

    if (images.size() != 1)
        throw std::runtime_error("printPrisma returned more than one image");

    return images[0];
}

static void writeSinglePrisma(
    const std::string& outputPath,
    cv::aruco2::PrismaDict dict,
    int id,
    int bitSize)
{
    cv::Mat image = renderSinglePrisma(dict, id, bitSize);

    if (image.empty())
        throw std::runtime_error("Generated PRISMarker image is empty");

    if (!cv::imwrite(outputPath, image))
        throw std::runtime_error("Could not write output image: " + outputPath);
}

static void writeAllPrisma(
    const std::string& outputDir,
    cv::aruco2::PrismaDict dict,
    int bitSize)
{
    fs::create_directories(outputDir);

    const cv::String dictName = cv::aruco2::getPrismaName(dict);
    const int count = cv::aruco2::getPrismaCount(dict);

    for (int id = 0; id < count; ++id)
    {
        cv::Mat image = renderSinglePrisma(dict, id, bitSize);

        const fs::path outPath =
            fs::path(outputDir) /
            ("prisma_" + std::string(dictName) + "_" + std::to_string(id) + ".png");

        if (!cv::imwrite(outPath.string(), image))
        {
            throw std::runtime_error(
                "Could not write output image: " + outPath.string());
        }
    }

    std::cout << "Generated " << count
              << " PRISMarker images in: " << outputDir << std::endl;
}

int main(int argc, char **argv)
{
    try
    {
        if (argc < 3)
        {
            printUsage();
            throw std::runtime_error("Not enough arguments");
        }

        std::string type = argv[1];
        if (type != "m" && type != "d" && type != "b" &&
            type != "r" && type != "p")
        {
            printUsage();
            throw std::runtime_error("Unknown type");
        }

        cv::Mat outImage;

        if (type == "m")
        {
            if (argc != 3)
            {
                printUsage();
                throw std::runtime_error("Mode 'm' expects exactly 2 arguments after program name");
            }

            cv::aruco2::getFiducialMarkerImage(
                outImage,
                cv::aruco2::DICT_ARUCO_MIP_36h12,
                0,
                100);
        }
        else if (type == "d")
        {
            if (argc != 3)
            {
                printUsage();
                throw std::runtime_error("Mode 'd' expects exactly 2 arguments after program name");
            }

            cv::Vec4i ids{0,1,2,3};
            cv::aruco2::getDiamondImage(
                outImage,
                cv::aruco2::DICT_ARUCO_MIP_36h12,
                ids);
        }
        else if (type == "b")
        {
            if (argc != 3)
            {
                printUsage();
                throw std::runtime_error("Mode 'b' expects exactly 2 arguments after program name");
            }

            cv::aruco2::getGridBoardImage(
                outImage,
                cv::Size(9,5),
                cv::aruco2::DICT_ARUCO_MIP_36h12);
        }
        else if (type == "r")
        {
            if (argc != 3)
            {
                printUsage();
                throw std::runtime_error("Mode 'r' expects exactly 2 arguments after program name");
            }

            cv::aruco2::getRArucoMarkerImage(
                outImage,
                cv::aruco2::DICT_APRILTAG_16h5,
                0,
                2,
                30,
                2,
                1);
        }
        else if (type == "p")
        {
            if (argc != 5 && argc != 6)
            {
                printUsage();
                throw std::runtime_error(
                    "Mode 'p' expects:\n"
                    "  ./aruco2_print p <out.png> <dict> <id> [bitSize]\n"
                    "or\n"
                    "  ./aruco2_print p <out_dir> <dict> all [bitSize]");
            }

            const std::string output = argv[2];
            const cv::aruco2::PrismaDict dict =
                cv::aruco2::getPrismaType(argv[3]);

            const std::string idOrAll = argv[4];
            const int bitSize = (argc == 6) ? std::stoi(argv[5]) : -1;

            if (idOrAll == "all")
            {
                writeAllPrisma(output, dict, bitSize);
                return 0;
            }
            else
            {
                const int id = std::stoi(idOrAll);
                writeSinglePrisma(output, dict, id, bitSize);
                return 0;
            }
        }

        if (outImage.empty())
            throw std::runtime_error("Generated image is empty");

        if (!cv::imwrite(argv[2], outImage))
            throw std::runtime_error("Could not write output image");

        return 0;
    }
    catch (std::exception &ex)
    {
        cerr << ex.what() << endl;
        return 1;
    }
}