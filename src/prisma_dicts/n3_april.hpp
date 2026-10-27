#pragma once

#include "data.hpp"

namespace cv {
namespace aruco2 {
namespace predef {
namespace n3_april {

// N3, AprilTag 36h11: 45 PRISMarkers.

static constexpr auto type = PRISMA_D3_APRILTAG_36H11;
static constexpr auto aux = DICT_APRILTAG_36h11;
static constexpr char name[] = "PRISMA_D3_APRILTAG_36H11";

using Mark = Marker<3>;

// Array position == PRISMarker ID.
static constexpr Mark markers[] = {

    // PRISMarker 0.
    {
        0u, // center
        {{
            // L0 outer.
            {
                {{
                    0x90, 0x00, 0xD1, 0x5F, 0xE1, 0x85, 0x1E, 0x76,
                    0x58, 0x7F, 0x68, 0x20, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{9u, 10u, 11u, 12u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x01, 0x22, 0xFE, 0x2F, 0x61, 0x84, 0x10, 0x52,
                    0xE8, 0xFF, 0x8A, 0x21, 0x04
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{5u, 6u, 7u, 8u}} // N, E, S, W
            },
            // L2 inner.
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
        13u, // center
        {{
            // L0 outer.
            {
                {{
                    0x54, 0x20, 0xD0, 0x3F, 0xE1, 0x87, 0x1C, 0x56,
                    0x58, 0x7F, 0x18, 0xF0, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{22u, 23u, 24u, 25u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x46, 0x3F, 0xDF, 0x6F, 0x61, 0x84, 0x10, 0x42,
                    0x48, 0x7F, 0x43, 0x26, 0x01
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{18u, 19u, 20u, 21u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x58, 0xD0, 0xD0, 0xBF, 0x21, 0x84, 0x1B, 0x76,
                    0x48, 0xFF, 0x84, 0x40, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{14u, 15u, 16u, 17u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 2.
    {
        26u, // center
        {{
            // L0 outer.
            {
                {{
                    0x84, 0x20, 0xC2, 0xFF, 0xA1, 0x84, 0x1C, 0x66,
                    0xE8, 0xFF, 0x64, 0xF0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{35u, 36u, 37u, 38u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0xC2, 0x2D, 0xD8, 0x7F, 0xA1, 0x84, 0x10, 0x72,
                    0xA8, 0x7F, 0x4D, 0x02, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{31u, 32u, 33u, 34u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x24, 0xF0, 0xE0, 0xCF, 0x61, 0x85, 0x1A, 0x66,
                    0xE8, 0xFF, 0x98, 0x70, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{27u, 28u, 29u, 30u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 3.
    {
        39u, // center
        {{
            // L0 outer.
            {
                {{
                    0x00, 0x00, 0xC3, 0x7F, 0x61, 0x87, 0x1C, 0x6A,
                    0xD8, 0x7F, 0xE4, 0x50, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{48u, 49u, 50u, 51u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x00, 0x3C, 0xD8, 0xFF, 0xE1, 0x84, 0x10, 0x42,
                    0xE8, 0xFF, 0xC7, 0x30, 0x01
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{44u, 45u, 46u, 47u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x20, 0xC0, 0xC2, 0xEF, 0x21, 0x85, 0x17, 0x6E,
                    0xE8, 0xFF, 0xFC, 0x80, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{40u, 41u, 42u, 43u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 4.
    {
        52u, // center
        {{
            // L0 outer.
            {
                {{
                    0x48, 0x30, 0xD2, 0x7F, 0xA1, 0x85, 0x14, 0x6E,
                    0x78, 0x7F, 0x28, 0x50, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{61u, 62u, 63u, 64u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x0E, 0x2D, 0xCB, 0x6F, 0x61, 0x84, 0x10, 0x72,
                    0xF8, 0x7F, 0x86, 0x23, 0x04
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{57u, 58u, 59u, 60u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x94, 0xF0, 0xE0, 0x3F, 0x21, 0x87, 0x1D, 0x42,
                    0x58, 0x7F, 0x30, 0x70, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{53u, 54u, 55u, 56u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 5.
    {
        65u, // center
        {{
            // L0 outer.
            {
                {{
                    0x2C, 0x60, 0xD2, 0xDF, 0xA1, 0x86, 0x10, 0x52,
                    0x18, 0x7F, 0xD0, 0xB0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{74u, 75u, 76u, 77u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x89, 0x2D, 0xDB, 0x8F, 0xA1, 0x84, 0x10, 0x62,
                    0x38, 0xBF, 0xC1, 0x09, 0x00
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{70u, 71u, 72u, 73u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x30, 0x80, 0xC0, 0x7F, 0x21, 0x86, 0x1E, 0x46,
                    0xD8, 0x7F, 0x7C, 0x30, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{66u, 67u, 68u, 69u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 6.
    {
        78u, // center
        {{
            // L0 outer.
            {
                {{
                    0xCC, 0x20, 0xE1, 0x2F, 0xE1, 0x86, 0x1A, 0x6A,
                    0x08, 0xBF, 0x84, 0x70, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{87u, 88u, 89u, 90u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x42, 0x25, 0xFA, 0xBF, 0x61, 0x84, 0x10, 0x72,
                    0xB8, 0xBF, 0x02, 0x06, 0x0B
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{83u, 84u, 85u, 86u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0xD8, 0x80, 0xD1, 0xEF, 0x21, 0x84, 0x1C, 0x6A,
                    0x58, 0x3F, 0x04, 0xF0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{79u, 80u, 81u, 82u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 7.
    {
        91u, // center
        {{
            // L0 outer.
            {
                {{
                    0x38, 0x10, 0xD2, 0x4F, 0xE1, 0x87, 0x1E, 0x4E,
                    0x18, 0xFF, 0x1C, 0x20, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{100u, 101u, 102u, 103u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x05, 0x32, 0xF6, 0x6F, 0xE1, 0x84, 0x10, 0x62,
                    0x38, 0xBF, 0x0B, 0x02, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{96u, 97u, 98u, 99u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x0C, 0x30, 0xC0, 0xBF, 0xA1, 0x84, 0x17, 0x4E,
                    0xD8, 0x3F, 0x7C, 0x40, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{92u, 93u, 94u, 95u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 8.
    {
        104u, // center
        {{
            // L0 outer.
            {
                {{
                    0xE0, 0xC0, 0xE2, 0xBF, 0x61, 0x87, 0x1C, 0x62,
                    0xA8, 0xBF, 0x20, 0xC0, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{113u, 114u, 115u, 116u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x0C, 0x11, 0xEF, 0xCF, 0x61, 0x84, 0x10, 0x62,
                    0xC8, 0xBF, 0x06, 0x2E, 0x0E
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{109u, 110u, 111u, 112u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0xA0, 0x50, 0xF0, 0x5F, 0xE1, 0x85, 0x1D, 0x4E,
                    0x38, 0xFF, 0x80, 0x00, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{105u, 106u, 107u, 108u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 9.
    {
        117u, // center
        {{
            // L0 outer.
            {
                {{
                    0x14, 0xF0, 0xD2, 0x9F, 0xA1, 0x87, 0x11, 0x46,
                    0x68, 0x3F, 0x8C, 0x20, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{126u, 127u, 128u, 129u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0xCA, 0x36, 0xC1, 0xEF, 0x61, 0x84, 0x10, 0x52,
                    0x18, 0xFF, 0x04, 0x23, 0x07
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{122u, 123u, 124u, 125u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x58, 0x10, 0xC1, 0x7F, 0x21, 0x87, 0x13, 0x76,
                    0xA8, 0x7F, 0x30, 0x20, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{118u, 119u, 120u, 121u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 10.
    {
        130u, // center
        {{
            // L0 outer.
            {
                {{
                    0xF8, 0x10, 0xD3, 0x4F, 0x21, 0x85, 0x1C, 0x62,
                    0x78, 0xBF, 0x7C, 0xC0, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{139u, 140u, 141u, 142u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x05, 0x1D, 0xF6, 0x1F, 0x61, 0x84, 0x10, 0x72,
                    0x78, 0xBF, 0x01, 0x2D, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{135u, 136u, 137u, 138u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x24, 0x10, 0xE3, 0x3F, 0x61, 0x87, 0x17, 0x5A,
                    0xB8, 0x3F, 0x38, 0xE0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{131u, 132u, 133u, 134u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 11.
    {
        143u, // center
        {{
            // L0 outer.
            {
                {{
                    0x80, 0xF0, 0xF1, 0xFF, 0xA1, 0x84, 0x14, 0x76,
                    0x08, 0x7F, 0x90, 0x70, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{152u, 153u, 154u, 155u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x0D, 0x2B, 0xE1, 0xAF, 0x61, 0x84, 0x10, 0x42,
                    0x88, 0xBF, 0x8B, 0x2D, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{148u, 149u, 150u, 151u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x6C, 0xC0, 0xF2, 0x6F, 0xE1, 0x85, 0x10, 0x56,
                    0x28, 0x3F, 0xCC, 0x30, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{144u, 145u, 146u, 147u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 12.
    {
        156u, // center
        {{
            // L0 outer.
            {
                {{
                    0x34, 0x10, 0xF3, 0x3F, 0xE1, 0x84, 0x1E, 0x6E,
                    0x28, 0xBF, 0x04, 0xE0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{165u, 166u, 167u, 168u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0xC0, 0x37, 0xCC, 0x6F, 0x61, 0x84, 0x10, 0x52,
                    0x98, 0x3F, 0x86, 0x34, 0x0D
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{161u, 162u, 163u, 164u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x34, 0xF0, 0xE2, 0x3F, 0x21, 0x87, 0x12, 0x6E,
                    0x48, 0x7F, 0x24, 0x90, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{157u, 158u, 159u, 160u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 13.
    {
        169u, // center
        {{
            // L0 outer.
            {
                {{
                    0xE0, 0xD0, 0xE1, 0x7F, 0x61, 0x86, 0x16, 0x72,
                    0x78, 0xBF, 0x2C, 0x80, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{178u, 179u, 180u, 181u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x0A, 0x04, 0xC6, 0x7F, 0xE1, 0x84, 0x10, 0x62,
                    0xB8, 0x7F, 0x05, 0x35, 0x0B
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{174u, 175u, 176u, 177u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x7C, 0xE0, 0xF1, 0x0F, 0x61, 0x85, 0x16, 0x4E,
                    0x48, 0xFF, 0xCC, 0xE0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{170u, 171u, 172u, 173u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 14.
    {
        182u, // center
        {{
            // L0 outer.
            {
                {{
                    0x28, 0xC0, 0xF0, 0x8F, 0x61, 0x84, 0x14, 0x7A,
                    0xE8, 0xFF, 0xE4, 0x70, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{191u, 192u, 193u, 194u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x49, 0x06, 0xD3, 0x2F, 0x61, 0x84, 0x10, 0x62,
                    0xB8, 0xFF, 0x07, 0x17, 0x04
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{187u, 188u, 189u, 190u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0xC0, 0x50, 0xE2, 0xAF, 0xE1, 0x84, 0x1A, 0x5E,
                    0xF8, 0xBF, 0x70, 0xC0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{183u, 184u, 185u, 186u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 15.
    {
        195u, // center
        {{
            // L0 outer.
            {
                {{
                    0x40, 0x20, 0xE1, 0x7F, 0xE1, 0x85, 0x1A, 0x4A,
                    0xC8, 0x7F, 0x34, 0x30, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{204u, 205u, 206u, 207u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x05, 0x1E, 0xFD, 0x5F, 0xE1, 0x84, 0x10, 0x52,
                    0x18, 0xBF, 0x8D, 0x38, 0x00
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{200u, 201u, 202u, 203u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0xE0, 0x60, 0xE1, 0x0F, 0xA1, 0x86, 0x1A, 0x66,
                    0x48, 0xBF, 0xB8, 0xD0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{196u, 197u, 198u, 199u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 16.
    {
        208u, // center
        {{
            // L0 outer.
            {
                {{
                    0x30, 0xA0, 0xF0, 0xEF, 0xE1, 0x86, 0x15, 0x5A,
                    0xF8, 0x3F, 0xC8, 0x40, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{217u, 218u, 219u, 220u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x86, 0x17, 0xD5, 0xAF, 0xE1, 0x84, 0x10, 0x62,
                    0x18, 0x7F, 0x81, 0x23, 0x0A
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{213u, 214u, 215u, 216u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0xC0, 0x70, 0xC0, 0xDF, 0xE1, 0x87, 0x13, 0x52,
                    0x38, 0xFF, 0xD0, 0xD0, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{209u, 210u, 211u, 212u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 17.
    {
        221u, // center
        {{
            // L0 outer.
            {
                {{
                    0xF0, 0xA0, 0xF0, 0xFF, 0xE1, 0x86, 0x18, 0x6E,
                    0x28, 0xBF, 0x84, 0x80, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{230u, 231u, 232u, 233u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x41, 0x29, 0xF9, 0xBF, 0x61, 0x84, 0x10, 0x42,
                    0xB8, 0x7F, 0xC4, 0x13, 0x0B
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{226u, 227u, 228u, 229u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0xB8, 0xB0, 0xF2, 0x3F, 0x21, 0x87, 0x1F, 0x6A,
                    0x98, 0x3F, 0x08, 0x20, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{222u, 223u, 224u, 225u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 18.
    {
        234u, // center
        {{
            // L0 outer.
            {
                {{
                    0x8C, 0x00, 0xC3, 0x7F, 0xA1, 0x87, 0x1B, 0x46,
                    0xD8, 0xFF, 0x44, 0xA0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{243u, 244u, 245u, 246u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0xCA, 0x2E, 0xF9, 0x5F, 0x61, 0x84, 0x10, 0x52,
                    0x98, 0x7F, 0x47, 0x05, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{239u, 240u, 241u, 242u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0xE0, 0xD0, 0xC0, 0x9F, 0x21, 0x87, 0x17, 0x52,
                    0x58, 0x3F, 0x5C, 0x60, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{235u, 236u, 237u, 238u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 19.
    {
        247u, // center
        {{
            // L0 outer.
            {
                {{
                    0x7C, 0x90, 0xC1, 0x8F, 0x61, 0x86, 0x10, 0x72,
                    0xA8, 0xFF, 0x20, 0xC0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{256u, 257u, 258u, 259u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0xC7, 0x16, 0xE2, 0xCF, 0x21, 0x84, 0x10, 0x62,
                    0xC8, 0x7F, 0xCA, 0x27, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{252u, 253u, 254u, 255u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0xB0, 0x70, 0xC3, 0xAF, 0x61, 0x86, 0x18, 0x72,
                    0xF8, 0xFF, 0x14, 0xB0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{248u, 249u, 250u, 251u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 20.
    {
        260u, // center
        {{
            // L0 outer.
            {
                {{
                    0xF0, 0x90, 0xD3, 0x3F, 0xE1, 0x86, 0x17, 0x52,
                    0xB8, 0xBF, 0x98, 0x40, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{269u, 270u, 271u, 272u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0xC9, 0x3B, 0xC3, 0x9F, 0x21, 0x84, 0x10, 0x72,
                    0x88, 0x3F, 0x01, 0x21, 0x07
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{265u, 266u, 267u, 268u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x2C, 0xA0, 0xF3, 0x4F, 0xA1, 0x87, 0x1E, 0x42,
                    0x98, 0xBF, 0x28, 0x70, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{261u, 262u, 263u, 264u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 21.
    {
        273u, // center
        {{
            // L0 outer.
            {
                {{
                    0x84, 0x50, 0xD3, 0xBF, 0xA1, 0x85, 0x1E, 0x46,
                    0x38, 0x3F, 0xCC, 0xC0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{282u, 283u, 284u, 285u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x43, 0x2A, 0xDB, 0x2F, 0xA1, 0x84, 0x10, 0x72,
                    0x78, 0x7F, 0xC6, 0x3A, 0x00
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{278u, 279u, 280u, 281u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x6C, 0xF0, 0xF1, 0xAF, 0x21, 0x87, 0x14, 0x66,
                    0x38, 0x3F, 0xA0, 0xB0, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{274u, 275u, 276u, 277u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 22.
    {
        286u, // center
        {{
            // L0 outer.
            {
                {{
                    0xE0, 0xB0, 0xF1, 0xDF, 0x21, 0x84, 0x1E, 0x7A,
                    0x18, 0x7F, 0x68, 0x40, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{295u, 296u, 297u, 298u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x89, 0x0A, 0xF7, 0x9F, 0x21, 0x84, 0x10, 0x62,
                    0xF8, 0x3F, 0x01, 0x1A, 0x0B
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{291u, 292u, 293u, 294u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x0C, 0xA0, 0xD2, 0x1F, 0x21, 0x85, 0x17, 0x5E,
                    0x68, 0x7F, 0xE0, 0x10, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{287u, 288u, 289u, 290u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 23.
    {
        299u, // center
        {{
            // L0 outer.
            {
                {{
                    0x3C, 0x40, 0xE2, 0x3F, 0xE1, 0x87, 0x13, 0x52,
                    0x98, 0x7F, 0x20, 0x30, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{308u, 309u, 310u, 311u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0xC2, 0x10, 0xF3, 0x1F, 0x21, 0x84, 0x10, 0x72,
                    0xC8, 0xBF, 0x49, 0x2D, 0x0F
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{304u, 305u, 306u, 307u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0xE0, 0xA0, 0xD0, 0xAF, 0xA1, 0x85, 0x17, 0x76,
                    0xB8, 0xFF, 0xC0, 0x80, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{300u, 301u, 302u, 303u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 24.
    {
        312u, // center
        {{
            // L0 outer.
            {
                {{
                    0x6C, 0x00, 0xF2, 0x9F, 0x21, 0x85, 0x1A, 0x5E,
                    0x98, 0x3F, 0xAC, 0x30, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{321u, 322u, 323u, 324u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x02, 0x03, 0xF9, 0x2F, 0xA1, 0x84, 0x10, 0x42,
                    0x38, 0xBF, 0x86, 0x2D, 0x07
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{317u, 318u, 319u, 320u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0xA0, 0x90, 0xC3, 0x0F, 0x61, 0x84, 0x1F, 0x76,
                    0xF8, 0xBF, 0x64, 0x20, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{313u, 314u, 315u, 316u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 25.
    {
        325u, // center
        {{
            // L0 outer.
            {
                {{
                    0x54, 0xB0, 0xC3, 0x4F, 0x21, 0x85, 0x1B, 0x72,
                    0x78, 0x3F, 0xB8, 0x60, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{334u, 335u, 336u, 337u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x0B, 0x20, 0xF6, 0x7F, 0x21, 0x84, 0x10, 0x72,
                    0xA8, 0x3F, 0x08, 0x0F, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{330u, 331u, 332u, 333u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x20, 0xA0, 0xD3, 0xBF, 0xA1, 0x85, 0x1B, 0x7A,
                    0xA8, 0x3F, 0xB4, 0x10, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{326u, 327u, 328u, 329u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 26.
    {
        338u, // center
        {{
            // L0 outer.
            {
                {{
                    0x50, 0x20, 0xF0, 0x7F, 0xE1, 0x85, 0x17, 0x62,
                    0x78, 0x7F, 0x1C, 0x80, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{347u, 348u, 349u, 350u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x0A, 0x17, 0xFC, 0x9F, 0x61, 0x84, 0x10, 0x52,
                    0xD8, 0xFF, 0x41, 0x21, 0x08
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{343u, 344u, 345u, 346u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x78, 0xE0, 0xD2, 0x2F, 0xA1, 0x84, 0x1D, 0x42,
                    0x18, 0x7F, 0xC8, 0x50, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{339u, 340u, 341u, 342u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 27.
    {
        351u, // center
        {{
            // L0 outer.
            {
                {{
                    0x88, 0x50, 0xC3, 0x6F, 0xA1, 0x84, 0x1B, 0x66,
                    0x58, 0x3F, 0x7C, 0x70, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{360u, 361u, 362u, 363u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x45, 0x35, 0xC2, 0x4F, 0xA1, 0x84, 0x10, 0x52,
                    0x88, 0xFF, 0xCF, 0x19, 0x04
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{356u, 357u, 358u, 359u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x00, 0x20, 0xD3, 0x5F, 0x21, 0x84, 0x15, 0x7E,
                    0x38, 0xBF, 0xE8, 0x40, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{352u, 353u, 354u, 355u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 28.
    {
        364u, // center
        {{
            // L0 outer.
            {
                {{
                    0xC8, 0x30, 0xD1, 0xCF, 0xE1, 0x87, 0x1E, 0x7E,
                    0xA8, 0x7F, 0x04, 0xA0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{373u, 374u, 375u, 376u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0xCD, 0x11, 0xFC, 0x1F, 0xE1, 0x84, 0x10, 0x62,
                    0xB8, 0x7F, 0x08, 0x01, 0x08
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{369u, 370u, 371u, 372u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0xCC, 0x90, 0xC3, 0x3F, 0x21, 0x86, 0x11, 0x6E,
                    0x08, 0xFF, 0xAC, 0xC0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{365u, 366u, 367u, 368u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 29.
    {
        377u, // center
        {{
            // L0 outer.
            {
                {{
                    0xE0, 0x00, 0xE2, 0xCF, 0xE1, 0x87, 0x11, 0x62,
                    0x48, 0x7F, 0xB4, 0x30, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{386u, 387u, 388u, 389u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x85, 0x12, 0xE4, 0xFF, 0xE1, 0x84, 0x10, 0x72,
                    0x08, 0x3F, 0x0F, 0x27, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{382u, 383u, 384u, 385u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0xA8, 0x60, 0xE1, 0xDF, 0x61, 0x85, 0x1C, 0x52,
                    0x68, 0x7F, 0x70, 0x80, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{378u, 379u, 380u, 381u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 30.
    {
        390u, // center
        {{
            // L0 outer.
            {
                {{
                    0x50, 0xE0, 0xC3, 0x5F, 0xE1, 0x85, 0x1D, 0x56,
                    0xD8, 0x3F, 0xB4, 0xB0, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{399u, 400u, 401u, 402u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x41, 0x0C, 0xF5, 0x0F, 0xA1, 0x84, 0x10, 0x72,
                    0xC8, 0x3F, 0xCB, 0x3C, 0x0A
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{395u, 396u, 397u, 398u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x9C, 0x50, 0xE1, 0x4F, 0x21, 0x87, 0x18, 0x72,
                    0xE8, 0x7F, 0x8C, 0xE0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{391u, 392u, 393u, 394u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 31.
    {
        403u, // center
        {{
            // L0 outer.
            {
                {{
                    0x80, 0x50, 0xF3, 0x6F, 0x61, 0x85, 0x19, 0x72,
                    0x48, 0x7F, 0x70, 0xD0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{412u, 413u, 414u, 415u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x81, 0x06, 0xC6, 0x5F, 0x21, 0x84, 0x10, 0x52,
                    0x78, 0xBF, 0xC7, 0x28, 0x07
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{408u, 409u, 410u, 411u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0xFC, 0xA0, 0xE2, 0x7F, 0x21, 0x84, 0x14, 0x6E,
                    0xB8, 0x3F, 0x34, 0x00, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{404u, 405u, 406u, 407u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 32.
    {
        416u, // center
        {{
            // L0 outer.
            {
                {{
                    0xC4, 0xB0, 0xF1, 0x2F, 0x21, 0x84, 0x18, 0x46,
                    0x78, 0x3F, 0x7C, 0xB0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{425u, 426u, 427u, 428u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x49, 0x35, 0xF2, 0x3F, 0xA1, 0x84, 0x10, 0x62,
                    0x68, 0x3F, 0xCB, 0x11, 0x0C
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{421u, 422u, 423u, 424u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x60, 0x40, 0xF3, 0x7F, 0x21, 0x84, 0x1C, 0x7E,
                    0x98, 0xFF, 0x50, 0x40, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{417u, 418u, 419u, 420u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 33.
    {
        429u, // center
        {{
            // L0 outer.
            {
                {{
                    0xF8, 0xB0, 0xD1, 0x6F, 0x21, 0x84, 0x18, 0x5E,
                    0x28, 0xBF, 0x40, 0x90, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{438u, 439u, 440u, 441u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x09, 0x11, 0xD5, 0x4F, 0xA1, 0x84, 0x10, 0x72,
                    0xE8, 0xFF, 0x41, 0x2D, 0x0C
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{434u, 435u, 436u, 437u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x14, 0xC0, 0xF2, 0xDF, 0x61, 0x84, 0x10, 0x4E,
                    0x38, 0x7F, 0xE8, 0x10, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{430u, 431u, 432u, 433u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 34.
    {
        442u, // center
        {{
            // L0 outer.
            {
                {{
                    0x90, 0x20, 0xE3, 0xFF, 0x61, 0x86, 0x1B, 0x6E,
                    0x28, 0xFF, 0x30, 0x80, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{451u, 452u, 453u, 454u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x4A, 0x35, 0xEA, 0x7F, 0x21, 0x84, 0x10, 0x62,
                    0x48, 0xBF, 0x48, 0x37, 0x01
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{447u, 448u, 449u, 450u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x6C, 0xB0, 0xE2, 0xDF, 0x21, 0x85, 0x1A, 0x4A,
                    0x68, 0xBF, 0x58, 0x80, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{443u, 444u, 445u, 446u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 35.
    {
        455u, // center
        {{
            // L0 outer.
            {
                {{
                    0x8C, 0xB0, 0xD0, 0xAF, 0x61, 0x84, 0x15, 0x6E,
                    0x48, 0x7F, 0xC4, 0x30, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{464u, 465u, 466u, 467u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x81, 0x1F, 0xCD, 0xCF, 0xE1, 0x84, 0x10, 0x72,
                    0xF8, 0x3F, 0x01, 0x20, 0x04
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{460u, 461u, 462u, 463u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x04, 0xB0, 0xC0, 0xCF, 0xE1, 0x87, 0x17, 0x42,
                    0xA8, 0x7F, 0x0C, 0x90, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{456u, 457u, 458u, 459u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 36.
    {
        468u, // center
        {{
            // L0 outer.
            {
                {{
                    0x2C, 0x40, 0xF1, 0x3F, 0xE1, 0x84, 0x19, 0x4A,
                    0x88, 0x3F, 0x5C, 0x50, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{477u, 478u, 479u, 480u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0xC1, 0x1F, 0xF4, 0xCF, 0x21, 0x84, 0x10, 0x72,
                    0xD8, 0x7F, 0xC2, 0x08, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{473u, 474u, 475u, 476u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x6C, 0x00, 0xC2, 0x5F, 0x61, 0x86, 0x14, 0x5A,
                    0xB8, 0xFF, 0x38, 0x00, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{469u, 470u, 471u, 472u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 37.
    {
        481u, // center
        {{
            // L0 outer.
            {
                {{
                    0x84, 0xF0, 0xE2, 0x6F, 0x21, 0x86, 0x17, 0x5E,
                    0x78, 0x3F, 0xC8, 0xB0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{490u, 491u, 492u, 493u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x47, 0x35, 0xE7, 0x0F, 0x21, 0x84, 0x10, 0x52,
                    0xF8, 0xFF, 0x06, 0x38, 0x08
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{486u, 487u, 488u, 489u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x1C, 0x80, 0xC2, 0x5F, 0x21, 0x86, 0x1C, 0x52,
                    0xF8, 0xBF, 0xEC, 0xC0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{482u, 483u, 484u, 485u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 38.
    {
        494u, // center
        {{
            // L0 outer.
            {
                {{
                    0xB4, 0xA0, 0xC1, 0xAF, 0x21, 0x86, 0x1B, 0x7A,
                    0x78, 0xFF, 0xD8, 0x00, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{503u, 504u, 505u, 506u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x4E, 0x29, 0xF4, 0xFF, 0x61, 0x84, 0x10, 0x62,
                    0x18, 0x3F, 0x01, 0x3A, 0x0C
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{499u, 500u, 501u, 502u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0xA4, 0x70, 0xC2, 0xCF, 0xA1, 0x87, 0x17, 0x66,
                    0x48, 0xBF, 0x28, 0x70, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{495u, 496u, 497u, 498u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 39.
    {
        507u, // center
        {{
            // L0 outer.
            {
                {{
                    0x20, 0x50, 0xC1, 0xFF, 0xE1, 0x87, 0x1C, 0x66,
                    0x38, 0x3F, 0x24, 0x20, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{516u, 517u, 518u, 519u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x85, 0x02, 0xFB, 0x3F, 0xA1, 0x84, 0x10, 0x52,
                    0xA8, 0xBF, 0xC3, 0x0A, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{512u, 513u, 514u, 515u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0xC8, 0xD0, 0xD3, 0x7F, 0x61, 0x84, 0x14, 0x46,
                    0xD8, 0x7F, 0xE0, 0xC0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{508u, 509u, 510u, 511u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 40.
    {
        520u, // center
        {{
            // L0 outer.
            {
                {{
                    0x68, 0xC0, 0xE2, 0xBF, 0xE1, 0x84, 0x12, 0x4A,
                    0xA8, 0xFF, 0x94, 0x40, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{529u, 530u, 531u, 532u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x0E, 0x34, 0xF5, 0x6F, 0x21, 0x84, 0x10, 0x42,
                    0x98, 0x7F, 0xC7, 0x29, 0x01
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{525u, 526u, 527u, 528u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0xCC, 0x20, 0xD2, 0x9F, 0xA1, 0x86, 0x15, 0x7E,
                    0x08, 0x7F, 0xF8, 0x70, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{521u, 522u, 523u, 524u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 41.
    {
        533u, // center
        {{
            // L0 outer.
            {
                {{
                    0xF4, 0x60, 0xE0, 0xAF, 0xA1, 0x86, 0x14, 0x5A,
                    0x58, 0x3F, 0x94, 0x50, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{542u, 543u, 544u, 545u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x0F, 0x23, 0xD4, 0x6F, 0xA1, 0x84, 0x10, 0x52,
                    0xB8, 0xBF, 0x85, 0x03, 0x03
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{538u, 539u, 540u, 541u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x7C, 0x30, 0xD3, 0x1F, 0xA1, 0x86, 0x11, 0x6E,
                    0x58, 0xFF, 0x20, 0x30, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{534u, 535u, 536u, 537u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 42.
    {
        546u, // center
        {{
            // L0 outer.
            {
                {{
                    0x30, 0xC0, 0xE2, 0x9F, 0x21, 0x86, 0x1E, 0x56,
                    0x68, 0xBF, 0x0C, 0x60, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{555u, 556u, 557u, 558u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x4D, 0x34, 0xCE, 0x2F, 0x61, 0x84, 0x10, 0x52,
                    0xF8, 0xBF, 0x89, 0x36, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{551u, 552u, 553u, 554u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x78, 0xC0, 0xC1, 0x3F, 0xA1, 0x87, 0x17, 0x4A,
                    0x78, 0x7F, 0x70, 0x30, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{547u, 548u, 549u, 550u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 43.
    {
        559u, // center
        {{
            // L0 outer.
            {
                {{
                    0xA4, 0xF0, 0xD0, 0x9F, 0xA1, 0x84, 0x1B, 0x6E,
                    0xA8, 0x7F, 0x18, 0xD0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{568u, 569u, 570u, 571u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x4A, 0x13, 0xE6, 0x7F, 0x61, 0x84, 0x10, 0x52,
                    0x98, 0xFF, 0x01, 0x2E, 0x03
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{564u, 565u, 566u, 567u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x78, 0xC0, 0xF3, 0x1F, 0x21, 0x85, 0x1C, 0x7A,
                    0x48, 0x3F, 0xB4, 0x90, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{560u, 561u, 562u, 563u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 44.
    {
        572u, // center
        {{
            // L0 outer.
            {
                {{
                    0xA0, 0x80, 0xF0, 0x6F, 0x61, 0x84, 0x1A, 0x76,
                    0x98, 0xFF, 0xCC, 0xD0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{581u, 582u, 583u, 584u}} // TL, TR, BR, BL
            },
            // L1.
            {
                {{
                    0x08, 0x2D, 0xE2, 0xDF, 0x21, 0x84, 0x10, 0x62,
                    0xB8, 0xBF, 0x8C, 0x32, 0x0F
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{577u, 578u, 579u, 580u}} // N, E, S, W
            },
            // L2 inner.
            {
                {{
                    0x8C, 0x30, 0xC3, 0xDF, 0x61, 0x85, 0x13, 0x42,
                    0x78, 0xFF, 0xA4, 0x40, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{573u, 574u, 575u, 576u}} // TL, TR, BR, BL
            }
        }}
    }

};

} // namespace n3_april
} // namespace predef
} // namespace aruco2
} // namespace cv
