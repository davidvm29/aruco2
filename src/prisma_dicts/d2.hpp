#pragma once
#include "data.hpp"
#include <array>
#include <cstddef>
#include <cstdint>

namespace cv { namespace aruco2 { namespace predef {
// D2: CARDINAL exterior + CORNERS interior (KC).
namespace d2 {
static constexpr std::size_t CAPACITY = pattern_bank::BANK_SIZE;
// Una pareja única K(id), C(id) por marcador, hasta 200.
inline std::array<pattern_bank::Ref, 2u> select(std::size_t id) {
    using pattern_bank::Kind;
    const auto index = static_cast<std::uint16_t>(id);
    return {{ {Kind::Cardinal, index}, {Kind::Corners, index} }};
}
} // namespace d2
}}} // namespace cv::aruco2::predef
