
#pragma once
#include "data.hpp"
#include <array>
#include <cstddef>
#include <cstdint>

namespace cv { namespace aruco2 { namespace predef {

// D3: CKC or KCK
namespace d3 {

static constexpr std::size_t CAPACITY =
    (2u * pattern_bank::BANK_SIZE / 3u);

static constexpr std::size_t CKC_COUNT =
    pattern_bank::BANK_SIZE - CAPACITY; // 67

static constexpr std::size_t KCK_COUNT =
    CAPACITY - CKC_COUNT; // 66

static_assert(2u * CKC_COUNT + KCK_COUNT <= pattern_bank::BANK_SIZE,
              "Not enough CORNERS patterns for D3");
static_assert(CKC_COUNT + 2u * KCK_COUNT <= pattern_bank::BANK_SIZE,
              "Not enough CARDINAL patterns for D3");

inline std::array<pattern_bank::Ref, 3u> select(std::size_t id) {
    using pattern_bank::Kind;

    if (id < CKC_COUNT) {
        // IDs 0..66: C[2*id+1], K[id], C[2*id].
        return {{
            {Kind::Corners, static_cast<std::uint16_t>(2u * id + 1u)},
            {Kind::Cardinal, static_cast<std::uint16_t>(id)},
            {Kind::Corners, static_cast<std::uint16_t>(2u * id)}
        }};
    }

    // IDs 67..132: KCK.
    const std::size_t j = id - CKC_COUNT;

    return {{
        {Kind::Cardinal, static_cast<std::uint16_t>(CKC_COUNT + 2u * j + 1u)},
        {Kind::Corners, static_cast<std::uint16_t>(2u * CKC_COUNT + j)},
        {Kind::Cardinal, static_cast<std::uint16_t>(CKC_COUNT + 2u * j)}
    }};
}

} // namespace d3
}}} // namespace cv::aruco2::predef
