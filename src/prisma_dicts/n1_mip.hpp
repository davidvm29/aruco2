#pragma once

#include "data.hpp"

namespace cv {
namespace aruco2 {
namespace predef {
namespace n1_mip {

// N1, ArUco MIP 36h12: 50 PRISMarkers.

static constexpr auto type = PRISMA_D1_ARUCO_MIP_36H12;
static constexpr auto aux = DICT_ARUCO_MIP_36h12;
static constexpr char name[] = "PRISMA_D1_ARUCO_MIP_36H12";

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
    }

};

} // namespace n1_mip
} // namespace predef
} // namespace aruco2
} // namespace cv
