#pragma once

#include "opencv2/objdetect/aruco2.hpp"

#include <array>
#include <cstddef>
#include <cstdint>

namespace cv {
namespace aruco2 {
namespace predef {

// Common geometry of the built-in PRISMarker dictionaries.
static constexpr std::uint16_t BITS = 100u;
static constexpr std::uint8_t N = 10u;
static constexpr std::uint8_t K = 6u;
static constexpr std::size_t BYTES = (BITS + 7u) / 8u;

// One fractal level.
struct Level
{
    std::array<std::uint8_t, BYTES> bits;
    PrismaLayout layout;
    // CARDINAL: N,E,S,W. CORNERS: TL,TR,BR,BL.
    std::array<std::uint16_t, 4> ids;
};

// One PRISMarker. Its array position is its ID.
template<std::size_t L>
struct Marker
{
    std::uint16_t center;
    std::array<Level, L> levels;
};

} // namespace predef
} // namespace aruco2
} // namespace cv
