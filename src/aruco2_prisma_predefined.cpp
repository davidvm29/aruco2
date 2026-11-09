// Generic PRISMarker dictionaries: one layout sequence per PRISMarker ID,
// selected deterministically for D1-D4 and the chosen auxiliary dictionary.
#include "aruco2_prisma_dict.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "prisma_dicts/d1.hpp"
#include "prisma_dicts/d2.hpp"
#include "prisma_dicts/d3.hpp"
#include "prisma_dicts/d4.hpp"

namespace cv {
namespace aruco2 {
namespace {

namespace pd = predef;
namespace bank = pd::pattern_bank;

struct Info {
    PrismaDict type;
    const char* name;
    int depth;
    std::size_t capacity;
};

static constexpr Info kInfos[] = {
    {PRISMA_D1, "PRISMA_D1", 1, pd::d1::CAPACITY},
    {PRISMA_D2, "PRISMA_D2", 2, pd::d2::CAPACITY},
    {PRISMA_D3, "PRISMA_D3", 3, pd::d3::CAPACITY},
    {PRISMA_D4, "PRISMA_D4", 4, pd::d4::CAPACITY}
};

[[noreturn]] void fail(const std::string& msg) {
    CV_Error(cv::Error::StsBadArg, msg);
}

const Info& findInfo(PrismaDict type) {
    for (const Info& d : kInfos)
        if (d.type == type) return d;
    fail("Invalid PRISMarker level: " + std::to_string(static_cast<int>(type)));
}

const Info& findInfo(const cv::String& name) {
    for (const Info& d : kInfos)
        if (name == d.name) return d;
    fail("Invalid PRISMarker level name: " + std::string(name));
}

int markerCount(const Info& info, DictionaryType auxiliaryDictionary) {
    const DictInfo& aux = getDictInfo(auxiliaryDictionary);
    if (aux.count <= 0)
        fail("Auxiliary dictionary has no usable codes");

    // Respect both resource bounds: auxiliary IDs (center + 4 per level)
    // and unique level layouts from the two banks.
    const int byAuxiliary = aux.count / (4 * info.depth + 1);
    const int byPatterns = static_cast<int>(info.capacity);
    return byAuxiliary < byPatterns ? byAuxiliary : byPatterns;
}

std::vector<unsigned char> unpack(const std::array<std::uint8_t, pd::BYTES>& packed) {
    std::vector<unsigned char> bits(pd::BITS, 0u);
    for (std::size_t i = 0; i < pd::BITS; ++i)
        bits[i] = static_cast<unsigned char>((packed[i / 8u] >> (i % 8u)) & 1u);
    return bits;
}

template<std::size_t L>
detail::PMark makeMarker(std::size_t id, const std::array<bank::Ref, L>& refs) {
    detail::PMark mark;
    mark.id = static_cast<int>(id);
    constexpr int stride = static_cast<int>(4u * L + 1u);
    mark.center = stride * mark.id;
    mark.levels.reserve(L);

    // refs are ordered outermost -> innermost.
    for (std::size_t j = 0; j < L; ++j) {
        const bank::Ref ref = refs[j];
        if (ref.index >= bank::BANK_SIZE)
            fail("PRISMarker pattern index outside the 200-entry bank");

        const auto& packed = (ref.kind == bank::Kind::Corners)
            ? bank::corners[ref.index] : bank::cardinal[ref.index];

        detail::PLevel level;
        level.n = pd::N;
        level.k = pd::K;
        level.layout = (ref.kind == bank::Kind::Corners)
            ? PRISMA_LAYOUT_CORNERS : PRISMA_LAYOUT_CARDINAL;
        level.bits = unpack(packed);

        // Match the historic allocation: center at stride*ID, first four aux
        // IDs for innermost level, last four for outermost level.
        const int first = mark.center + 1 + 4 * static_cast<int>(L - j - 1);
        for (std::size_t k = 0; k < 4; ++k)
            level.aruco[k] = first + static_cast<int>(k);
        mark.levels.push_back(std::move(level));
    }
    return mark;
}

template<std::size_t L, typename Choose>
detail::PDict build(DictionaryType auxiliaryDictionary, std::size_t count,
                    Choose choose) {
    detail::PDict result;
    result.arucoDict = auxiliaryDictionary;
    result.markers.reserve(count);
    for (std::size_t i = 0; i < count; ++i)
        result.markers.push_back(makeMarker<L>(i, choose(i)));
    return result;
}

} // namespace

cv::String getPrismaName(PrismaDict type) { return findInfo(type).name; }

PrismaDict getPrismaType(const cv::String& name) { return findInfo(name).type; }

int getPrismaCount(PrismaDict type, DictionaryType auxiliaryDictionary) {
    return markerCount(findInfo(type), auxiliaryDictionary);
}

std::vector<cv::String> getPrismaNames() {
    std::vector<cv::String> names;
    names.reserve(4);
    for (const Info& d : kInfos) names.emplace_back(d.name);
    return names;
}

namespace detail {

PMark loadPMarker(PrismaDict type, DictionaryType auxiliaryDictionary, int markerId) {
    const Info& info = findInfo(type);
    const int count = markerCount(info, auxiliaryDictionary);
    if (markerId < 0 || markerId >= count)
        fail("PRISMarker id not found: " + std::to_string(markerId));

    const std::size_t id = static_cast<std::size_t>(markerId);
    switch (info.depth) {
        case 1: return makeMarker<1>(id, pd::d1::select(id));
        case 2: return makeMarker<2>(id, pd::d2::select(id));
        case 3: return makeMarker<3>(id, pd::d3::select(id));
        case 4: return makeMarker<4>(id, pd::d4::select(id));
        default:
            fail("Unsupported PRISMarker level");
    }
}

PDict loadPDict(PrismaDict type, DictionaryType auxiliaryDictionary) {
    const Info& info = findInfo(type);
    const std::size_t count =
        static_cast<std::size_t>(markerCount(info, auxiliaryDictionary));
    switch (info.depth) {
        case 1: return build<1>(auxiliaryDictionary, count, pd::d1::select);
        case 2: return build<2>(auxiliaryDictionary, count, pd::d2::select);
        case 3: return build<3>(auxiliaryDictionary, count, pd::d3::select);
        case 4: return build<4>(auxiliaryDictionary, count, pd::d4::select);
        default:
            fail("Unsupported PRISMarker level");
    }
}


PDict loadPDict(const cv::String& name, DictionaryType auxiliaryDictionary) {
    return loadPDict(findInfo(name).type, auxiliaryDictionary);
}

} // namespace detail
} // namespace aruco2
} // namespace cv
