#pragma once

#include "data.hpp"

namespace cv {
namespace aruco2 {
namespace predef {
namespace n4_april {

// N4, AprilTag 36h11: 34 PRISMarkers.

static constexpr auto type = PRISMA_D4_APRILTAG_36H11;
static constexpr auto aux = DICT_APRILTAG_36h11;
static constexpr char name[] = "PRISMA_D4_APRILTAG_36H11";

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
                    0x0A, 0x03, 0xD5, 0xDF, 0x21, 0x84, 0x10, 0x72,
                    0x28, 0x3F, 0x4D, 0x19, 0x01
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{13u, 14u, 15u, 16u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x90, 0x00, 0xD1, 0x5F, 0xE1, 0x85, 0x1E, 0x76,
                    0x58, 0x7F, 0x68, 0x20, 0x00
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
                    0x42, 0x35, 0xDF, 0xFF, 0xA1, 0x84, 0x10, 0x72,
                    0x78, 0x3F, 0x00, 0x19, 0x04
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{30u, 31u, 32u, 33u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x54, 0x20, 0xD0, 0x3F, 0xE1, 0x87, 0x1C, 0x56,
                    0x58, 0x7F, 0x18, 0xF0, 0x02
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
                    0x43, 0x17, 0xE1, 0xEF, 0x61, 0x84, 0x10, 0x72,
                    0xA8, 0xBF, 0xC6, 0x01, 0x0D
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{47u, 48u, 49u, 50u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x84, 0x20, 0xC2, 0xFF, 0xA1, 0x84, 0x1C, 0x66,
                    0xE8, 0xFF, 0x64, 0xF0, 0x00
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
                    0xC0, 0x19, 0xC3, 0xAF, 0xE1, 0x84, 0x10, 0x42,
                    0x98, 0x3F, 0x0D, 0x2F, 0x0F
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{64u, 65u, 66u, 67u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x00, 0x00, 0xC3, 0x7F, 0x61, 0x87, 0x1C, 0x6A,
                    0xD8, 0x7F, 0xE4, 0x50, 0x01
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
                    0x4E, 0x02, 0xF1, 0x6F, 0x61, 0x84, 0x10, 0x52,
                    0xF8, 0x3F, 0x02, 0x0E, 0x04
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{81u, 82u, 83u, 84u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x48, 0x30, 0xD2, 0x7F, 0xA1, 0x85, 0x14, 0x6E,
                    0x78, 0x7F, 0x28, 0x50, 0x00
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
                    0xCE, 0x28, 0xD7, 0x9F, 0xE1, 0x84, 0x10, 0x52,
                    0x78, 0xBF, 0xC4, 0x02, 0x04
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{98u, 99u, 100u, 101u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x2C, 0x60, 0xD2, 0xDF, 0xA1, 0x86, 0x10, 0x52,
                    0x18, 0x7F, 0xD0, 0xB0, 0x03
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
                    0x0D, 0x25, 0xE2, 0x1F, 0xE1, 0x84, 0x10, 0x42,
                    0xD8, 0xBF, 0x47, 0x27, 0x0D
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{115u, 116u, 117u, 118u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0xCC, 0x20, 0xE1, 0x2F, 0xE1, 0x86, 0x1A, 0x6A,
                    0x08, 0xBF, 0x84, 0x70, 0x00
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
                    0x0A, 0x29, 0xC8, 0x3F, 0xA1, 0x84, 0x10, 0x52,
                    0x28, 0x7F, 0x0E, 0x1D, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{132u, 133u, 134u, 135u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x38, 0x10, 0xD2, 0x4F, 0xE1, 0x87, 0x1E, 0x4E,
                    0x18, 0xFF, 0x1C, 0x20, 0x02
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
                    0x81, 0x2D, 0xCC, 0xEF, 0x21, 0x84, 0x10, 0x52,
                    0x28, 0xFF, 0x87, 0x04, 0x06
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{149u, 150u, 151u, 152u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0xE0, 0xC0, 0xE2, 0xBF, 0x61, 0x87, 0x1C, 0x62,
                    0xA8, 0xBF, 0x20, 0xC0, 0x02
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
                    0x42, 0x27, 0xE9, 0xCF, 0xE1, 0x84, 0x10, 0x42,
                    0x58, 0xBF, 0xC0, 0x25, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{166u, 167u, 168u, 169u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x14, 0xF0, 0xD2, 0x9F, 0xA1, 0x87, 0x11, 0x46,
                    0x68, 0x3F, 0x8C, 0x20, 0x03
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
                    0x05, 0x04, 0xE4, 0x3F, 0x21, 0x84, 0x10, 0x72,
                    0x08, 0xFF, 0xC9, 0x1B, 0x0B
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{183u, 184u, 185u, 186u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0xF8, 0x10, 0xD3, 0x4F, 0x21, 0x85, 0x1C, 0x62,
                    0x78, 0xBF, 0x7C, 0xC0, 0x02
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
                    0x05, 0x38, 0xE8, 0x7F, 0x21, 0x84, 0x10, 0x72,
                    0x18, 0xBF, 0x48, 0x29, 0x07
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{200u, 201u, 202u, 203u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x80, 0xF0, 0xF1, 0xFF, 0xA1, 0x84, 0x14, 0x76,
                    0x08, 0x7F, 0x90, 0x70, 0x01
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
                    0x03, 0x3F, 0xD4, 0xBF, 0x21, 0x84, 0x10, 0x52,
                    0x58, 0x3F, 0x8D, 0x20, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{217u, 218u, 219u, 220u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x34, 0x10, 0xF3, 0x3F, 0xE1, 0x84, 0x1E, 0x6E,
                    0x28, 0xBF, 0x04, 0xE0, 0x01
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
                    0x84, 0x29, 0xEB, 0xFF, 0xE1, 0x84, 0x10, 0x42,
                    0x48, 0x3F, 0xC2, 0x30, 0x08
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{234u, 235u, 236u, 237u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0xE0, 0xD0, 0xE1, 0x7F, 0x61, 0x86, 0x16, 0x72,
                    0x78, 0xBF, 0x2C, 0x80, 0x00
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
    },

    // PRISMarker 14.
    {
        238u, // center
        {{
            // L0 outer.
            {
                {{
                    0xC1, 0x1C, 0xE0, 0xBF, 0xE1, 0x84, 0x10, 0x52,
                    0x38, 0x3F, 0x46, 0x34, 0x0B
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{251u, 252u, 253u, 254u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x28, 0xC0, 0xF0, 0x8F, 0x61, 0x84, 0x14, 0x7A,
                    0xE8, 0xFF, 0xE4, 0x70, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{247u, 248u, 249u, 250u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x49, 0x06, 0xD3, 0x2F, 0x61, 0x84, 0x10, 0x62,
                    0xB8, 0xFF, 0x07, 0x17, 0x04
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{243u, 244u, 245u, 246u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0xC0, 0x50, 0xE2, 0xAF, 0xE1, 0x84, 0x1A, 0x5E,
                    0xF8, 0xBF, 0x70, 0xC0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{239u, 240u, 241u, 242u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 15.
    {
        255u, // center
        {{
            // L0 outer.
            {
                {{
                    0xCF, 0x1D, 0xF2, 0x8F, 0x21, 0x84, 0x10, 0x72,
                    0x88, 0x3F, 0x47, 0x3D, 0x00
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{268u, 269u, 270u, 271u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x40, 0x20, 0xE1, 0x7F, 0xE1, 0x85, 0x1A, 0x4A,
                    0xC8, 0x7F, 0x34, 0x30, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{264u, 265u, 266u, 267u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x05, 0x1E, 0xFD, 0x5F, 0xE1, 0x84, 0x10, 0x52,
                    0x18, 0xBF, 0x8D, 0x38, 0x00
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{260u, 261u, 262u, 263u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0xE0, 0x60, 0xE1, 0x0F, 0xA1, 0x86, 0x1A, 0x66,
                    0x48, 0xBF, 0xB8, 0xD0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{256u, 257u, 258u, 259u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 16.
    {
        272u, // center
        {{
            // L0 outer.
            {
                {{
                    0xC2, 0x09, 0xEE, 0xAF, 0x61, 0x84, 0x10, 0x52,
                    0xD8, 0xFF, 0xC2, 0x34, 0x01
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{285u, 286u, 287u, 288u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x30, 0xA0, 0xF0, 0xEF, 0xE1, 0x86, 0x15, 0x5A,
                    0xF8, 0x3F, 0xC8, 0x40, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{281u, 282u, 283u, 284u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x86, 0x17, 0xD5, 0xAF, 0xE1, 0x84, 0x10, 0x62,
                    0x18, 0x7F, 0x81, 0x23, 0x0A
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{277u, 278u, 279u, 280u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0xC0, 0x70, 0xC0, 0xDF, 0xE1, 0x87, 0x13, 0x52,
                    0x38, 0xFF, 0xD0, 0xD0, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{273u, 274u, 275u, 276u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 17.
    {
        289u, // center
        {{
            // L0 outer.
            {
                {{
                    0x49, 0x1C, 0xCF, 0x3F, 0xE1, 0x84, 0x10, 0x52,
                    0xC8, 0xFF, 0xC2, 0x2C, 0x00
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{302u, 303u, 304u, 305u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0xF0, 0xA0, 0xF0, 0xFF, 0xE1, 0x86, 0x18, 0x6E,
                    0x28, 0xBF, 0x84, 0x80, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{298u, 299u, 300u, 301u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x41, 0x29, 0xF9, 0xBF, 0x61, 0x84, 0x10, 0x42,
                    0xB8, 0x7F, 0xC4, 0x13, 0x0B
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{294u, 295u, 296u, 297u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0xB8, 0xB0, 0xF2, 0x3F, 0x21, 0x87, 0x1F, 0x6A,
                    0x98, 0x3F, 0x08, 0x20, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{290u, 291u, 292u, 293u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 18.
    {
        306u, // center
        {{
            // L0 outer.
            {
                {{
                    0xC7, 0x35, 0xE3, 0x3F, 0x21, 0x84, 0x10, 0x72,
                    0x88, 0x7F, 0x40, 0x01, 0x08
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{319u, 320u, 321u, 322u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x8C, 0x00, 0xC3, 0x7F, 0xA1, 0x87, 0x1B, 0x46,
                    0xD8, 0xFF, 0x44, 0xA0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{315u, 316u, 317u, 318u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0xCA, 0x2E, 0xF9, 0x5F, 0x61, 0x84, 0x10, 0x52,
                    0x98, 0x7F, 0x47, 0x05, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{311u, 312u, 313u, 314u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0xE0, 0xD0, 0xC0, 0x9F, 0x21, 0x87, 0x17, 0x52,
                    0x58, 0x3F, 0x5C, 0x60, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{307u, 308u, 309u, 310u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 19.
    {
        323u, // center
        {{
            // L0 outer.
            {
                {{
                    0x85, 0x16, 0xD6, 0x7F, 0x61, 0x84, 0x10, 0x72,
                    0xE8, 0x3F, 0x4B, 0x0B, 0x09
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{336u, 337u, 338u, 339u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x7C, 0x90, 0xC1, 0x8F, 0x61, 0x86, 0x10, 0x72,
                    0xA8, 0xFF, 0x20, 0xC0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{332u, 333u, 334u, 335u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0xC7, 0x16, 0xE2, 0xCF, 0x21, 0x84, 0x10, 0x62,
                    0xC8, 0x7F, 0xCA, 0x27, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{328u, 329u, 330u, 331u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0xB0, 0x70, 0xC3, 0xAF, 0x61, 0x86, 0x18, 0x72,
                    0xF8, 0xFF, 0x14, 0xB0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{324u, 325u, 326u, 327u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 20.
    {
        340u, // center
        {{
            // L0 outer.
            {
                {{
                    0x86, 0x12, 0xD6, 0xEF, 0x21, 0x84, 0x10, 0x72,
                    0x38, 0x3F, 0x0C, 0x2C, 0x0B
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{353u, 354u, 355u, 356u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0xF0, 0x90, 0xD3, 0x3F, 0xE1, 0x86, 0x17, 0x52,
                    0xB8, 0xBF, 0x98, 0x40, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{349u, 350u, 351u, 352u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0xC9, 0x3B, 0xC3, 0x9F, 0x21, 0x84, 0x10, 0x72,
                    0x88, 0x3F, 0x01, 0x21, 0x07
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{345u, 346u, 347u, 348u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x2C, 0xA0, 0xF3, 0x4F, 0xA1, 0x87, 0x1E, 0x42,
                    0x98, 0xBF, 0x28, 0x70, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{341u, 342u, 343u, 344u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 21.
    {
        357u, // center
        {{
            // L0 outer.
            {
                {{
                    0x89, 0x07, 0xDF, 0xAF, 0x21, 0x84, 0x10, 0x62,
                    0x68, 0x3F, 0x44, 0x29, 0x0F
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{370u, 371u, 372u, 373u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x84, 0x50, 0xD3, 0xBF, 0xA1, 0x85, 0x1E, 0x46,
                    0x38, 0x3F, 0xCC, 0xC0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{366u, 367u, 368u, 369u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x43, 0x2A, 0xDB, 0x2F, 0xA1, 0x84, 0x10, 0x72,
                    0x78, 0x7F, 0xC6, 0x3A, 0x00
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{362u, 363u, 364u, 365u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x6C, 0xF0, 0xF1, 0xAF, 0x21, 0x87, 0x14, 0x66,
                    0x38, 0x3F, 0xA0, 0xB0, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{358u, 359u, 360u, 361u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 22.
    {
        374u, // center
        {{
            // L0 outer.
            {
                {{
                    0x86, 0x22, 0xEF, 0xBF, 0x61, 0x84, 0x10, 0x52,
                    0xA8, 0x3F, 0x04, 0x29, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{387u, 388u, 389u, 390u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0xE0, 0xB0, 0xF1, 0xDF, 0x21, 0x84, 0x1E, 0x7A,
                    0x18, 0x7F, 0x68, 0x40, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{383u, 384u, 385u, 386u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x89, 0x0A, 0xF7, 0x9F, 0x21, 0x84, 0x10, 0x62,
                    0xF8, 0x3F, 0x01, 0x1A, 0x0B
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{379u, 380u, 381u, 382u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x0C, 0xA0, 0xD2, 0x1F, 0x21, 0x85, 0x17, 0x5E,
                    0x68, 0x7F, 0xE0, 0x10, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{375u, 376u, 377u, 378u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 23.
    {
        391u, // center
        {{
            // L0 outer.
            {
                {{
                    0xC3, 0x26, 0xE7, 0x4F, 0xA1, 0x84, 0x10, 0x42,
                    0xC8, 0xBF, 0x83, 0x24, 0x01
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{404u, 405u, 406u, 407u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x3C, 0x40, 0xE2, 0x3F, 0xE1, 0x87, 0x13, 0x52,
                    0x98, 0x7F, 0x20, 0x30, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{400u, 401u, 402u, 403u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0xC2, 0x10, 0xF3, 0x1F, 0x21, 0x84, 0x10, 0x72,
                    0xC8, 0xBF, 0x49, 0x2D, 0x0F
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{396u, 397u, 398u, 399u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0xE0, 0xA0, 0xD0, 0xAF, 0xA1, 0x85, 0x17, 0x76,
                    0xB8, 0xFF, 0xC0, 0x80, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{392u, 393u, 394u, 395u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 24.
    {
        408u, // center
        {{
            // L0 outer.
            {
                {{
                    0x87, 0x2B, 0xD0, 0x9F, 0x21, 0x84, 0x10, 0x52,
                    0x68, 0x3F, 0x44, 0x0E, 0x03
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{421u, 422u, 423u, 424u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x6C, 0x00, 0xF2, 0x9F, 0x21, 0x85, 0x1A, 0x5E,
                    0x98, 0x3F, 0xAC, 0x30, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{417u, 418u, 419u, 420u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x02, 0x03, 0xF9, 0x2F, 0xA1, 0x84, 0x10, 0x42,
                    0x38, 0xBF, 0x86, 0x2D, 0x07
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{413u, 414u, 415u, 416u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0xA0, 0x90, 0xC3, 0x0F, 0x61, 0x84, 0x1F, 0x76,
                    0xF8, 0xBF, 0x64, 0x20, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{409u, 410u, 411u, 412u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 25.
    {
        425u, // center
        {{
            // L0 outer.
            {
                {{
                    0x88, 0x2D, 0xD1, 0xFF, 0x21, 0x84, 0x10, 0x62,
                    0x98, 0x7F, 0x80, 0x35, 0x0C
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{438u, 439u, 440u, 441u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x54, 0xB0, 0xC3, 0x4F, 0x21, 0x85, 0x1B, 0x72,
                    0x78, 0x3F, 0xB8, 0x60, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{434u, 435u, 436u, 437u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x0B, 0x20, 0xF6, 0x7F, 0x21, 0x84, 0x10, 0x72,
                    0xA8, 0x3F, 0x08, 0x0F, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{430u, 431u, 432u, 433u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x20, 0xA0, 0xD3, 0xBF, 0xA1, 0x85, 0x1B, 0x7A,
                    0xA8, 0x3F, 0xB4, 0x10, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{426u, 427u, 428u, 429u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 26.
    {
        442u, // center
        {{
            // L0 outer.
            {
                {{
                    0x4C, 0x0B, 0xFD, 0xDF, 0xA1, 0x84, 0x10, 0x42,
                    0xC8, 0xBF, 0xC0, 0x02, 0x09
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{455u, 456u, 457u, 458u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x50, 0x20, 0xF0, 0x7F, 0xE1, 0x85, 0x17, 0x62,
                    0x78, 0x7F, 0x1C, 0x80, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{451u, 452u, 453u, 454u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x0A, 0x17, 0xFC, 0x9F, 0x61, 0x84, 0x10, 0x52,
                    0xD8, 0xFF, 0x41, 0x21, 0x08
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{447u, 448u, 449u, 450u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x78, 0xE0, 0xD2, 0x2F, 0xA1, 0x84, 0x1D, 0x42,
                    0x18, 0x7F, 0xC8, 0x50, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{443u, 444u, 445u, 446u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 27.
    {
        459u, // center
        {{
            // L0 outer.
            {
                {{
                    0x0D, 0x3D, 0xE1, 0xEF, 0xA1, 0x84, 0x10, 0x62,
                    0x18, 0xBF, 0xC7, 0x06, 0x01
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{472u, 473u, 474u, 475u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x88, 0x50, 0xC3, 0x6F, 0xA1, 0x84, 0x1B, 0x66,
                    0x58, 0x3F, 0x7C, 0x70, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{468u, 469u, 470u, 471u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x45, 0x35, 0xC2, 0x4F, 0xA1, 0x84, 0x10, 0x52,
                    0x88, 0xFF, 0xCF, 0x19, 0x04
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{464u, 465u, 466u, 467u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x00, 0x20, 0xD3, 0x5F, 0x21, 0x84, 0x15, 0x7E,
                    0x38, 0xBF, 0xE8, 0x40, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{460u, 461u, 462u, 463u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 28.
    {
        476u, // center
        {{
            // L0 outer.
            {
                {{
                    0x4B, 0x23, 0xE1, 0xBF, 0xA1, 0x84, 0x10, 0x62,
                    0x28, 0xFF, 0x00, 0x3D, 0x0E
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{489u, 490u, 491u, 492u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0xC8, 0x30, 0xD1, 0xCF, 0xE1, 0x87, 0x1E, 0x7E,
                    0xA8, 0x7F, 0x04, 0xA0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{485u, 486u, 487u, 488u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0xCD, 0x11, 0xFC, 0x1F, 0xE1, 0x84, 0x10, 0x62,
                    0xB8, 0x7F, 0x08, 0x01, 0x08
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{481u, 482u, 483u, 484u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0xCC, 0x90, 0xC3, 0x3F, 0x21, 0x86, 0x11, 0x6E,
                    0x08, 0xFF, 0xAC, 0xC0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{477u, 478u, 479u, 480u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 29.
    {
        493u, // center
        {{
            // L0 outer.
            {
                {{
                    0xC7, 0x02, 0xDF, 0x4F, 0xE1, 0x84, 0x10, 0x62,
                    0x08, 0x3F, 0x46, 0x0A, 0x07
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{506u, 507u, 508u, 509u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0xE0, 0x00, 0xE2, 0xCF, 0xE1, 0x87, 0x11, 0x62,
                    0x48, 0x7F, 0xB4, 0x30, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{502u, 503u, 504u, 505u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x85, 0x12, 0xE4, 0xFF, 0xE1, 0x84, 0x10, 0x72,
                    0x08, 0x3F, 0x0F, 0x27, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{498u, 499u, 500u, 501u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0xA8, 0x60, 0xE1, 0xDF, 0x61, 0x85, 0x1C, 0x52,
                    0x68, 0x7F, 0x70, 0x80, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{494u, 495u, 496u, 497u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 30.
    {
        510u, // center
        {{
            // L0 outer.
            {
                {{
                    0x8F, 0x06, 0xEC, 0x4F, 0xA1, 0x84, 0x10, 0x72,
                    0xF8, 0x3F, 0x06, 0x39, 0x00
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{523u, 524u, 525u, 526u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x50, 0xE0, 0xC3, 0x5F, 0xE1, 0x85, 0x1D, 0x56,
                    0xD8, 0x3F, 0xB4, 0xB0, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{519u, 520u, 521u, 522u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x41, 0x0C, 0xF5, 0x0F, 0xA1, 0x84, 0x10, 0x72,
                    0xC8, 0x3F, 0xCB, 0x3C, 0x0A
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{515u, 516u, 517u, 518u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x9C, 0x50, 0xE1, 0x4F, 0x21, 0x87, 0x18, 0x72,
                    0xE8, 0x7F, 0x8C, 0xE0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{511u, 512u, 513u, 514u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 31.
    {
        527u, // center
        {{
            // L0 outer.
            {
                {{
                    0xCE, 0x01, 0xFC, 0x5F, 0x61, 0x84, 0x10, 0x42,
                    0x58, 0x3F, 0xC6, 0x2E, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{540u, 541u, 542u, 543u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0x80, 0x50, 0xF3, 0x6F, 0x61, 0x85, 0x19, 0x72,
                    0x48, 0x7F, 0x70, 0xD0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{536u, 537u, 538u, 539u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x81, 0x06, 0xC6, 0x5F, 0x21, 0x84, 0x10, 0x52,
                    0x78, 0xBF, 0xC7, 0x28, 0x07
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{532u, 533u, 534u, 535u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0xFC, 0xA0, 0xE2, 0x7F, 0x21, 0x84, 0x14, 0x6E,
                    0xB8, 0x3F, 0x34, 0x00, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{528u, 529u, 530u, 531u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 32.
    {
        544u, // center
        {{
            // L0 outer.
            {
                {{
                    0x4F, 0x2F, 0xDF, 0xDF, 0xE1, 0x84, 0x10, 0x52,
                    0x08, 0x3F, 0x00, 0x07, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{557u, 558u, 559u, 560u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0xC4, 0xB0, 0xF1, 0x2F, 0x21, 0x84, 0x18, 0x46,
                    0x78, 0x3F, 0x7C, 0xB0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{553u, 554u, 555u, 556u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x49, 0x35, 0xF2, 0x3F, 0xA1, 0x84, 0x10, 0x62,
                    0x68, 0x3F, 0xCB, 0x11, 0x0C
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{549u, 550u, 551u, 552u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x60, 0x40, 0xF3, 0x7F, 0x21, 0x84, 0x1C, 0x7E,
                    0x98, 0xFF, 0x50, 0x40, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{545u, 546u, 547u, 548u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 33.
    {
        561u, // center
        {{
            // L0 outer.
            {
                {{
                    0x06, 0x3B, 0xF5, 0xCF, 0xA1, 0x84, 0x10, 0x72,
                    0x08, 0xBF, 0x82, 0x31, 0x08
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{574u, 575u, 576u, 577u}} // N, E, S, W
            },
            // L1.
            {
                {{
                    0xF8, 0xB0, 0xD1, 0x6F, 0x21, 0x84, 0x18, 0x5E,
                    0x28, 0xBF, 0x40, 0x90, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{570u, 571u, 572u, 573u}} // TL, TR, BR, BL
            },
            // L2.
            {
                {{
                    0x09, 0x11, 0xD5, 0x4F, 0xA1, 0x84, 0x10, 0x72,
                    0xE8, 0xFF, 0x41, 0x2D, 0x0C
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{566u, 567u, 568u, 569u}} // N, E, S, W
            },
            // L3 inner.
            {
                {{
                    0x14, 0xC0, 0xF2, 0xDF, 0x61, 0x84, 0x10, 0x4E,
                    0x38, 0x7F, 0xE8, 0x10, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{562u, 563u, 564u, 565u}} // TL, TR, BR, BL
            }
        }}
    }

};

} // namespace n4_april
} // namespace predef
} // namespace aruco2
} // namespace cv
