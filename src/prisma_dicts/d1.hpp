#pragma once
#include "data.hpp"
#include <array>
#include <cstddef>
#include <cstdint>

namespace cv { namespace aruco2 { namespace predef {
// D1: CORNERS o CARDINAL (C/K), un patrón por PRISMarker.
namespace d1 {
static constexpr std::size_t CAPACITY = (2u * pattern_bank::BANK_SIZE);
inline std::array<pattern_bank::Ref, 1u> select(std::size_t id) {
    using pattern_bank::Kind;
    if (id < pattern_bank::BANK_SIZE)
        return {{ {Kind::Corners, static_cast<std::uint16_t>(id)} }};
    return {{ {Kind::Cardinal,
                static_cast<std::uint16_t>(id - pattern_bank::BANK_SIZE)} }};
}
} // namespace d1
}}} // namespace cv::aruco2::predef
