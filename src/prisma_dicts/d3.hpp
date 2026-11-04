#pragma once
#include "data.hpp"
#include <array>
#include <cstddef>
#include <cstdint>

namespace cv { namespace aruco2 { namespace predef {
// D3: CORNERS-CARDINAL-CORNERS (CKC) o CARDINAL-CORNERS-CARDINAL (KCK).
namespace d3 {
static constexpr std::size_t CAPACITY = (2u * pattern_bank::BANK_SIZE / 3u);
inline std::array<pattern_bank::Ref, 3u> select(std::size_t id, std::size_t count) {
    using pattern_bank::Kind;
    const std::size_t x = count <= (pattern_bank::BANK_SIZE / 2u)
        ? count : pattern_bank::BANK_SIZE - count;
    if (id < x) {
        // CKC: C[x + id] (exterior), K[id], C[id] (interior).
        return {{ {Kind::Corners, static_cast<std::uint16_t>(x + id)},
                  {Kind::Cardinal, static_cast<std::uint16_t>(id)},
                  {Kind::Corners, static_cast<std::uint16_t>(id)} }};
    }
    // KCK: K[count + j] (exterior), C[2*x + j], K[x + j] (interior).
    const std::size_t j = id - x;
    return {{ {Kind::Cardinal, static_cast<std::uint16_t>(count + j)},
              {Kind::Corners, static_cast<std::uint16_t>(2u*x + j)},
              {Kind::Cardinal, static_cast<std::uint16_t>(x + j)} }};
}
} // namespace d3
}}} // namespace cv::aruco2::predef
