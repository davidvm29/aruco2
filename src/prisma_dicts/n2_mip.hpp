#pragma once

#include "data.hpp"

namespace cv {
namespace aruco2 {
namespace predef {
namespace n2_mip {

// N2, ArUco MIP 36h12: 27 PRISMarkers.

static constexpr auto type = PRISMA_D2_ARUCO_MIP_36H12;
static constexpr auto aux = DICT_ARUCO_MIP_36h12;
static constexpr char name[] = "PRISMA_D2_ARUCO_MIP_36H12";

using Mark = Marker<2>;

// Array position == PRISMarker ID.
static constexpr Mark markers[] = {

    // PRISMarker 0.
    {
        0u, // center
        {{
            // L0 outer.
            {
                {{
                    0x01, 0x22, 0xFE, 0x2F, 0x61, 0x84, 0x10, 0x52,
                    0xE8, 0xFF, 0x8A, 0x21, 0x04
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{5u, 6u, 7u, 8u}} // N, E, S, W
            },
            // L1 inner.
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
        9u, // center
        {{
            // L0 outer.
            {
                {{
                    0x46, 0x3F, 0xDF, 0x6F, 0x61, 0x84, 0x10, 0x42,
                    0x48, 0x7F, 0x43, 0x26, 0x01
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{14u, 15u, 16u, 17u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x58, 0xD0, 0xD0, 0xBF, 0x21, 0x84, 0x1B, 0x76,
                    0x48, 0xFF, 0x84, 0x40, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{10u, 11u, 12u, 13u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 2.
    {
        18u, // center
        {{
            // L0 outer.
            {
                {{
                    0xC2, 0x2D, 0xD8, 0x7F, 0xA1, 0x84, 0x10, 0x72,
                    0xA8, 0x7F, 0x4D, 0x02, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{23u, 24u, 25u, 26u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x24, 0xF0, 0xE0, 0xCF, 0x61, 0x85, 0x1A, 0x66,
                    0xE8, 0xFF, 0x98, 0x70, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{19u, 20u, 21u, 22u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 3.
    {
        27u, // center
        {{
            // L0 outer.
            {
                {{
                    0x00, 0x3C, 0xD8, 0xFF, 0xE1, 0x84, 0x10, 0x42,
                    0xE8, 0xFF, 0xC7, 0x30, 0x01
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{32u, 33u, 34u, 35u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x20, 0xC0, 0xC2, 0xEF, 0x21, 0x85, 0x17, 0x6E,
                    0xE8, 0xFF, 0xFC, 0x80, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{28u, 29u, 30u, 31u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 4.
    {
        36u, // center
        {{
            // L0 outer.
            {
                {{
                    0x0E, 0x2D, 0xCB, 0x6F, 0x61, 0x84, 0x10, 0x72,
                    0xF8, 0x7F, 0x86, 0x23, 0x04
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{41u, 42u, 43u, 44u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x94, 0xF0, 0xE0, 0x3F, 0x21, 0x87, 0x1D, 0x42,
                    0x58, 0x7F, 0x30, 0x70, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{37u, 38u, 39u, 40u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 5.
    {
        45u, // center
        {{
            // L0 outer.
            {
                {{
                    0x89, 0x2D, 0xDB, 0x8F, 0xA1, 0x84, 0x10, 0x62,
                    0x38, 0xBF, 0xC1, 0x09, 0x00
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{50u, 51u, 52u, 53u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x30, 0x80, 0xC0, 0x7F, 0x21, 0x86, 0x1E, 0x46,
                    0xD8, 0x7F, 0x7C, 0x30, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{46u, 47u, 48u, 49u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 6.
    {
        54u, // center
        {{
            // L0 outer.
            {
                {{
                    0x42, 0x25, 0xFA, 0xBF, 0x61, 0x84, 0x10, 0x72,
                    0xB8, 0xBF, 0x02, 0x06, 0x0B
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{59u, 60u, 61u, 62u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xD8, 0x80, 0xD1, 0xEF, 0x21, 0x84, 0x1C, 0x6A,
                    0x58, 0x3F, 0x04, 0xF0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{55u, 56u, 57u, 58u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 7.
    {
        63u, // center
        {{
            // L0 outer.
            {
                {{
                    0x05, 0x32, 0xF6, 0x6F, 0xE1, 0x84, 0x10, 0x62,
                    0x38, 0xBF, 0x0B, 0x02, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{68u, 69u, 70u, 71u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x0C, 0x30, 0xC0, 0xBF, 0xA1, 0x84, 0x17, 0x4E,
                    0xD8, 0x3F, 0x7C, 0x40, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{64u, 65u, 66u, 67u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 8.
    {
        72u, // center
        {{
            // L0 outer.
            {
                {{
                    0x0C, 0x11, 0xEF, 0xCF, 0x61, 0x84, 0x10, 0x62,
                    0xC8, 0xBF, 0x06, 0x2E, 0x0E
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{77u, 78u, 79u, 80u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xA0, 0x50, 0xF0, 0x5F, 0xE1, 0x85, 0x1D, 0x4E,
                    0x38, 0xFF, 0x80, 0x00, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{73u, 74u, 75u, 76u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 9.
    {
        81u, // center
        {{
            // L0 outer.
            {
                {{
                    0xCA, 0x36, 0xC1, 0xEF, 0x61, 0x84, 0x10, 0x52,
                    0x18, 0xFF, 0x04, 0x23, 0x07
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{86u, 87u, 88u, 89u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x58, 0x10, 0xC1, 0x7F, 0x21, 0x87, 0x13, 0x76,
                    0xA8, 0x7F, 0x30, 0x20, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{82u, 83u, 84u, 85u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 10.
    {
        90u, // center
        {{
            // L0 outer.
            {
                {{
                    0x05, 0x1D, 0xF6, 0x1F, 0x61, 0x84, 0x10, 0x72,
                    0x78, 0xBF, 0x01, 0x2D, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{95u, 96u, 97u, 98u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x24, 0x10, 0xE3, 0x3F, 0x61, 0x87, 0x17, 0x5A,
                    0xB8, 0x3F, 0x38, 0xE0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{91u, 92u, 93u, 94u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 11.
    {
        99u, // center
        {{
            // L0 outer.
            {
                {{
                    0x0D, 0x2B, 0xE1, 0xAF, 0x61, 0x84, 0x10, 0x42,
                    0x88, 0xBF, 0x8B, 0x2D, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{104u, 105u, 106u, 107u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x6C, 0xC0, 0xF2, 0x6F, 0xE1, 0x85, 0x10, 0x56,
                    0x28, 0x3F, 0xCC, 0x30, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{100u, 101u, 102u, 103u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 12.
    {
        108u, // center
        {{
            // L0 outer.
            {
                {{
                    0xC0, 0x37, 0xCC, 0x6F, 0x61, 0x84, 0x10, 0x52,
                    0x98, 0x3F, 0x86, 0x34, 0x0D
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{113u, 114u, 115u, 116u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x34, 0xF0, 0xE2, 0x3F, 0x21, 0x87, 0x12, 0x6E,
                    0x48, 0x7F, 0x24, 0x90, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{109u, 110u, 111u, 112u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 13.
    {
        117u, // center
        {{
            // L0 outer.
            {
                {{
                    0x0A, 0x04, 0xC6, 0x7F, 0xE1, 0x84, 0x10, 0x62,
                    0xB8, 0x7F, 0x05, 0x35, 0x0B
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{122u, 123u, 124u, 125u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x7C, 0xE0, 0xF1, 0x0F, 0x61, 0x85, 0x16, 0x4E,
                    0x48, 0xFF, 0xCC, 0xE0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{118u, 119u, 120u, 121u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 14.
    {
        126u, // center
        {{
            // L0 outer.
            {
                {{
                    0x49, 0x06, 0xD3, 0x2F, 0x61, 0x84, 0x10, 0x62,
                    0xB8, 0xFF, 0x07, 0x17, 0x04
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{131u, 132u, 133u, 134u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xC0, 0x50, 0xE2, 0xAF, 0xE1, 0x84, 0x1A, 0x5E,
                    0xF8, 0xBF, 0x70, 0xC0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{127u, 128u, 129u, 130u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 15.
    {
        135u, // center
        {{
            // L0 outer.
            {
                {{
                    0x05, 0x1E, 0xFD, 0x5F, 0xE1, 0x84, 0x10, 0x52,
                    0x18, 0xBF, 0x8D, 0x38, 0x00
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{140u, 141u, 142u, 143u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xE0, 0x60, 0xE1, 0x0F, 0xA1, 0x86, 0x1A, 0x66,
                    0x48, 0xBF, 0xB8, 0xD0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{136u, 137u, 138u, 139u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 16.
    {
        144u, // center
        {{
            // L0 outer.
            {
                {{
                    0x86, 0x17, 0xD5, 0xAF, 0xE1, 0x84, 0x10, 0x62,
                    0x18, 0x7F, 0x81, 0x23, 0x0A
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{149u, 150u, 151u, 152u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xC0, 0x70, 0xC0, 0xDF, 0xE1, 0x87, 0x13, 0x52,
                    0x38, 0xFF, 0xD0, 0xD0, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{145u, 146u, 147u, 148u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 17.
    {
        153u, // center
        {{
            // L0 outer.
            {
                {{
                    0x41, 0x29, 0xF9, 0xBF, 0x61, 0x84, 0x10, 0x42,
                    0xB8, 0x7F, 0xC4, 0x13, 0x0B
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{158u, 159u, 160u, 161u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xB8, 0xB0, 0xF2, 0x3F, 0x21, 0x87, 0x1F, 0x6A,
                    0x98, 0x3F, 0x08, 0x20, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{154u, 155u, 156u, 157u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 18.
    {
        162u, // center
        {{
            // L0 outer.
            {
                {{
                    0xCA, 0x2E, 0xF9, 0x5F, 0x61, 0x84, 0x10, 0x52,
                    0x98, 0x7F, 0x47, 0x05, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{167u, 168u, 169u, 170u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xE0, 0xD0, 0xC0, 0x9F, 0x21, 0x87, 0x17, 0x52,
                    0x58, 0x3F, 0x5C, 0x60, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{163u, 164u, 165u, 166u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 19.
    {
        171u, // center
        {{
            // L0 outer.
            {
                {{
                    0xC7, 0x16, 0xE2, 0xCF, 0x21, 0x84, 0x10, 0x62,
                    0xC8, 0x7F, 0xCA, 0x27, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{176u, 177u, 178u, 179u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xB0, 0x70, 0xC3, 0xAF, 0x61, 0x86, 0x18, 0x72,
                    0xF8, 0xFF, 0x14, 0xB0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{172u, 173u, 174u, 175u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 20.
    {
        180u, // center
        {{
            // L0 outer.
            {
                {{
                    0xC9, 0x3B, 0xC3, 0x9F, 0x21, 0x84, 0x10, 0x72,
                    0x88, 0x3F, 0x01, 0x21, 0x07
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{185u, 186u, 187u, 188u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x2C, 0xA0, 0xF3, 0x4F, 0xA1, 0x87, 0x1E, 0x42,
                    0x98, 0xBF, 0x28, 0x70, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{181u, 182u, 183u, 184u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 21.
    {
        189u, // center
        {{
            // L0 outer.
            {
                {{
                    0x43, 0x2A, 0xDB, 0x2F, 0xA1, 0x84, 0x10, 0x72,
                    0x78, 0x7F, 0xC6, 0x3A, 0x00
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{194u, 195u, 196u, 197u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x6C, 0xF0, 0xF1, 0xAF, 0x21, 0x87, 0x14, 0x66,
                    0x38, 0x3F, 0xA0, 0xB0, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{190u, 191u, 192u, 193u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 22.
    {
        198u, // center
        {{
            // L0 outer.
            {
                {{
                    0x89, 0x0A, 0xF7, 0x9F, 0x21, 0x84, 0x10, 0x62,
                    0xF8, 0x3F, 0x01, 0x1A, 0x0B
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{203u, 204u, 205u, 206u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x0C, 0xA0, 0xD2, 0x1F, 0x21, 0x85, 0x17, 0x5E,
                    0x68, 0x7F, 0xE0, 0x10, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{199u, 200u, 201u, 202u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 23.
    {
        207u, // center
        {{
            // L0 outer.
            {
                {{
                    0xC2, 0x10, 0xF3, 0x1F, 0x21, 0x84, 0x10, 0x72,
                    0xC8, 0xBF, 0x49, 0x2D, 0x0F
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{212u, 213u, 214u, 215u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xE0, 0xA0, 0xD0, 0xAF, 0xA1, 0x85, 0x17, 0x76,
                    0xB8, 0xFF, 0xC0, 0x80, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{208u, 209u, 210u, 211u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 24.
    {
        216u, // center
        {{
            // L0 outer.
            {
                {{
                    0x02, 0x03, 0xF9, 0x2F, 0xA1, 0x84, 0x10, 0x42,
                    0x38, 0xBF, 0x86, 0x2D, 0x07
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{221u, 222u, 223u, 224u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xA0, 0x90, 0xC3, 0x0F, 0x61, 0x84, 0x1F, 0x76,
                    0xF8, 0xBF, 0x64, 0x20, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{217u, 218u, 219u, 220u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 25.
    {
        225u, // center
        {{
            // L0 outer.
            {
                {{
                    0x0B, 0x20, 0xF6, 0x7F, 0x21, 0x84, 0x10, 0x72,
                    0xA8, 0x3F, 0x08, 0x0F, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{230u, 231u, 232u, 233u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x20, 0xA0, 0xD3, 0xBF, 0xA1, 0x85, 0x1B, 0x7A,
                    0xA8, 0x3F, 0xB4, 0x10, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{226u, 227u, 228u, 229u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 26.
    {
        234u, // center
        {{
            // L0 outer.
            {
                {{
                    0x0A, 0x17, 0xFC, 0x9F, 0x61, 0x84, 0x10, 0x52,
                    0xD8, 0xFF, 0x41, 0x21, 0x08
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{239u, 240u, 241u, 242u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x78, 0xE0, 0xD2, 0x2F, 0xA1, 0x84, 0x1D, 0x42,
                    0x18, 0x7F, 0xC8, 0x50, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{235u, 236u, 237u, 238u}} // TL, TR, BR, BL
            }
        }}
    }

};

} // namespace n2_mip
} // namespace predef
} // namespace aruco2
} // namespace cv
