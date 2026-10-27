#pragma once

#include "data.hpp"

namespace cv {
namespace aruco2 {
namespace predef {
namespace n1_april {

// N1, AprilTag 36h11: 117 PRISMarkers.

static constexpr auto type = PRISMA_D1_APRILTAG_36H11;
static constexpr auto aux = DICT_APRILTAG_36h11;
static constexpr char name[] = "PRISMA_D1_APRILTAG_36H11";

using Mark = Marker<1>;

// Array position == PRISMarker ID.
static constexpr Mark markers[] = {

    // PRISMarker 0.
    {
        0u, // center
        {{
            // L0.
            {
                {{
                    0xB8, 0x60, 0xC2, 0xBF, 0x61, 0x86, 0x1C, 0x4E,
                    0x38, 0xFF, 0x20, 0x70, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{1u, 2u, 3u, 4u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 1.
    {
        5u, // center
        {{
            // L0.
            {
                {{
                    0x58, 0xD0, 0xD0, 0xBF, 0x21, 0x84, 0x1B, 0x76,
                    0x48, 0xFF, 0x84, 0x40, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{6u, 7u, 8u, 9u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 2.
    {
        10u, // center
        {{
            // L0.
            {
                {{
                    0x24, 0xF0, 0xE0, 0xCF, 0x61, 0x85, 0x1A, 0x66,
                    0xE8, 0xFF, 0x98, 0x70, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{11u, 12u, 13u, 14u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 3.
    {
        15u, // center
        {{
            // L0.
            {
                {{
                    0x20, 0xC0, 0xC2, 0xEF, 0x21, 0x85, 0x17, 0x6E,
                    0xE8, 0xFF, 0xFC, 0x80, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{16u, 17u, 18u, 19u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 4.
    {
        20u, // center
        {{
            // L0.
            {
                {{
                    0x94, 0xF0, 0xE0, 0x3F, 0x21, 0x87, 0x1D, 0x42,
                    0x58, 0x7F, 0x30, 0x70, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{21u, 22u, 23u, 24u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 5.
    {
        25u, // center
        {{
            // L0.
            {
                {{
                    0x30, 0x80, 0xC0, 0x7F, 0x21, 0x86, 0x1E, 0x46,
                    0xD8, 0x7F, 0x7C, 0x30, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{26u, 27u, 28u, 29u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 6.
    {
        30u, // center
        {{
            // L0.
            {
                {{
                    0xD8, 0x80, 0xD1, 0xEF, 0x21, 0x84, 0x1C, 0x6A,
                    0x58, 0x3F, 0x04, 0xF0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{31u, 32u, 33u, 34u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 7.
    {
        35u, // center
        {{
            // L0.
            {
                {{
                    0x0C, 0x30, 0xC0, 0xBF, 0xA1, 0x84, 0x17, 0x4E,
                    0xD8, 0x3F, 0x7C, 0x40, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{36u, 37u, 38u, 39u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 8.
    {
        40u, // center
        {{
            // L0.
            {
                {{
                    0xA0, 0x50, 0xF0, 0x5F, 0xE1, 0x85, 0x1D, 0x4E,
                    0x38, 0xFF, 0x80, 0x00, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{41u, 42u, 43u, 44u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 9.
    {
        45u, // center
        {{
            // L0.
            {
                {{
                    0x58, 0x10, 0xC1, 0x7F, 0x21, 0x87, 0x13, 0x76,
                    0xA8, 0x7F, 0x30, 0x20, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{46u, 47u, 48u, 49u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 10.
    {
        50u, // center
        {{
            // L0.
            {
                {{
                    0x24, 0x10, 0xE3, 0x3F, 0x61, 0x87, 0x17, 0x5A,
                    0xB8, 0x3F, 0x38, 0xE0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{51u, 52u, 53u, 54u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 11.
    {
        55u, // center
        {{
            // L0.
            {
                {{
                    0x6C, 0xC0, 0xF2, 0x6F, 0xE1, 0x85, 0x10, 0x56,
                    0x28, 0x3F, 0xCC, 0x30, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{56u, 57u, 58u, 59u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 12.
    {
        60u, // center
        {{
            // L0.
            {
                {{
                    0x34, 0xF0, 0xE2, 0x3F, 0x21, 0x87, 0x12, 0x6E,
                    0x48, 0x7F, 0x24, 0x90, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{61u, 62u, 63u, 64u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 13.
    {
        65u, // center
        {{
            // L0.
            {
                {{
                    0x7C, 0xE0, 0xF1, 0x0F, 0x61, 0x85, 0x16, 0x4E,
                    0x48, 0xFF, 0xCC, 0xE0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{66u, 67u, 68u, 69u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 14.
    {
        70u, // center
        {{
            // L0.
            {
                {{
                    0xC0, 0x50, 0xE2, 0xAF, 0xE1, 0x84, 0x1A, 0x5E,
                    0xF8, 0xBF, 0x70, 0xC0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{71u, 72u, 73u, 74u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 15.
    {
        75u, // center
        {{
            // L0.
            {
                {{
                    0xE0, 0x60, 0xE1, 0x0F, 0xA1, 0x86, 0x1A, 0x66,
                    0x48, 0xBF, 0xB8, 0xD0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{76u, 77u, 78u, 79u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 16.
    {
        80u, // center
        {{
            // L0.
            {
                {{
                    0xC0, 0x70, 0xC0, 0xDF, 0xE1, 0x87, 0x13, 0x52,
                    0x38, 0xFF, 0xD0, 0xD0, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{81u, 82u, 83u, 84u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 17.
    {
        85u, // center
        {{
            // L0.
            {
                {{
                    0xB8, 0xB0, 0xF2, 0x3F, 0x21, 0x87, 0x1F, 0x6A,
                    0x98, 0x3F, 0x08, 0x20, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{86u, 87u, 88u, 89u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 18.
    {
        90u, // center
        {{
            // L0.
            {
                {{
                    0xE0, 0xD0, 0xC0, 0x9F, 0x21, 0x87, 0x17, 0x52,
                    0x58, 0x3F, 0x5C, 0x60, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{91u, 92u, 93u, 94u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 19.
    {
        95u, // center
        {{
            // L0.
            {
                {{
                    0xB0, 0x70, 0xC3, 0xAF, 0x61, 0x86, 0x18, 0x72,
                    0xF8, 0xFF, 0x14, 0xB0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{96u, 97u, 98u, 99u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 20.
    {
        100u, // center
        {{
            // L0.
            {
                {{
                    0x2C, 0xA0, 0xF3, 0x4F, 0xA1, 0x87, 0x1E, 0x42,
                    0x98, 0xBF, 0x28, 0x70, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{101u, 102u, 103u, 104u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 21.
    {
        105u, // center
        {{
            // L0.
            {
                {{
                    0x6C, 0xF0, 0xF1, 0xAF, 0x21, 0x87, 0x14, 0x66,
                    0x38, 0x3F, 0xA0, 0xB0, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{106u, 107u, 108u, 109u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 22.
    {
        110u, // center
        {{
            // L0.
            {
                {{
                    0x0C, 0xA0, 0xD2, 0x1F, 0x21, 0x85, 0x17, 0x5E,
                    0x68, 0x7F, 0xE0, 0x10, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{111u, 112u, 113u, 114u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 23.
    {
        115u, // center
        {{
            // L0.
            {
                {{
                    0xE0, 0xA0, 0xD0, 0xAF, 0xA1, 0x85, 0x17, 0x76,
                    0xB8, 0xFF, 0xC0, 0x80, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{116u, 117u, 118u, 119u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 24.
    {
        120u, // center
        {{
            // L0.
            {
                {{
                    0xA0, 0x90, 0xC3, 0x0F, 0x61, 0x84, 0x1F, 0x76,
                    0xF8, 0xBF, 0x64, 0x20, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{121u, 122u, 123u, 124u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 25.
    {
        125u, // center
        {{
            // L0.
            {
                {{
                    0x20, 0xA0, 0xD3, 0xBF, 0xA1, 0x85, 0x1B, 0x7A,
                    0xA8, 0x3F, 0xB4, 0x10, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{126u, 127u, 128u, 129u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 26.
    {
        130u, // center
        {{
            // L0.
            {
                {{
                    0x78, 0xE0, 0xD2, 0x2F, 0xA1, 0x84, 0x1D, 0x42,
                    0x18, 0x7F, 0xC8, 0x50, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{131u, 132u, 133u, 134u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 27.
    {
        135u, // center
        {{
            // L0.
            {
                {{
                    0x00, 0x20, 0xD3, 0x5F, 0x21, 0x84, 0x15, 0x7E,
                    0x38, 0xBF, 0xE8, 0x40, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{136u, 137u, 138u, 139u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 28.
    {
        140u, // center
        {{
            // L0.
            {
                {{
                    0xCC, 0x90, 0xC3, 0x3F, 0x21, 0x86, 0x11, 0x6E,
                    0x08, 0xFF, 0xAC, 0xC0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{141u, 142u, 143u, 144u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 29.
    {
        145u, // center
        {{
            // L0.
            {
                {{
                    0xA8, 0x60, 0xE1, 0xDF, 0x61, 0x85, 0x1C, 0x52,
                    0x68, 0x7F, 0x70, 0x80, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{146u, 147u, 148u, 149u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 30.
    {
        150u, // center
        {{
            // L0.
            {
                {{
                    0x9C, 0x50, 0xE1, 0x4F, 0x21, 0x87, 0x18, 0x72,
                    0xE8, 0x7F, 0x8C, 0xE0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{151u, 152u, 153u, 154u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 31.
    {
        155u, // center
        {{
            // L0.
            {
                {{
                    0xFC, 0xA0, 0xE2, 0x7F, 0x21, 0x84, 0x14, 0x6E,
                    0xB8, 0x3F, 0x34, 0x00, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{156u, 157u, 158u, 159u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 32.
    {
        160u, // center
        {{
            // L0.
            {
                {{
                    0x60, 0x40, 0xF3, 0x7F, 0x21, 0x84, 0x1C, 0x7E,
                    0x98, 0xFF, 0x50, 0x40, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{161u, 162u, 163u, 164u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 33.
    {
        165u, // center
        {{
            // L0.
            {
                {{
                    0x14, 0xC0, 0xF2, 0xDF, 0x61, 0x84, 0x10, 0x4E,
                    0x38, 0x7F, 0xE8, 0x10, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{166u, 167u, 168u, 169u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 34.
    {
        170u, // center
        {{
            // L0.
            {
                {{
                    0x6C, 0xB0, 0xE2, 0xDF, 0x21, 0x85, 0x1A, 0x4A,
                    0x68, 0xBF, 0x58, 0x80, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{171u, 172u, 173u, 174u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 35.
    {
        175u, // center
        {{
            // L0.
            {
                {{
                    0x04, 0xB0, 0xC0, 0xCF, 0xE1, 0x87, 0x17, 0x42,
                    0xA8, 0x7F, 0x0C, 0x90, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{176u, 177u, 178u, 179u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 36.
    {
        180u, // center
        {{
            // L0.
            {
                {{
                    0x6C, 0x00, 0xC2, 0x5F, 0x61, 0x86, 0x14, 0x5A,
                    0xB8, 0xFF, 0x38, 0x00, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{181u, 182u, 183u, 184u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 37.
    {
        185u, // center
        {{
            // L0.
            {
                {{
                    0x1C, 0x80, 0xC2, 0x5F, 0x21, 0x86, 0x1C, 0x52,
                    0xF8, 0xBF, 0xEC, 0xC0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{186u, 187u, 188u, 189u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 38.
    {
        190u, // center
        {{
            // L0.
            {
                {{
                    0xA4, 0x70, 0xC2, 0xCF, 0xA1, 0x87, 0x17, 0x66,
                    0x48, 0xBF, 0x28, 0x70, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{191u, 192u, 193u, 194u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 39.
    {
        195u, // center
        {{
            // L0.
            {
                {{
                    0xC8, 0xD0, 0xD3, 0x7F, 0x61, 0x84, 0x14, 0x46,
                    0xD8, 0x7F, 0xE0, 0xC0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{196u, 197u, 198u, 199u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 40.
    {
        200u, // center
        {{
            // L0.
            {
                {{
                    0xCC, 0x20, 0xD2, 0x9F, 0xA1, 0x86, 0x15, 0x7E,
                    0x08, 0x7F, 0xF8, 0x70, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{201u, 202u, 203u, 204u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 41.
    {
        205u, // center
        {{
            // L0.
            {
                {{
                    0x7C, 0x30, 0xD3, 0x1F, 0xA1, 0x86, 0x11, 0x6E,
                    0x58, 0xFF, 0x20, 0x30, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{206u, 207u, 208u, 209u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 42.
    {
        210u, // center
        {{
            // L0.
            {
                {{
                    0x78, 0xC0, 0xC1, 0x3F, 0xA1, 0x87, 0x17, 0x4A,
                    0x78, 0x7F, 0x70, 0x30, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{211u, 212u, 213u, 214u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 43.
    {
        215u, // center
        {{
            // L0.
            {
                {{
                    0x78, 0xC0, 0xF3, 0x1F, 0x21, 0x85, 0x1C, 0x7A,
                    0x48, 0x3F, 0xB4, 0x90, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{216u, 217u, 218u, 219u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 44.
    {
        220u, // center
        {{
            // L0.
            {
                {{
                    0x8C, 0x30, 0xC3, 0xDF, 0x61, 0x85, 0x13, 0x42,
                    0x78, 0xFF, 0xA4, 0x40, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{221u, 222u, 223u, 224u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 45.
    {
        225u, // center
        {{
            // L0.
            {
                {{
                    0xD8, 0xD0, 0xC1, 0x8F, 0x61, 0x87, 0x14, 0x52,
                    0xC8, 0xBF, 0x30, 0x30, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{226u, 227u, 228u, 229u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 46.
    {
        230u, // center
        {{
            // L0.
            {
                {{
                    0x28, 0x70, 0xD0, 0x2F, 0x21, 0x84, 0x17, 0x72,
                    0x78, 0xFF, 0x08, 0x60, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{231u, 232u, 233u, 234u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 47.
    {
        235u, // center
        {{
            // L0.
            {
                {{
                    0x94, 0x90, 0xE1, 0x0F, 0xE1, 0x84, 0x1C, 0x6E,
                    0x58, 0xFF, 0x94, 0x50, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{236u, 237u, 238u, 239u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 48.
    {
        240u, // center
        {{
            // L0.
            {
                {{
                    0x74, 0x20, 0xE0, 0xFF, 0x61, 0x85, 0x1A, 0x5E,
                    0xD8, 0xBF, 0x00, 0x00, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{241u, 242u, 243u, 244u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 49.
    {
        245u, // center
        {{
            // L0.
            {
                {{
                    0x00, 0xD0, 0xD0, 0x3F, 0x61, 0x86, 0x18, 0x5A,
                    0xE8, 0xBF, 0x7C, 0xE0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{246u, 247u, 248u, 249u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 50.
    {
        250u, // center
        {{
            // L0.
            {
                {{
                    0xB8, 0x10, 0xE3, 0xCF, 0xE1, 0x85, 0x18, 0x66,
                    0x98, 0xBF, 0xC0, 0xC0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{251u, 252u, 253u, 254u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 51.
    {
        255u, // center
        {{
            // L0.
            {
                {{
                    0xE4, 0xD0, 0xD0, 0x1F, 0x61, 0x87, 0x11, 0x56,
                    0xB8, 0x7F, 0x20, 0xD0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{256u, 257u, 258u, 259u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 52.
    {
        260u, // center
        {{
            // L0.
            {
                {{
                    0xA8, 0x90, 0xE0, 0x5F, 0xE1, 0x85, 0x17, 0x7E,
                    0x48, 0xFF, 0x08, 0xE0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{261u, 262u, 263u, 264u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 53.
    {
        265u, // center
        {{
            // L0.
            {
                {{
                    0xAC, 0xC0, 0xD3, 0x3F, 0xE1, 0x84, 0x10, 0x42,
                    0x78, 0xFF, 0x9C, 0xA0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{266u, 267u, 268u, 269u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 54.
    {
        270u, // center
        {{
            // L0.
            {
                {{
                    0x44, 0xB0, 0xD2, 0x8F, 0x61, 0x86, 0x1E, 0x56,
                    0xC8, 0xFF, 0x4C, 0x70, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{271u, 272u, 273u, 274u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 55.
    {
        275u, // center
        {{
            // L0.
            {
                {{
                    0x5C, 0x10, 0xF3, 0x1F, 0xE1, 0x84, 0x13, 0x5E,
                    0x38, 0xBF, 0xB4, 0x20, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{276u, 277u, 278u, 279u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 56.
    {
        280u, // center
        {{
            // L0.
            {
                {{
                    0x74, 0x90, 0xD2, 0xBF, 0x21, 0x84, 0x12, 0x46,
                    0xB8, 0x7F, 0x64, 0x50, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{281u, 282u, 283u, 284u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 57.
    {
        285u, // center
        {{
            // L0.
            {
                {{
                    0x88, 0x50, 0xE0, 0x4F, 0x61, 0x84, 0x11, 0x7E,
                    0x38, 0x3F, 0xF4, 0xA0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{286u, 287u, 288u, 289u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 58.
    {
        290u, // center
        {{
            // L0.
            {
                {{
                    0x58, 0x50, 0xF0, 0x7F, 0xE1, 0x87, 0x1C, 0x56,
                    0xA8, 0xFF, 0x6C, 0x40, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{291u, 292u, 293u, 294u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 59.
    {
        295u, // center
        {{
            // L0.
            {
                {{
                    0x14, 0xB0, 0xD0, 0x6F, 0x21, 0x85, 0x19, 0x46,
                    0xD8, 0xFF, 0x8C, 0xE0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{296u, 297u, 298u, 299u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 60.
    {
        300u, // center
        {{
            // L0.
            {
                {{
                    0x38, 0xD0, 0xC3, 0x6F, 0x61, 0x87, 0x17, 0x66,
                    0x18, 0xFF, 0x00, 0x40, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{301u, 302u, 303u, 304u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 61.
    {
        305u, // center
        {{
            // L0.
            {
                {{
                    0x48, 0x70, 0xE1, 0x5F, 0x21, 0x87, 0x11, 0x5E,
                    0x48, 0xBF, 0xCC, 0xC0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{306u, 307u, 308u, 309u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 62.
    {
        310u, // center
        {{
            // L0.
            {
                {{
                    0xB8, 0x80, 0xF0, 0x5F, 0xA1, 0x85, 0x15, 0x46,
                    0x58, 0x7F, 0x70, 0x90, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{311u, 312u, 313u, 314u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 63.
    {
        315u, // center
        {{
            // L0.
            {
                {{
                    0x88, 0x30, 0xE3, 0x4F, 0x61, 0x87, 0x14, 0x46,
                    0x78, 0x3F, 0xF8, 0x60, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{316u, 317u, 318u, 319u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 64.
    {
        320u, // center
        {{
            // L0.
            {
                {{
                    0x0C, 0xD0, 0xD3, 0x9F, 0x61, 0x84, 0x1A, 0x7E,
                    0x38, 0x7F, 0x90, 0xA0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{321u, 322u, 323u, 324u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 65.
    {
        325u, // center
        {{
            // L0.
            {
                {{
                    0x90, 0x00, 0xD1, 0x5F, 0xE1, 0x85, 0x1E, 0x76,
                    0x58, 0x7F, 0x68, 0x20, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{326u, 327u, 328u, 329u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 66.
    {
        330u, // center
        {{
            // L0.
            {
                {{
                    0x54, 0x20, 0xD0, 0x3F, 0xE1, 0x87, 0x1C, 0x56,
                    0x58, 0x7F, 0x18, 0xF0, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{331u, 332u, 333u, 334u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 67.
    {
        335u, // center
        {{
            // L0.
            {
                {{
                    0x84, 0x20, 0xC2, 0xFF, 0xA1, 0x84, 0x1C, 0x66,
                    0xE8, 0xFF, 0x64, 0xF0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{336u, 337u, 338u, 339u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 68.
    {
        340u, // center
        {{
            // L0.
            {
                {{
                    0x00, 0x00, 0xC3, 0x7F, 0x61, 0x87, 0x1C, 0x6A,
                    0xD8, 0x7F, 0xE4, 0x50, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{341u, 342u, 343u, 344u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 69.
    {
        345u, // center
        {{
            // L0.
            {
                {{
                    0x48, 0x30, 0xD2, 0x7F, 0xA1, 0x85, 0x14, 0x6E,
                    0x78, 0x7F, 0x28, 0x50, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{346u, 347u, 348u, 349u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 70.
    {
        350u, // center
        {{
            // L0.
            {
                {{
                    0x2C, 0x60, 0xD2, 0xDF, 0xA1, 0x86, 0x10, 0x52,
                    0x18, 0x7F, 0xD0, 0xB0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{351u, 352u, 353u, 354u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 71.
    {
        355u, // center
        {{
            // L0.
            {
                {{
                    0xCC, 0x20, 0xE1, 0x2F, 0xE1, 0x86, 0x1A, 0x6A,
                    0x08, 0xBF, 0x84, 0x70, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{356u, 357u, 358u, 359u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 72.
    {
        360u, // center
        {{
            // L0.
            {
                {{
                    0x38, 0x10, 0xD2, 0x4F, 0xE1, 0x87, 0x1E, 0x4E,
                    0x18, 0xFF, 0x1C, 0x20, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{361u, 362u, 363u, 364u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 73.
    {
        365u, // center
        {{
            // L0.
            {
                {{
                    0xE0, 0xC0, 0xE2, 0xBF, 0x61, 0x87, 0x1C, 0x62,
                    0xA8, 0xBF, 0x20, 0xC0, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{366u, 367u, 368u, 369u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 74.
    {
        370u, // center
        {{
            // L0.
            {
                {{
                    0x14, 0xF0, 0xD2, 0x9F, 0xA1, 0x87, 0x11, 0x46,
                    0x68, 0x3F, 0x8C, 0x20, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{371u, 372u, 373u, 374u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 75.
    {
        375u, // center
        {{
            // L0.
            {
                {{
                    0xF8, 0x10, 0xD3, 0x4F, 0x21, 0x85, 0x1C, 0x62,
                    0x78, 0xBF, 0x7C, 0xC0, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{376u, 377u, 378u, 379u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 76.
    {
        380u, // center
        {{
            // L0.
            {
                {{
                    0x80, 0xF0, 0xF1, 0xFF, 0xA1, 0x84, 0x14, 0x76,
                    0x08, 0x7F, 0x90, 0x70, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{381u, 382u, 383u, 384u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 77.
    {
        385u, // center
        {{
            // L0.
            {
                {{
                    0x34, 0x10, 0xF3, 0x3F, 0xE1, 0x84, 0x1E, 0x6E,
                    0x28, 0xBF, 0x04, 0xE0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{386u, 387u, 388u, 389u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 78.
    {
        390u, // center
        {{
            // L0.
            {
                {{
                    0xE0, 0xD0, 0xE1, 0x7F, 0x61, 0x86, 0x16, 0x72,
                    0x78, 0xBF, 0x2C, 0x80, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{391u, 392u, 393u, 394u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 79.
    {
        395u, // center
        {{
            // L0.
            {
                {{
                    0x28, 0xC0, 0xF0, 0x8F, 0x61, 0x84, 0x14, 0x7A,
                    0xE8, 0xFF, 0xE4, 0x70, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{396u, 397u, 398u, 399u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 80.
    {
        400u, // center
        {{
            // L0.
            {
                {{
                    0x40, 0x20, 0xE1, 0x7F, 0xE1, 0x85, 0x1A, 0x4A,
                    0xC8, 0x7F, 0x34, 0x30, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{401u, 402u, 403u, 404u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 81.
    {
        405u, // center
        {{
            // L0.
            {
                {{
                    0x30, 0xA0, 0xF0, 0xEF, 0xE1, 0x86, 0x15, 0x5A,
                    0xF8, 0x3F, 0xC8, 0x40, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{406u, 407u, 408u, 409u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 82.
    {
        410u, // center
        {{
            // L0.
            {
                {{
                    0xF0, 0xA0, 0xF0, 0xFF, 0xE1, 0x86, 0x18, 0x6E,
                    0x28, 0xBF, 0x84, 0x80, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{411u, 412u, 413u, 414u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 83.
    {
        415u, // center
        {{
            // L0.
            {
                {{
                    0x8C, 0x00, 0xC3, 0x7F, 0xA1, 0x87, 0x1B, 0x46,
                    0xD8, 0xFF, 0x44, 0xA0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{416u, 417u, 418u, 419u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 84.
    {
        420u, // center
        {{
            // L0.
            {
                {{
                    0x7C, 0x90, 0xC1, 0x8F, 0x61, 0x86, 0x10, 0x72,
                    0xA8, 0xFF, 0x20, 0xC0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{421u, 422u, 423u, 424u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 85.
    {
        425u, // center
        {{
            // L0.
            {
                {{
                    0xF0, 0x90, 0xD3, 0x3F, 0xE1, 0x86, 0x17, 0x52,
                    0xB8, 0xBF, 0x98, 0x40, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{426u, 427u, 428u, 429u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 86.
    {
        430u, // center
        {{
            // L0.
            {
                {{
                    0x84, 0x50, 0xD3, 0xBF, 0xA1, 0x85, 0x1E, 0x46,
                    0x38, 0x3F, 0xCC, 0xC0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{431u, 432u, 433u, 434u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 87.
    {
        435u, // center
        {{
            // L0.
            {
                {{
                    0xE0, 0xB0, 0xF1, 0xDF, 0x21, 0x84, 0x1E, 0x7A,
                    0x18, 0x7F, 0x68, 0x40, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{436u, 437u, 438u, 439u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 88.
    {
        440u, // center
        {{
            // L0.
            {
                {{
                    0x3C, 0x40, 0xE2, 0x3F, 0xE1, 0x87, 0x13, 0x52,
                    0x98, 0x7F, 0x20, 0x30, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{441u, 442u, 443u, 444u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 89.
    {
        445u, // center
        {{
            // L0.
            {
                {{
                    0x6C, 0x00, 0xF2, 0x9F, 0x21, 0x85, 0x1A, 0x5E,
                    0x98, 0x3F, 0xAC, 0x30, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{446u, 447u, 448u, 449u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 90.
    {
        450u, // center
        {{
            // L0.
            {
                {{
                    0x54, 0xB0, 0xC3, 0x4F, 0x21, 0x85, 0x1B, 0x72,
                    0x78, 0x3F, 0xB8, 0x60, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{451u, 452u, 453u, 454u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 91.
    {
        455u, // center
        {{
            // L0.
            {
                {{
                    0x50, 0x20, 0xF0, 0x7F, 0xE1, 0x85, 0x17, 0x62,
                    0x78, 0x7F, 0x1C, 0x80, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{456u, 457u, 458u, 459u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 92.
    {
        460u, // center
        {{
            // L0.
            {
                {{
                    0x88, 0x50, 0xC3, 0x6F, 0xA1, 0x84, 0x1B, 0x66,
                    0x58, 0x3F, 0x7C, 0x70, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{461u, 462u, 463u, 464u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 93.
    {
        465u, // center
        {{
            // L0.
            {
                {{
                    0xC8, 0x30, 0xD1, 0xCF, 0xE1, 0x87, 0x1E, 0x7E,
                    0xA8, 0x7F, 0x04, 0xA0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{466u, 467u, 468u, 469u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 94.
    {
        470u, // center
        {{
            // L0.
            {
                {{
                    0xE0, 0x00, 0xE2, 0xCF, 0xE1, 0x87, 0x11, 0x62,
                    0x48, 0x7F, 0xB4, 0x30, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{471u, 472u, 473u, 474u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 95.
    {
        475u, // center
        {{
            // L0.
            {
                {{
                    0x50, 0xE0, 0xC3, 0x5F, 0xE1, 0x85, 0x1D, 0x56,
                    0xD8, 0x3F, 0xB4, 0xB0, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{476u, 477u, 478u, 479u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 96.
    {
        480u, // center
        {{
            // L0.
            {
                {{
                    0x80, 0x50, 0xF3, 0x6F, 0x61, 0x85, 0x19, 0x72,
                    0x48, 0x7F, 0x70, 0xD0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{481u, 482u, 483u, 484u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 97.
    {
        485u, // center
        {{
            // L0.
            {
                {{
                    0xC4, 0xB0, 0xF1, 0x2F, 0x21, 0x84, 0x18, 0x46,
                    0x78, 0x3F, 0x7C, 0xB0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{486u, 487u, 488u, 489u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 98.
    {
        490u, // center
        {{
            // L0.
            {
                {{
                    0xF8, 0xB0, 0xD1, 0x6F, 0x21, 0x84, 0x18, 0x5E,
                    0x28, 0xBF, 0x40, 0x90, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{491u, 492u, 493u, 494u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 99.
    {
        495u, // center
        {{
            // L0.
            {
                {{
                    0x90, 0x20, 0xE3, 0xFF, 0x61, 0x86, 0x1B, 0x6E,
                    0x28, 0xFF, 0x30, 0x80, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{496u, 497u, 498u, 499u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 100.
    {
        500u, // center
        {{
            // L0.
            {
                {{
                    0x8C, 0xB0, 0xD0, 0xAF, 0x61, 0x84, 0x15, 0x6E,
                    0x48, 0x7F, 0xC4, 0x30, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{501u, 502u, 503u, 504u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 101.
    {
        505u, // center
        {{
            // L0.
            {
                {{
                    0x2C, 0x40, 0xF1, 0x3F, 0xE1, 0x84, 0x19, 0x4A,
                    0x88, 0x3F, 0x5C, 0x50, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{506u, 507u, 508u, 509u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 102.
    {
        510u, // center
        {{
            // L0.
            {
                {{
                    0x84, 0xF0, 0xE2, 0x6F, 0x21, 0x86, 0x17, 0x5E,
                    0x78, 0x3F, 0xC8, 0xB0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{511u, 512u, 513u, 514u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 103.
    {
        515u, // center
        {{
            // L0.
            {
                {{
                    0xB4, 0xA0, 0xC1, 0xAF, 0x21, 0x86, 0x1B, 0x7A,
                    0x78, 0xFF, 0xD8, 0x00, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{516u, 517u, 518u, 519u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 104.
    {
        520u, // center
        {{
            // L0.
            {
                {{
                    0x20, 0x50, 0xC1, 0xFF, 0xE1, 0x87, 0x1C, 0x66,
                    0x38, 0x3F, 0x24, 0x20, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{521u, 522u, 523u, 524u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 105.
    {
        525u, // center
        {{
            // L0.
            {
                {{
                    0x68, 0xC0, 0xE2, 0xBF, 0xE1, 0x84, 0x12, 0x4A,
                    0xA8, 0xFF, 0x94, 0x40, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{526u, 527u, 528u, 529u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 106.
    {
        530u, // center
        {{
            // L0.
            {
                {{
                    0xF4, 0x60, 0xE0, 0xAF, 0xA1, 0x86, 0x14, 0x5A,
                    0x58, 0x3F, 0x94, 0x50, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{531u, 532u, 533u, 534u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 107.
    {
        535u, // center
        {{
            // L0.
            {
                {{
                    0x30, 0xC0, 0xE2, 0x9F, 0x21, 0x86, 0x1E, 0x56,
                    0x68, 0xBF, 0x0C, 0x60, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{536u, 537u, 538u, 539u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 108.
    {
        540u, // center
        {{
            // L0.
            {
                {{
                    0xA4, 0xF0, 0xD0, 0x9F, 0xA1, 0x84, 0x1B, 0x6E,
                    0xA8, 0x7F, 0x18, 0xD0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{541u, 542u, 543u, 544u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 109.
    {
        545u, // center
        {{
            // L0.
            {
                {{
                    0xA0, 0x80, 0xF0, 0x6F, 0x61, 0x84, 0x1A, 0x76,
                    0x98, 0xFF, 0xCC, 0xD0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{546u, 547u, 548u, 549u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 110.
    {
        550u, // center
        {{
            // L0.
            {
                {{
                    0xF0, 0xB0, 0xC3, 0xCF, 0xE1, 0x85, 0x14, 0x7A,
                    0xB8, 0x7F, 0x70, 0x80, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{551u, 552u, 553u, 554u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 111.
    {
        555u, // center
        {{
            // L0.
            {
                {{
                    0xA0, 0x90, 0xC1, 0x0F, 0xA1, 0x86, 0x13, 0x62,
                    0x88, 0xFF, 0xF0, 0xB0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{556u, 557u, 558u, 559u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 112.
    {
        560u, // center
        {{
            // L0.
            {
                {{
                    0x58, 0x60, 0xE3, 0xBF, 0xE1, 0x85, 0x1A, 0x46,
                    0x28, 0x3F, 0x60, 0xB0, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{561u, 562u, 563u, 564u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 113.
    {
        565u, // center
        {{
            // L0.
            {
                {{
                    0x44, 0x40, 0xF2, 0xBF, 0x61, 0x86, 0x16, 0x5A,
                    0x88, 0xBF, 0xE0, 0x10, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{566u, 567u, 568u, 569u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 114.
    {
        570u, // center
        {{
            // L0.
            {
                {{
                    0xE4, 0x30, 0xD2, 0x4F, 0xE1, 0x86, 0x11, 0x5E,
                    0x78, 0xBF, 0x6C, 0x00, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{571u, 572u, 573u, 574u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 115.
    {
        575u, // center
        {{
            // L0.
            {
                {{
                    0x30, 0x10, 0xF1, 0x8F, 0xE1, 0x84, 0x13, 0x76,
                    0x28, 0xBF, 0x78, 0x40, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{576u, 577u, 578u, 579u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 116.
    {
        580u, // center
        {{
            // L0.
            {
                {{
                    0xC8, 0xA0, 0xC1, 0xBF, 0xE1, 0x84, 0x12, 0x72,
                    0x08, 0xFF, 0x30, 0x80, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{581u, 582u, 583u, 584u}} // TL, TR, BR, BL
            }
        }}
    }

};

} // namespace n1_april
} // namespace predef
} // namespace aruco2
} // namespace cv
