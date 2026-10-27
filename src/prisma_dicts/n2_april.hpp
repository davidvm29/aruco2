#pragma once

#include "data.hpp"

namespace cv {
namespace aruco2 {
namespace predef {
namespace n2_april {

// N2, AprilTag 36h11: 65 PRISMarkers.

static constexpr auto type = PRISMA_D2_APRILTAG_36H11;
static constexpr auto aux = DICT_APRILTAG_36h11;
static constexpr char name[] = "PRISMA_D2_APRILTAG_36H11";

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
    },

    // PRISMarker 27.
    {
        243u, // center
        {{
            // L0 outer.
            {
                {{
                    0x45, 0x35, 0xC2, 0x4F, 0xA1, 0x84, 0x10, 0x52,
                    0x88, 0xFF, 0xCF, 0x19, 0x04
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{248u, 249u, 250u, 251u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x00, 0x20, 0xD3, 0x5F, 0x21, 0x84, 0x15, 0x7E,
                    0x38, 0xBF, 0xE8, 0x40, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{244u, 245u, 246u, 247u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 28.
    {
        252u, // center
        {{
            // L0 outer.
            {
                {{
                    0xCD, 0x11, 0xFC, 0x1F, 0xE1, 0x84, 0x10, 0x62,
                    0xB8, 0x7F, 0x08, 0x01, 0x08
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{257u, 258u, 259u, 260u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xCC, 0x90, 0xC3, 0x3F, 0x21, 0x86, 0x11, 0x6E,
                    0x08, 0xFF, 0xAC, 0xC0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{253u, 254u, 255u, 256u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 29.
    {
        261u, // center
        {{
            // L0 outer.
            {
                {{
                    0x85, 0x12, 0xE4, 0xFF, 0xE1, 0x84, 0x10, 0x72,
                    0x08, 0x3F, 0x0F, 0x27, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{266u, 267u, 268u, 269u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xA8, 0x60, 0xE1, 0xDF, 0x61, 0x85, 0x1C, 0x52,
                    0x68, 0x7F, 0x70, 0x80, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{262u, 263u, 264u, 265u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 30.
    {
        270u, // center
        {{
            // L0 outer.
            {
                {{
                    0x41, 0x0C, 0xF5, 0x0F, 0xA1, 0x84, 0x10, 0x72,
                    0xC8, 0x3F, 0xCB, 0x3C, 0x0A
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{275u, 276u, 277u, 278u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x9C, 0x50, 0xE1, 0x4F, 0x21, 0x87, 0x18, 0x72,
                    0xE8, 0x7F, 0x8C, 0xE0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{271u, 272u, 273u, 274u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 31.
    {
        279u, // center
        {{
            // L0 outer.
            {
                {{
                    0x81, 0x06, 0xC6, 0x5F, 0x21, 0x84, 0x10, 0x52,
                    0x78, 0xBF, 0xC7, 0x28, 0x07
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{284u, 285u, 286u, 287u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xFC, 0xA0, 0xE2, 0x7F, 0x21, 0x84, 0x14, 0x6E,
                    0xB8, 0x3F, 0x34, 0x00, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{280u, 281u, 282u, 283u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 32.
    {
        288u, // center
        {{
            // L0 outer.
            {
                {{
                    0x49, 0x35, 0xF2, 0x3F, 0xA1, 0x84, 0x10, 0x62,
                    0x68, 0x3F, 0xCB, 0x11, 0x0C
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{293u, 294u, 295u, 296u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x60, 0x40, 0xF3, 0x7F, 0x21, 0x84, 0x1C, 0x7E,
                    0x98, 0xFF, 0x50, 0x40, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{289u, 290u, 291u, 292u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 33.
    {
        297u, // center
        {{
            // L0 outer.
            {
                {{
                    0x09, 0x11, 0xD5, 0x4F, 0xA1, 0x84, 0x10, 0x72,
                    0xE8, 0xFF, 0x41, 0x2D, 0x0C
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{302u, 303u, 304u, 305u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x14, 0xC0, 0xF2, 0xDF, 0x61, 0x84, 0x10, 0x4E,
                    0x38, 0x7F, 0xE8, 0x10, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{298u, 299u, 300u, 301u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 34.
    {
        306u, // center
        {{
            // L0 outer.
            {
                {{
                    0x4A, 0x35, 0xEA, 0x7F, 0x21, 0x84, 0x10, 0x62,
                    0x48, 0xBF, 0x48, 0x37, 0x01
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{311u, 312u, 313u, 314u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x6C, 0xB0, 0xE2, 0xDF, 0x21, 0x85, 0x1A, 0x4A,
                    0x68, 0xBF, 0x58, 0x80, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{307u, 308u, 309u, 310u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 35.
    {
        315u, // center
        {{
            // L0 outer.
            {
                {{
                    0x81, 0x1F, 0xCD, 0xCF, 0xE1, 0x84, 0x10, 0x72,
                    0xF8, 0x3F, 0x01, 0x20, 0x04
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{320u, 321u, 322u, 323u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x04, 0xB0, 0xC0, 0xCF, 0xE1, 0x87, 0x17, 0x42,
                    0xA8, 0x7F, 0x0C, 0x90, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{316u, 317u, 318u, 319u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 36.
    {
        324u, // center
        {{
            // L0 outer.
            {
                {{
                    0xC1, 0x1F, 0xF4, 0xCF, 0x21, 0x84, 0x10, 0x72,
                    0xD8, 0x7F, 0xC2, 0x08, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{329u, 330u, 331u, 332u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x6C, 0x00, 0xC2, 0x5F, 0x61, 0x86, 0x14, 0x5A,
                    0xB8, 0xFF, 0x38, 0x00, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{325u, 326u, 327u, 328u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 37.
    {
        333u, // center
        {{
            // L0 outer.
            {
                {{
                    0x47, 0x35, 0xE7, 0x0F, 0x21, 0x84, 0x10, 0x52,
                    0xF8, 0xFF, 0x06, 0x38, 0x08
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{338u, 339u, 340u, 341u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x1C, 0x80, 0xC2, 0x5F, 0x21, 0x86, 0x1C, 0x52,
                    0xF8, 0xBF, 0xEC, 0xC0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{334u, 335u, 336u, 337u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 38.
    {
        342u, // center
        {{
            // L0 outer.
            {
                {{
                    0x4E, 0x29, 0xF4, 0xFF, 0x61, 0x84, 0x10, 0x62,
                    0x18, 0x3F, 0x01, 0x3A, 0x0C
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{347u, 348u, 349u, 350u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xA4, 0x70, 0xC2, 0xCF, 0xA1, 0x87, 0x17, 0x66,
                    0x48, 0xBF, 0x28, 0x70, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{343u, 344u, 345u, 346u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 39.
    {
        351u, // center
        {{
            // L0 outer.
            {
                {{
                    0x85, 0x02, 0xFB, 0x3F, 0xA1, 0x84, 0x10, 0x52,
                    0xA8, 0xBF, 0xC3, 0x0A, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{356u, 357u, 358u, 359u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xC8, 0xD0, 0xD3, 0x7F, 0x61, 0x84, 0x14, 0x46,
                    0xD8, 0x7F, 0xE0, 0xC0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{352u, 353u, 354u, 355u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 40.
    {
        360u, // center
        {{
            // L0 outer.
            {
                {{
                    0x0E, 0x34, 0xF5, 0x6F, 0x21, 0x84, 0x10, 0x42,
                    0x98, 0x7F, 0xC7, 0x29, 0x01
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{365u, 366u, 367u, 368u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xCC, 0x20, 0xD2, 0x9F, 0xA1, 0x86, 0x15, 0x7E,
                    0x08, 0x7F, 0xF8, 0x70, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{361u, 362u, 363u, 364u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 41.
    {
        369u, // center
        {{
            // L0 outer.
            {
                {{
                    0x0F, 0x23, 0xD4, 0x6F, 0xA1, 0x84, 0x10, 0x52,
                    0xB8, 0xBF, 0x85, 0x03, 0x03
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{374u, 375u, 376u, 377u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x7C, 0x30, 0xD3, 0x1F, 0xA1, 0x86, 0x11, 0x6E,
                    0x58, 0xFF, 0x20, 0x30, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{370u, 371u, 372u, 373u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 42.
    {
        378u, // center
        {{
            // L0 outer.
            {
                {{
                    0x4D, 0x34, 0xCE, 0x2F, 0x61, 0x84, 0x10, 0x52,
                    0xF8, 0xBF, 0x89, 0x36, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{383u, 384u, 385u, 386u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x78, 0xC0, 0xC1, 0x3F, 0xA1, 0x87, 0x17, 0x4A,
                    0x78, 0x7F, 0x70, 0x30, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{379u, 380u, 381u, 382u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 43.
    {
        387u, // center
        {{
            // L0 outer.
            {
                {{
                    0x4A, 0x13, 0xE6, 0x7F, 0x61, 0x84, 0x10, 0x52,
                    0x98, 0xFF, 0x01, 0x2E, 0x03
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{392u, 393u, 394u, 395u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x78, 0xC0, 0xF3, 0x1F, 0x21, 0x85, 0x1C, 0x7A,
                    0x48, 0x3F, 0xB4, 0x90, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{388u, 389u, 390u, 391u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 44.
    {
        396u, // center
        {{
            // L0 outer.
            {
                {{
                    0x08, 0x2D, 0xE2, 0xDF, 0x21, 0x84, 0x10, 0x62,
                    0xB8, 0xBF, 0x8C, 0x32, 0x0F
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{401u, 402u, 403u, 404u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x8C, 0x30, 0xC3, 0xDF, 0x61, 0x85, 0x13, 0x42,
                    0x78, 0xFF, 0xA4, 0x40, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{397u, 398u, 399u, 400u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 45.
    {
        405u, // center
        {{
            // L0 outer.
            {
                {{
                    0x4D, 0x38, 0xCB, 0xEF, 0x21, 0x84, 0x10, 0x62,
                    0x08, 0x7F, 0x88, 0x16, 0x0A
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{410u, 411u, 412u, 413u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xD8, 0xD0, 0xC1, 0x8F, 0x61, 0x87, 0x14, 0x52,
                    0xC8, 0xBF, 0x30, 0x30, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{406u, 407u, 408u, 409u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 46.
    {
        414u, // center
        {{
            // L0 outer.
            {
                {{
                    0xC4, 0x07, 0xC9, 0xFF, 0xA1, 0x84, 0x10, 0x42,
                    0xA8, 0x7F, 0x40, 0x07, 0x0F
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{419u, 420u, 421u, 422u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x28, 0x70, 0xD0, 0x2F, 0x21, 0x84, 0x17, 0x72,
                    0x78, 0xFF, 0x08, 0x60, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{415u, 416u, 417u, 418u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 47.
    {
        423u, // center
        {{
            // L0 outer.
            {
                {{
                    0x09, 0x15, 0xDE, 0xFF, 0xE1, 0x84, 0x10, 0x72,
                    0x08, 0xFF, 0x8C, 0x21, 0x03
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{428u, 429u, 430u, 431u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x94, 0x90, 0xE1, 0x0F, 0xE1, 0x84, 0x1C, 0x6E,
                    0x58, 0xFF, 0x94, 0x50, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{424u, 425u, 426u, 427u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 48.
    {
        432u, // center
        {{
            // L0 outer.
            {
                {{
                    0x8B, 0x32, 0xE4, 0xEF, 0x21, 0x84, 0x10, 0x62,
                    0xF8, 0xBF, 0x84, 0x1F, 0x0A
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{437u, 438u, 439u, 440u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x74, 0x20, 0xE0, 0xFF, 0x61, 0x85, 0x1A, 0x5E,
                    0xD8, 0xBF, 0x00, 0x00, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{433u, 434u, 435u, 436u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 49.
    {
        441u, // center
        {{
            // L0 outer.
            {
                {{
                    0x0B, 0x3C, 0xFA, 0x6F, 0x61, 0x84, 0x10, 0x42,
                    0x38, 0x3F, 0x06, 0x19, 0x0C
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{446u, 447u, 448u, 449u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x00, 0xD0, 0xD0, 0x3F, 0x61, 0x86, 0x18, 0x5A,
                    0xE8, 0xBF, 0x7C, 0xE0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{442u, 443u, 444u, 445u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 50.
    {
        450u, // center
        {{
            // L0 outer.
            {
                {{
                    0x43, 0x29, 0xFE, 0x3F, 0xA1, 0x84, 0x10, 0x42,
                    0xF8, 0xBF, 0x0E, 0x37, 0x05
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{455u, 456u, 457u, 458u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xB8, 0x10, 0xE3, 0xCF, 0xE1, 0x85, 0x18, 0x66,
                    0x98, 0xBF, 0xC0, 0xC0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{451u, 452u, 453u, 454u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 51.
    {
        459u, // center
        {{
            // L0 outer.
            {
                {{
                    0x02, 0x03, 0xD3, 0x7F, 0xE1, 0x84, 0x10, 0x72,
                    0x58, 0xFF, 0x43, 0x3B, 0x09
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{464u, 465u, 466u, 467u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xE4, 0xD0, 0xD0, 0x1F, 0x61, 0x87, 0x11, 0x56,
                    0xB8, 0x7F, 0x20, 0xD0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{460u, 461u, 462u, 463u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 52.
    {
        468u, // center
        {{
            // L0 outer.
            {
                {{
                    0xC4, 0x25, 0xEC, 0xCF, 0x21, 0x84, 0x10, 0x52,
                    0xF8, 0x3F, 0x4C, 0x1F, 0x01
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{473u, 474u, 475u, 476u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xA8, 0x90, 0xE0, 0x5F, 0xE1, 0x85, 0x17, 0x7E,
                    0x48, 0xFF, 0x08, 0xE0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{469u, 470u, 471u, 472u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 53.
    {
        477u, // center
        {{
            // L0 outer.
            {
                {{
                    0xC7, 0x0C, 0xE5, 0x1F, 0x61, 0x84, 0x10, 0x42,
                    0x58, 0xBF, 0xC3, 0x1A, 0x0D
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{482u, 483u, 484u, 485u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xAC, 0xC0, 0xD3, 0x3F, 0xE1, 0x84, 0x10, 0x42,
                    0x78, 0xFF, 0x9C, 0xA0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{478u, 479u, 480u, 481u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 54.
    {
        486u, // center
        {{
            // L0 outer.
            {
                {{
                    0x8C, 0x38, 0xCD, 0x7F, 0xE1, 0x84, 0x10, 0x52,
                    0xF8, 0x3F, 0x0C, 0x18, 0x0C
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{491u, 492u, 493u, 494u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x44, 0xB0, 0xD2, 0x8F, 0x61, 0x86, 0x1E, 0x56,
                    0xC8, 0xFF, 0x4C, 0x70, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{487u, 488u, 489u, 490u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 55.
    {
        495u, // center
        {{
            // L0 outer.
            {
                {{
                    0xC1, 0x14, 0xEC, 0x4F, 0xA1, 0x84, 0x10, 0x42,
                    0x18, 0xBF, 0x42, 0x0B, 0x0B
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{500u, 501u, 502u, 503u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x5C, 0x10, 0xF3, 0x1F, 0xE1, 0x84, 0x13, 0x5E,
                    0x38, 0xBF, 0xB4, 0x20, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{496u, 497u, 498u, 499u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 56.
    {
        504u, // center
        {{
            // L0 outer.
            {
                {{
                    0x82, 0x3A, 0xF3, 0x4F, 0x21, 0x84, 0x10, 0x62,
                    0xA8, 0xBF, 0xC2, 0x0A, 0x0D
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{509u, 510u, 511u, 512u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x74, 0x90, 0xD2, 0xBF, 0x21, 0x84, 0x12, 0x46,
                    0xB8, 0x7F, 0x64, 0x50, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{505u, 506u, 507u, 508u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 57.
    {
        513u, // center
        {{
            // L0 outer.
            {
                {{
                    0x89, 0x0E, 0xE9, 0x1F, 0x21, 0x84, 0x10, 0x52,
                    0xA8, 0xFF, 0xC7, 0x33, 0x0E
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{518u, 519u, 520u, 521u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x88, 0x50, 0xE0, 0x4F, 0x61, 0x84, 0x11, 0x7E,
                    0x38, 0x3F, 0xF4, 0xA0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{514u, 515u, 516u, 517u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 58.
    {
        522u, // center
        {{
            // L0 outer.
            {
                {{
                    0x49, 0x1B, 0xD5, 0x6F, 0x61, 0x84, 0x10, 0x62,
                    0x28, 0x3F, 0x47, 0x18, 0x0C
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{527u, 528u, 529u, 530u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x58, 0x50, 0xF0, 0x7F, 0xE1, 0x87, 0x1C, 0x56,
                    0xA8, 0xFF, 0x6C, 0x40, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{523u, 524u, 525u, 526u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 59.
    {
        531u, // center
        {{
            // L0 outer.
            {
                {{
                    0x08, 0x3B, 0xE6, 0xAF, 0xA1, 0x84, 0x10, 0x62,
                    0x78, 0x3F, 0x0D, 0x14, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{536u, 537u, 538u, 539u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x14, 0xB0, 0xD0, 0x6F, 0x21, 0x85, 0x19, 0x46,
                    0xD8, 0xFF, 0x8C, 0xE0, 0x00
                }},
                PRISMA_LAYOUT_CORNERS,
                {{532u, 533u, 534u, 535u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 60.
    {
        540u, // center
        {{
            // L0 outer.
            {
                {{
                    0x41, 0x2A, 0xCE, 0x5F, 0xA1, 0x84, 0x10, 0x72,
                    0x08, 0x7F, 0x0F, 0x32, 0x03
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{545u, 546u, 547u, 548u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x38, 0xD0, 0xC3, 0x6F, 0x61, 0x87, 0x17, 0x66,
                    0x18, 0xFF, 0x00, 0x40, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{541u, 542u, 543u, 544u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 61.
    {
        549u, // center
        {{
            // L0 outer.
            {
                {{
                    0x47, 0x00, 0xDC, 0x9F, 0x61, 0x84, 0x10, 0x72,
                    0xB8, 0xBF, 0x0C, 0x3A, 0x01
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{554u, 555u, 556u, 557u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x48, 0x70, 0xE1, 0x5F, 0x21, 0x87, 0x11, 0x5E,
                    0x48, 0xBF, 0xCC, 0xC0, 0x03
                }},
                PRISMA_LAYOUT_CORNERS,
                {{550u, 551u, 552u, 553u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 62.
    {
        558u, // center
        {{
            // L0 outer.
            {
                {{
                    0x4F, 0x0A, 0xC8, 0x8F, 0x21, 0x84, 0x10, 0x62,
                    0x18, 0xFF, 0x47, 0x0E, 0x02
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{563u, 564u, 565u, 566u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0xB8, 0x80, 0xF0, 0x5F, 0xA1, 0x85, 0x15, 0x46,
                    0x58, 0x7F, 0x70, 0x90, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{559u, 560u, 561u, 562u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 63.
    {
        567u, // center
        {{
            // L0 outer.
            {
                {{
                    0x04, 0x1B, 0xDB, 0x0F, 0xE1, 0x84, 0x10, 0x62,
                    0x68, 0x7F, 0x02, 0x31, 0x07
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{572u, 573u, 574u, 575u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x88, 0x30, 0xE3, 0x4F, 0x61, 0x87, 0x14, 0x46,
                    0x78, 0x3F, 0xF8, 0x60, 0x02
                }},
                PRISMA_LAYOUT_CORNERS,
                {{568u, 569u, 570u, 571u}} // TL, TR, BR, BL
            }
        }}
    },

    // PRISMarker 64.
    {
        576u, // center
        {{
            // L0 outer.
            {
                {{
                    0x04, 0x36, 0xF5, 0x1F, 0xA1, 0x84, 0x10, 0x72,
                    0x38, 0x3F, 0x80, 0x12, 0x07
                }},
                PRISMA_LAYOUT_CARDINAL,
                {{581u, 582u, 583u, 584u}} // N, E, S, W
            },
            // L1 inner.
            {
                {{
                    0x0C, 0xD0, 0xD3, 0x9F, 0x61, 0x84, 0x1A, 0x7E,
                    0x38, 0x7F, 0x90, 0xA0, 0x01
                }},
                PRISMA_LAYOUT_CORNERS,
                {{577u, 578u, 579u, 580u}} // TL, TR, BR, BL
            }
        }}
    }

};

} // namespace n2_april
} // namespace predef
} // namespace aruco2
} // namespace cv
