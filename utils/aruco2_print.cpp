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
 *     ./aruco2_print p <out.png> <dict> [-aux AUX_DICT] <id> [bitSize]
 *
 *   PRISMarker batch mode:
 *     ./aruco2_print p <out_dir> <dict> [-aux AUX_DICT] all [bitSize]
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
#include "aruco2_prisma_dict.hpp"

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>

#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect/aruco_board.hpp>

using namespace std;
namespace fs = std::filesystem;

static bool startsWith(const std::string& value, const std::string& prefix)
{
    return value.rfind(prefix, 0) == 0;
}

static void printUsage()
{
    cerr
        << "Usage:\n"
        << "  ./aruco2_print <type> <out.png>\n"
        << "  ./aruco2_print p <out.png> <dict> [-aux AUX_DICT] <id> [bitSize]\n"
        << "  ./aruco2_print p <out_dir> <dict> [-aux AUX_DICT] all [bitSize]\n\n"
        << "Types:\n"
        << "  m : standard fiducial marker\n"
        << "  d : diamond marker\n"
        << "  b : grid board\n"
        << "  r : RAruco marker\n"
        << "  p : PRISMarker\n\n"
        << "Notes:\n"
        << "  - Default auxiliary dictionary: DICT_ARUCO_MIP_36h12\n"
        << "  - You can specify the auxiliary dictionary as:\n"
        << "      -aux DICT_APRILTAG_36h10\n"
        << "    or:\n"
        << "      -aux=DICT_APRILTAG_36h10\n\n"
        << "Available auxiliaries:\n";

    for (int id = static_cast<int>(cv::aruco2::DICT_4X4_50);
         id <= static_cast<int>(cv::aruco2::DICT_ALVAR_7X7_1000); ++id)
    {
        cerr << "  "
             << cv::aruco2::getDictInfo(
                    static_cast<cv::aruco2::DictionaryType>(id)).name
             << '\n';
    }
}

static cv::aruco2::DictionaryType parseAuxiliaryOption(
    int argc,
    char** argv,
    int& pos)
{
    cv::aruco2::DictionaryType auxiliaryDictionary =
        cv::aruco2::DICT_ARUCO_MIP_36h12;

    if (pos >= argc)
        return auxiliaryDictionary;

    const std::string token = argv[pos];

    if (startsWith(token, "-aux="))
    {
        const std::string auxName = token.substr(5);
        if (auxName.empty())
            throw std::runtime_error("Empty auxiliary dictionary after -aux=");
        auxiliaryDictionary = cv::aruco2::getDictInfo(auxName).type;
        ++pos;
        return auxiliaryDictionary;
    }

    if (token == "-aux")
    {
        if (pos + 1 >= argc)
            throw std::runtime_error("Missing value after -aux");
        auxiliaryDictionary = cv::aruco2::getDictInfo(argv[pos + 1]).type;
        pos += 2;
        return auxiliaryDictionary;
    }

    return auxiliaryDictionary;
}

static cv::Mat renderSinglePrisma(
    cv::aruco2::PrismaDict dict,
    int id,
    int bitSize,
    cv::aruco2::DictionaryType auxiliaryDictionary)
{
    cv::Mat image;
    cv::aruco2::getPrismaMarkerImage(
        image, dict, id, bitSize, auxiliaryDictionary);
    return image;
}

static void writeSinglePrisma(
    const std::string& outputPath,
    cv::aruco2::PrismaDict dict,
    int id,
    int bitSize,
    cv::aruco2::DictionaryType auxiliaryDictionary)
{
    cv::Mat image = renderSinglePrisma(dict, id, bitSize, auxiliaryDictionary);

    if (image.empty())
        throw std::runtime_error("Generated PRISMarker image is empty");

    if (!cv::imwrite(outputPath, image))
        throw std::runtime_error("Could not write output image: " + outputPath);
}

static void writeAllPrisma(
    const std::string& outputDir,
    cv::aruco2::PrismaDict dict,
    int bitSize,
    cv::aruco2::DictionaryType auxiliaryDictionary)
{
    fs::create_directories(outputDir);

    const cv::String dictName = cv::aruco2::getPrismaName(dict);
    const int count = cv::aruco2::getPrismaCount(dict, auxiliaryDictionary);

    for (int id = 0; id < count; ++id)
    {
        cv::Mat image = renderSinglePrisma(dict, id, bitSize, auxiliaryDictionary);

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
            if (argc < 5 || argc > 8)
            {
                printUsage();
                throw std::runtime_error(
                    "Mode 'p' expects:\n"
                    "  ./aruco2_print p <out.png> <dict> [-aux AUX_DICT] <id> [bitSize]\n"
                    "or\n"
                    "  ./aruco2_print p <out_dir> <dict> [-aux AUX_DICT] all [bitSize]");
            }

            const std::string output = argv[2];
            const cv::aruco2::PrismaDict dict =
                cv::aruco2::getPrismaType(argv[3]);

            int pos = 4;

            const auto auxiliaryDictionary =
                parseAuxiliaryOption(argc, argv, pos);

            if (pos >= argc)
            {
                printUsage();
                throw std::runtime_error(
                    "Missing PRISMarker id or 'all' after dictionary/auxiliary options");
            }

            const std::string idOrAll = argv[pos++];
            int bitSize = -1;

            if (pos < argc)
            {
                bitSize = std::stoi(argv[pos++]);
            }

            if (pos != argc)
            {
                printUsage();
                throw std::runtime_error("Too many arguments in mode 'p'");
            }

            if (idOrAll == "all")
            {
                writeAllPrisma(output, dict, bitSize, auxiliaryDictionary);
                return 0;
            }
            else
            {
                const int id = std::stoi(idOrAll);
                writeSinglePrisma(output, dict, id, bitSize, auxiliaryDictionary);
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