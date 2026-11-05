#pragma once
#include "data.hpp"
#include <array>
#include <cstddef>
#include <cstdint>

namespace cv { namespace aruco2 { namespace predef {

// D4: KCKC. Two consecutive patterns of each type per ID.
namespace d4 {

static constexpr std::size_t CAPACITY =
    (pattern_bank::BANK_SIZE / 2u);

inline std::array<pattern_bank::Ref, 4u> select(std::size_t id) {
    using pattern_bank::Kind;

    const auto inner = static_cast<std::uint16_t>(2u * id);
    const auto outer = static_cast<std::uint16_t>(2u * id + 1u);

    return {{
        {Kind::Cardinal, outer},
        {Kind::Corners, outer},
        {Kind::Cardinal, inner},
        {Kind::Corners, inner}
    }};
}

} // namespace d4
}}} // namespace cv::aruco2::predef
