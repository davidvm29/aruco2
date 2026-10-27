#pragma once

#include "data.hpp"

namespace cv {
namespace aruco2 {
namespace predef {
namespace n4_mip {

// N4, ArUco MIP 36h12: 14 PRISMarkers.

static constexpr auto type = PRISMA_D4_ARUCO_MIP_36H12;
static constexpr auto aux = DICT_ARUCO_MIP_36h12;
static constexpr char name[] = "PRISMA_D4_ARUCO_MIP_36H12";

using Mark = Marker<4>;

// Array position == PRISMarker ID.
static constexpr Mark markers[] = {

    // PRISMarker 0.
    {
        0u, // center
        {{
            // L0 outer.
            {
                {{
                    0x45, 0x35, 0xC2, 0x4F, 0xA1, 0x84, 0x10, 0x52,
                    0x88, 0xFF, 0xCF, 0x19, 0x04
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{13u, 14u, 15u, 16u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x00, 0x20, 0xD3, 0x5F, 0x21, 0x84, 0x15, 0x7E,
                    0x38, 0xBF, 0xE8, 0x40, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{9u, 10u, 11u, 12u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x01, 0x22, 0xFE, 0x2F, 0x61, 0x84, 0x10, 0x52,
                    0xE8, 0xFF, 0x8A, 0x21, 0x04
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{5u, 6u, 7u, 8u}} // N, E, S, W
            },
            // L3 inner.
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
        17u, // center
        {{
            // L0 outer.
            {
                {{
                    0xCD, 0x11, 0xFC, 0x1F, 0xE1, 0x84, 0x10, 0x62,
                    0xB8, 0x7F, 0x08, 0x01, 0x08
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{30u, 31u, 32u, 33u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0xCC, 0x90, 0xC3, 0x3F, 0x21, 0x86, 0x11, 0x6E,
                    0x08, 0xFF, 0xAC, 0xC0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{26u, 27u, 28u, 29u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x46, 0x3F, 0xDF, 0x6F, 0x61, 0x84, 0x10, 0x42,
                    0x48, 0x7F, 0x43, 0x26, 0x01
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{22u, 23u, 24u, 25u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x58, 0xD0, 0xD0, 0xBF, 0x21, 0x84, 0x1B, 0x76,
                    0x48, 0xFF, 0x84, 0x40, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{18u, 19u, 20u, 21u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 2.
    {
        34u, // center
        {{
            // L0 outer.
            {
                {{
                    0x85, 0x12, 0xE4, 0xFF, 0xE1, 0x84, 0x10, 0x72,
                    0x08, 0x3F, 0x0F, 0x27, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{47u, 48u, 49u, 50u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0xA8, 0x60, 0xE1, 0xDF, 0x61, 0x85, 0x1C, 0x52,
                    0x68, 0x7F, 0x70, 0x80, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{43u, 44u, 45u, 46u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0xC2, 0x2D, 0xD8, 0x7F, 0xA1, 0x84, 0x10, 0x72,
                    0xA8, 0x7F, 0x4D, 0x02, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{39u, 40u, 41u, 42u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x24, 0xF0, 0xE0, 0xCF, 0x61, 0x85, 0x1A, 0x66,
                    0xE8, 0xFF, 0x98, 0x70, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{35u, 36u, 37u, 38u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 3.
    {
        51u, // center
        {{
            // L0 outer.
            {
                {{
                    0x41, 0x0C, 0xF5, 0x0F, 0xA1, 0x84, 0x10, 0x72,
                    0xC8, 0x3F, 0xCB, 0x3C, 0x0A
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{64u, 65u, 66u, 67u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x9C, 0x50, 0xE1, 0x4F, 0x21, 0x87, 0x18, 0x72,
                    0xE8, 0x7F, 0x8C, 0xE0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{60u, 61u, 62u, 63u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x00, 0x3C, 0xD8, 0xFF, 0xE1, 0x84, 0x10, 0x42,
                    0xE8, 0xFF, 0xC7, 0x30, 0x01
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{56u, 57u, 58u, 59u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x20, 0xC0, 0xC2, 0xEF, 0x21, 0x85, 0x17, 0x6E,
                    0xE8, 0xFF, 0xFC, 0x80, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{52u, 53u, 54u, 55u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 4.
    {
        68u, // center
        {{
            // L0 outer.
            {
                {{
                    0x81, 0x06, 0xC6, 0x5F, 0x21, 0x84, 0x10, 0x52,
                    0x78, 0xBF, 0xC7, 0x28, 0x07
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{81u, 82u, 83u, 84u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0xFC, 0xA0, 0xE2, 0x7F, 0x21, 0x84, 0x14, 0x6E,
                    0xB8, 0x3F, 0x34, 0x00, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{77u, 78u, 79u, 80u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x0E, 0x2D, 0xCB, 0x6F, 0x61, 0x84, 0x10, 0x72,
                    0xF8, 0x7F, 0x86, 0x23, 0x04
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{73u, 74u, 75u, 76u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x94, 0xF0, 0xE0, 0x3F, 0x21, 0x87, 0x1D, 0x42,
                    0x58, 0x7F, 0x30, 0x70, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{69u, 70u, 71u, 72u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 5.
    {
        85u, // center
        {{
            // L0 outer.
            {
                {{
                    0x49, 0x35, 0xF2, 0x3F, 0xA1, 0x84, 0x10, 0x62,
                    0x68, 0x3F, 0xCB, 0x11, 0x0C
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{98u, 99u, 100u, 101u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x60, 0x40, 0xF3, 0x7F, 0x21, 0x84, 0x1C, 0x7E,
                    0x98, 0xFF, 0x50, 0x40, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{94u, 95u, 96u, 97u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x89, 0x2D, 0xDB, 0x8F, 0xA1, 0x84, 0x10, 0x62,
                    0x38, 0xBF, 0xC1, 0x09, 0x00
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{90u, 91u, 92u, 93u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x30, 0x80, 0xC0, 0x7F, 0x21, 0x86, 0x1E, 0x46,
                    0xD8, 0x7F, 0x7C, 0x30, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{86u, 87u, 88u, 89u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 6.
    {
        102u, // center
        {{
            // L0 outer.
            {
                {{
                    0x09, 0x11, 0xD5, 0x4F, 0xA1, 0x84, 0x10, 0x72,
                    0xE8, 0xFF, 0x41, 0x2D, 0x0C
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{115u, 116u, 117u, 118u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x14, 0xC0, 0xF2, 0xDF, 0x61, 0x84, 0x10, 0x4E,
                    0x38, 0x7F, 0xE8, 0x10, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{111u, 112u, 113u, 114u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x42, 0x25, 0xFA, 0xBF, 0x61, 0x84, 0x10, 0x72,
                    0xB8, 0xBF, 0x02, 0x06, 0x0B
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{107u, 108u, 109u, 110u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0xD8, 0x80, 0xD1, 0xEF, 0x21, 0x84, 0x1C, 0x6A,
                    0x58, 0x3F, 0x04, 0xF0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{103u, 104u, 105u, 106u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 7.
    {
        119u, // center
        {{
            // L0 outer.
            {
                {{
                    0x4A, 0x35, 0xEA, 0x7F, 0x21, 0x84, 0x10, 0x62,
                    0x48, 0xBF, 0x48, 0x37, 0x01
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{132u, 133u, 134u, 135u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x6C, 0xB0, 0xE2, 0xDF, 0x21, 0x85, 0x1A, 0x4A,
                    0x68, 0xBF, 0x58, 0x80, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{128u, 129u, 130u, 131u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x05, 0x32, 0xF6, 0x6F, 0xE1, 0x84, 0x10, 0x62,
                    0x38, 0xBF, 0x0B, 0x02, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{124u, 125u, 126u, 127u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x0C, 0x30, 0xC0, 0xBF, 0xA1, 0x84, 0x17, 0x4E,
                    0xD8, 0x3F, 0x7C, 0x40, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{120u, 121u, 122u, 123u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 8.
    {
        136u, // center
        {{
            // L0 outer.
            {
                {{
                    0x81, 0x1F, 0xCD, 0xCF, 0xE1, 0x84, 0x10, 0x72,
                    0xF8, 0x3F, 0x01, 0x20, 0x04
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{149u, 150u, 151u, 152u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x04, 0xB0, 0xC0, 0xCF, 0xE1, 0x87, 0x17, 0x42,
                    0xA8, 0x7F, 0x0C, 0x90, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{145u, 146u, 147u, 148u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x0C, 0x11, 0xEF, 0xCF, 0x61, 0x84, 0x10, 0x62,
                    0xC8, 0xBF, 0x06, 0x2E, 0x0E
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{141u, 142u, 143u, 144u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0xA0, 0x50, 0xF0, 0x5F, 0xE1, 0x85, 0x1D, 0x4E,
                    0x38, 0xFF, 0x80, 0x00, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{137u, 138u, 139u, 140u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 9.
    {
        153u, // center
        {{
            // L0 outer.
            {
                {{
                    0xC1, 0x1F, 0xF4, 0xCF, 0x21, 0x84, 0x10, 0x72,
                    0xD8, 0x7F, 0xC2, 0x08, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{166u, 167u, 168u, 169u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x6C, 0x00, 0xC2, 0x5F, 0x61, 0x86, 0x14, 0x5A,
                    0xB8, 0xFF, 0x38, 0x00, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{162u, 163u, 164u, 165u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0xCA, 0x36, 0xC1, 0xEF, 0x61, 0x84, 0x10, 0x52,
                    0x18, 0xFF, 0x04, 0x23, 0x07
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{158u, 159u, 160u, 161u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x58, 0x10, 0xC1, 0x7F, 0x21, 0x87, 0x13, 0x76,
                    0xA8, 0x7F, 0x30, 0x20, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{154u, 155u, 156u, 157u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 10.
    {
        170u, // center
        {{
            // L0 outer.
            {
                {{
                    0x47, 0x35, 0xE7, 0x0F, 0x21, 0x84, 0x10, 0x52,
                    0xF8, 0xFF, 0x06, 0x38, 0x08
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{183u, 184u, 185u, 186u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x1C, 0x80, 0xC2, 0x5F, 0x21, 0x86, 0x1C, 0x52,
                    0xF8, 0xBF, 0xEC, 0xC0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{179u, 180u, 181u, 182u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x05, 0x1D, 0xF6, 0x1F, 0x61, 0x84, 0x10, 0x72,
                    0x78, 0xBF, 0x01, 0x2D, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{175u, 176u, 177u, 178u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x24, 0x10, 0xE3, 0x3F, 0x61, 0x87, 0x17, 0x5A,
                    0xB8, 0x3F, 0x38, 0xE0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{171u, 172u, 173u, 174u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 11.
    {
        187u, // center
        {{
            // L0 outer.
            {
                {{
                    0x4E, 0x29, 0xF4, 0xFF, 0x61, 0x84, 0x10, 0x62,
                    0x18, 0x3F, 0x01, 0x3A, 0x0C
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{200u, 201u, 202u, 203u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0xA4, 0x70, 0xC2, 0xCF, 0xA1, 0x87, 0x17, 0x66,
                    0x48, 0xBF, 0x28, 0x70, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{196u, 197u, 198u, 199u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x0D, 0x2B, 0xE1, 0xAF, 0x61, 0x84, 0x10, 0x42,
                    0x88, 0xBF, 0x8B, 0x2D, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{192u, 193u, 194u, 195u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x6C, 0xC0, 0xF2, 0x6F, 0xE1, 0x85, 0x10, 0x56,
                    0x28, 0x3F, 0xCC, 0x30, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{188u, 189u, 190u, 191u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 12.
    {
        204u, // center
        {{
            // L0 outer.
            {
                {{
                    0x85, 0x02, 0xFB, 0x3F, 0xA1, 0x84, 0x10, 0x52,
                    0xA8, 0xBF, 0xC3, 0x0A, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{217u, 218u, 219u, 220u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0xC8, 0xD0, 0xD3, 0x7F, 0x61, 0x84, 0x14, 0x46,
                    0xD8, 0x7F, 0xE0, 0xC0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{213u, 214u, 215u, 216u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0xC0, 0x37, 0xCC, 0x6F, 0x61, 0x84, 0x10, 0x52,
                    0x98, 0x3F, 0x86, 0x34, 0x0D
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{209u, 210u, 211u, 212u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x34, 0xF0, 0xE2, 0x3F, 0x21, 0x87, 0x12, 0x6E,
                    0x48, 0x7F, 0x24, 0x90, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{205u, 206u, 207u, 208u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 13.
    {
        221u, // center
        {{
            // L0 outer.
            {
                {{
                    0x0E, 0x34, 0xF5, 0x6F, 0x21, 0x84, 0x10, 0x42,
                    0x98, 0x7F, 0xC7, 0x29, 0x01
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{234u, 235u, 236u, 237u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0xCC, 0x20, 0xD2, 0x9F, 0xA1, 0x86, 0x15, 0x7E,
                    0x08, 0x7F, 0xF8, 0x70, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{230u, 231u, 232u, 233u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x0A, 0x04, 0xC6, 0x7F, 0xE1, 0x84, 0x10, 0x62,
                    0xB8, 0x7F, 0x05, 0x35, 0x0B
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{226u, 227u, 228u, 229u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x7C, 0xE0, 0xF1, 0x0F, 0x61, 0x85, 0x16, 0x4E,
                    0x48, 0xFF, 0xCC, 0xE0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{222u, 223u, 224u, 225u}} // TL, TR, BR, BL
            }
        }}
    }

};

} // namespace n4_mip
} // namespace predef
} // namespace aruco2
} // namespace cv
