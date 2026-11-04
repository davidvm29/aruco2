#include "aruco2_prisma_dict.hpp"

#include <array>
#include <string>

namespace cv {
namespace aruco2 {
namespace {


constexpr std::array<DictInfo, 24> kDictInfo = {{
    {DICT_4X4_50,           "DICT_4X4_50",           50,   4,  4},
    {DICT_4X4_100,          "DICT_4X4_100",          100,  4,  3},
    {DICT_4X4_250,          "DICT_4X4_250",          250,  4,  3},
    {DICT_4X4_1000,         "DICT_4X4_1000",         1000, 4,  2},

    {DICT_5X5_50,           "DICT_5X5_50",           50,   5,  8},
    {DICT_5X5_100,          "DICT_5X5_100",          100,  5,  7},
    {DICT_5X5_250,          "DICT_5X5_250",          250,  5,  6},
    {DICT_5X5_1000,         "DICT_5X5_1000",         1000, 5,  5},

    {DICT_6X6_50,           "DICT_6X6_50",           50,   6, 13},
    {DICT_6X6_100,          "DICT_6X6_100",          100,  6, 12},
    {DICT_6X6_250,          "DICT_6X6_250",          250,  6, 11},
    {DICT_6X6_1000,         "DICT_6X6_1000",         1000, 6,  9},

    {DICT_7X7_50,           "DICT_7X7_50",           50,   7, 19},
    {DICT_7X7_100,          "DICT_7X7_100",          100,  7, 18},
    {DICT_7X7_250,          "DICT_7X7_250",          250,  7, 17},
    {DICT_7X7_1000,         "DICT_7X7_1000",         1000, 7, 14},

    {DICT_ARUCO_ORIGINAL,    "DICT_ARUCO_ORIGINAL",    1024, 5,  3},

    {DICT_APRILTAG_16h5,    "DICT_APRILTAG_16h5",    30,   4,  5},
    {DICT_APRILTAG_25h9,    "DICT_APRILTAG_25h9",    35,   5,  9},
    {DICT_APRILTAG_36h10,   "DICT_APRILTAG_36h10",   2320, 6, 10},
    {DICT_APRILTAG_36h11,   "DICT_APRILTAG_36h11",   587,  6, 11},

    {DICT_ARUCO_MIP_36h12,  "DICT_ARUCO_MIP_36h12",  250,  6, 12},

    {DICT_ALVAR_5X5_256,    "DICT_ALVAR_5X5_256",    256,  5,  4},
    {DICT_ALVAR_7X7_1000,   "DICT_ALVAR_7X7_1000",   1000, 7,  4}
}};

} // namespace

const DictInfo& getDictInfo(DictionaryType dictionary)
{
    for (const DictInfo& info : kDictInfo)
    {
        if (info.type == dictionary)
            return info;
    }

    CV_Error(
        cv::Error::StsBadArg,
        "Unsupported PRISMarker auxiliary DictionaryType value: " +
            std::to_string(static_cast<int>(dictionary))
    );

    return kDictInfo.front();
}

const DictInfo& getDictInfo(const cv::String& name)
{
    for (const DictInfo& info : kDictInfo)
    {
        if (name == info.name)
            return info;
    }

    CV_Error(
        cv::Error::StsBadArg,
        "Unsupported PRISMarker auxiliary dictionary name: " +
            std::string(name)
    );

    return kDictInfo.front();
}

} // namespace aruco2
} // namespace cv