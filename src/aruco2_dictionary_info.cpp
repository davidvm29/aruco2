#include "aruco2_prisma_dict.hpp"

#include <array>
#include <string>

namespace cv {
namespace aruco2 {
namespace {

constexpr std::array<DictInfo, 2> kDictInfo = {{
    {
        DICT_ARUCO_MIP_36h12,
        "DICT_ARUCO_MIP_36h12",
        250,
        6,
        12
    },
    {
        DICT_APRILTAG_36h11,
        "DICT_APRILTAG_36h11",
        587,
        6,
        11
    }
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