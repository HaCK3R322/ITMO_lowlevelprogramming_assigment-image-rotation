#pragma once
#include <inttypes.h>

enum BMPVersion {
    NONE = 0,
    CORE = 12,
    V3 = 40,
    V4 = 108,
    V5 = 124
};

#pragma pack(push, 1)
//all BMP formats
struct BMPFILEHEADER {
    uint8_t bfType[2];
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bOffBits;
};

//for versions 3, 4, 5
struct BMPINFOHEADER {
    uint32_t Size;
    uint32_t Width;
    uint32_t Height;
    uint16_t Planes;
    uint16_t BitCount;

    uint32_t Compression;
    uint32_t SizeImage;
    uint32_t XPelsPerMeter;
    uint32_t YPelsPerMeter;

    uint32_t ClrUsed;
    uint32_t ClrImportant;
};

//for versions 4, 5
struct BMPV4HEADER {
    uint32_t RedMask;
    uint32_t GreenMask;
    uint32_t BlueMask;
    uint32_t AlphaMask;
    uint32_t CSType;
    uint32_t Endpoints[8];
    uint32_t GammaRed;
    uint32_t GammaGreen;
    uint32_t GammaBlue;
};

//for version 5
struct BMPV5HEADER {
    uint32_t Intent;
    uint32_t ProfileData;
    uint32_t ProfileSize;
    uint32_t Reserved;
};

//////////////////////////////
//HEADERS FOR 16 and 32 BMPs//
//////////////////////////////

struct BMPHEADER16 {
    struct BMPFILEHEADER fileheader;

    uint32_t Size;
    uint16_t Width;
    uint16_t Height;
    uint16_t Planes;
    uint16_t BitCount;
};

struct BMPHEADER32 {
    struct BMPFILEHEADER fileheader;

    //version 3, 4, 5
    struct BMPINFOHEADER infoheader;

    //version 4, 5
    struct BMPV4HEADER v4header;

    //version 5
    struct BMPV5HEADER v5header;
};
#pragma pack(pop)
