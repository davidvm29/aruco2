
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

// Load a predefined PRISMarker dictionary.
PDict loadPDict(PrismaDict type);
PDict loadPDict(const cv::String& name);

} // namespace detail
