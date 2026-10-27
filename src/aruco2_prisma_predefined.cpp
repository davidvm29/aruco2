#include "aruco2_prisma_dict.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <string>
#include <utility>

#include "prisma_dicts/n1_mip.hpp"
#include "prisma_dicts/n2_mip.hpp"
#include "prisma_dicts/n3_mip.hpp"
#include "prisma_dicts/n4_mip.hpp"
#include "prisma_dicts/n1_april.hpp"
#include "prisma_dicts/n2_april.hpp"
#include "prisma_dicts/n3_april.hpp"
#include "prisma_dicts/n4_april.hpp"

namespace cv {
namespace aruco2 {
namespace {

namespace pd = predef;

struct Info
{
    PrismaDict type;
    DictionaryType aux;
    const char* name;
    std::size_t count;
};

static constexpr Info dicts[] = {
    {pd::n1_mip::type,   pd::n1_mip::aux,   pd::n1_mip::name,   std::size(pd::n1_mip::markers)},
    {pd::n2_mip::type,   pd::n2_mip::aux,   pd::n2_mip::name,   std::size(pd::n2_mip::markers)},
    {pd::n3_mip::type,   pd::n3_mip::aux,   pd::n3_mip::name,   std::size(pd::n3_mip::markers)},
    {pd::n4_mip::type,   pd::n4_mip::aux,   pd::n4_mip::name,   std::size(pd::n4_mip::markers)},
    {pd::n1_april::type, pd::n1_april::aux, pd::n1_april::name, std::size(pd::n1_april::markers)},
    {pd::n2_april::type, pd::n2_april::aux, pd::n2_april::name, std::size(pd::n2_april::markers)},
    {pd::n3_april::type, pd::n3_april::aux, pd::n3_april::name, std::size(pd::n3_april::markers)},
    {pd::n4_april::type, pd::n4_april::aux, pd::n4_april::name, std::size(pd::n4_april::markers)}
};

const Info* findInfo(PrismaDict type)
{
    for (const auto& d : dicts)
        if (d.type == type)
            return &d;

    return nullptr;
}

const Info* findInfo(const cv::String& name)
{
    for (const auto& d : dicts)
        if (name == d.name)
            return &d;

    return nullptr;
}

[[noreturn]] void fail(const std::string& msg)
{
    CV_Error(cv::Error::StsBadArg, msg);
}

std::vector<unsigned char> unpack(
    const std::array<std::uint8_t, pd::BYTES>& src
)
{
    std::vector<unsigned char> bits(pd::BITS, 0u);

    for (std::size_t i = 0; i < pd::BITS; ++i)
        bits[i] = static_cast<unsigned char>(
            (src[i >> 3u] >> (i & 7u)) & 1u
        );

    return bits;
}

// Convert the compact compile-time representation into the simple logical one.
template<std::size_t L, std::size_t M>
detail::PDict makeDict(
    const pd::Marker<L> (&src)[M],
    DictionaryType arucoDict
)
{
    detail::PDict dict;
    dict.arucoDict = arucoDict;
    dict.markers.reserve(M);

    for (std::size_t id = 0; id < M; ++id)
    {
        const auto& srcMark = src[id];

        detail::PMark mark;
        mark.id = static_cast<int>(id);
        mark.center = srcMark.center;
        mark.levels.reserve(L);

        for (const auto& srcLevel : srcMark.levels)
        {
            detail::PLevel level;
            level.n = pd::N;
            level.k = pd::K;
            level.layout = srcLevel.layout;

            for (std::size_t i = 0; i < srcLevel.ids.size(); ++i)
                level.aruco[i] = srcLevel.ids[i];

            level.bits = unpack(srcLevel.bits);
            mark.levels.push_back(std::move(level));
        }

        dict.markers.push_back(std::move(mark));
    }

    return dict;
}

} // namespace

cv::String getPrismaName(PrismaDict type)
{
    const Info* d = findInfo(type);

    if (!d)
        fail(
            "Invalid predefined PRISMarker dictionary type: " +
            std::to_string(static_cast<int>(type))
        );

    return d->name;
}

PrismaDict getPrismaType(const cv::String& name)
{
    const Info* d = findInfo(name);

    if (!d)
        fail("Invalid predefined PRISMarker dictionary name: " + std::string(name));

    return d->type;
}

DictionaryType getPrismaDict(PrismaDict type)
{
    const Info* d = findInfo(type);

    if (!d)
        fail(
            "Invalid predefined PRISMarker dictionary type: " +
            std::to_string(static_cast<int>(type))
        );

    return d->aux;
}

int getPrismaCount(PrismaDict type)
{
    const Info* d = findInfo(type);

    if (!d)
        fail(
            "Invalid predefined PRISMarker dictionary type: " +
            std::to_string(static_cast<int>(type))
        );

    return static_cast<int>(d->count);
}

std::vector<cv::String> getPrismaNames()
{
    std::vector<cv::String> names;
    names.reserve(std::size(dicts));

    for (const auto& d : dicts)
        names.emplace_back(d.name);

    return names;
}

namespace detail {

PDict loadPDict(PrismaDict type)
{
    switch (type)
    {
        case pd::n1_mip::type:   return makeDict(pd::n1_mip::markers,   pd::n1_mip::aux);
        case pd::n2_mip::type:   return makeDict(pd::n2_mip::markers,   pd::n2_mip::aux);
        case pd::n3_mip::type:   return makeDict(pd::n3_mip::markers,   pd::n3_mip::aux);
        case pd::n4_mip::type:   return makeDict(pd::n4_mip::markers,   pd::n4_mip::aux);
        case pd::n1_april::type: return makeDict(pd::n1_april::markers, pd::n1_april::aux);
        case pd::n2_april::type: return makeDict(pd::n2_april::markers, pd::n2_april::aux);
        case pd::n3_april::type: return makeDict(pd::n3_april::markers, pd::n3_april::aux);
        case pd::n4_april::type: return makeDict(pd::n4_april::markers, pd::n4_april::aux);
    }

    fail(
        "Invalid predefined PRISMarker dictionary type: " +
        std::to_string(static_cast<int>(type))
    );
}

PDict loadPDict(const cv::String& name)
{
    const Info* d = findInfo(name);

    if (!d)
        fail("Invalid predefined PRISMarker dictionary name: " + std::string(name));

    return loadPDict(d->type);
}

} // namespace detail
} // namespace aruco2
} // namespace cv