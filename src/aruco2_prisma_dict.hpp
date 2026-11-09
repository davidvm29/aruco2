
#ifndef OPENCV_ARUCO2_PRISMA_DICT_HPP
#define OPENCV_ARUCO2_PRISMA_DICT_HPP

#include <array>
#include <vector>

#include "opencv2/objdetect/aruco2.hpp"

namespace cv {
namespace aruco2 {

// Auxiliary ArUco dictionary metadata.
struct DictInfo
{
    DictionaryType type;
    const char* name;
    int count;
    int bits;
    int minDist;
};

const DictInfo& getDictInfo(DictionaryType dictionary);
const DictInfo& getDictInfo(const cv::String& name);

namespace detail {

// One level of a PRISMarker.
struct PLevel
{
    PrismaLayout layout = PRISMA_LAYOUT_CARDINAL;
    int n = 0;
    int k = 0;
    std::array<int, 4> aruco = {-1, -1, -1, -1};
    std::vector<unsigned char> bits;
};

// One logical PRISMarker.
struct PMark
{
    int id = -1;
    int center = -1;
    std::vector<PLevel> levels; // outermost to innermost
};

// Predefined PRISMarker dictionary.
struct PDict
{
    DictionaryType arucoDict = static_cast<DictionaryType>(-1);
    std::vector<PMark> markers;
};

// Build only the requested marker (used by image generation).
PMark loadPMarker(
    PrismaDict type,
    DictionaryType auxiliaryDictionary,
    int markerId
);

// Load the complete dictionary (used by the detector).
PDict loadPDict(
    PrismaDict type,
    DictionaryType auxiliaryDictionary
);

PDict loadPDict(
    const cv::String& name,
    DictionaryType auxiliaryDictionary
);

} // namespace detail
} // namespace aruco2
} // namespace cv

#endif // OPENCV_ARUCO2_PRISMA_DICT_HPP
