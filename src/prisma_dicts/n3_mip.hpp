#pragma once

#include "data.hpp"

namespace cv {
namespace aruco2 {
namespace predef {
namespace n3_mip {

// N3, ArUco MIP 36h12: 19 PRISMarkers.

static constexpr auto type = PRISMA_D3_ARUCO_MIP_36H12;
static constexpr auto aux = DICT_ARUCO_MIP_36h12;
static constexpr char name[] = "PRISMA_D3_ARUCO_MIP_36H12";

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
                    0x00, 0x20, 0xD3, 0x5F, 0x21, 0x84, 0x15, 0x7E,
                    0x38, 0xBF, 0xE8, 0x40, 0x03
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
                    0xCC, 0x90, 0xC3, 0x3F, 0x21, 0x86, 0x11, 0x6E,
                    0x08, 0xFF, 0xAC, 0xC0, 0x01
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
                    0xA8, 0x60, 0xE1, 0xDF, 0x61, 0x85, 0x1C, 0x52,
                    0x68, 0x7F, 0x70, 0x80, 0x03
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
                    0x9C, 0x50, 0xE1, 0x4F, 0x21, 0x87, 0x18, 0x72,
                    0xE8, 0x7F, 0x8C, 0xE0, 0x00
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
                    0xFC, 0xA0, 0xE2, 0x7F, 0x21, 0x84, 0x14, 0x6E,
                    0xB8, 0x3F, 0x34, 0x00, 0x01
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
                    0x60, 0x40, 0xF3, 0x7F, 0x21, 0x84, 0x1C, 0x7E,
                    0x98, 0xFF, 0x50, 0x40, 0x00
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
                    0x14, 0xC0, 0xF2, 0xDF, 0x61, 0x84, 0x10, 0x4E,
                    0x38, 0x7F, 0xE8, 0x10, 0x01
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
                    0x6C, 0xB0, 0xE2, 0xDF, 0x21, 0x85, 0x1A, 0x4A,
                    0x68, 0xBF, 0x58, 0x80, 0x01
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
                    0x04, 0xB0, 0xC0, 0xCF, 0xE1, 0x87, 0x17, 0x42,
                    0xA8, 0x7F, 0x0C, 0x90, 0x03
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
                    0x6C, 0x00, 0xC2, 0x5F, 0x61, 0x86, 0x14, 0x5A,
                    0xB8, 0xFF, 0x38, 0x00, 0x03
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
                    0x1C, 0x80, 0xC2, 0x5F, 0x21, 0x86, 0x1C, 0x52,
                    0xF8, 0xBF, 0xEC, 0xC0, 0x01
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
                    0xA4, 0x70, 0xC2, 0xCF, 0xA1, 0x87, 0x17, 0x66,
                    0x48, 0xBF, 0x28, 0x70, 0x01
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
                    0xC8, 0xD0, 0xD3, 0x7F, 0x61, 0x84, 0x14, 0x46,
                    0xD8, 0x7F, 0xE0, 0xC0, 0x01
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
                    0xCC, 0x20, 0xD2, 0x9F, 0xA1, 0x86, 0x15, 0x7E,
                    0x08, 0x7F, 0xF8, 0x70, 0x02
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
                    0x7C, 0x30, 0xD3, 0x1F, 0xA1, 0x86, 0x11, 0x6E,
                    0x58, 0xFF, 0x20, 0x30, 0x03
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
                    0x78, 0xC0, 0xC1, 0x3F, 0xA1, 0x87, 0x17, 0x4A,
                    0x78, 0x7F, 0x70, 0x30, 0x00
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
                    0x78, 0xC0, 0xF3, 0x1F, 0x21, 0x85, 0x1C, 0x7A,
                    0x48, 0x3F, 0xB4, 0x90, 0x00
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
                    0x8C, 0x30, 0xC3, 0xDF, 0x61, 0x85, 0x13, 0x42,
                    0x78, 0xFF, 0xA4, 0x40, 0x03
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
                    0xD8, 0xD0, 0xC1, 0x8F, 0x61, 0x87, 0x14, 0x52,
                    0xC8, 0xBF, 0x30, 0x30, 0x02
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
    }

};

} // namespace n3_mip
} // namespace predef
} // namespace aruco2
} // namespace cv
