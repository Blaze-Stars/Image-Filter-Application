
#include <cstdint>

typedef uint8_t BYTE;
typedef uint32_t DWORD;
typedef uint16_t WORD;
typedef int32_t LONG;


typedef struct{
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} __attribute__((__packed__))
BITMAPFILEHEADER;

typedef struct{
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} __attribute__((__packed__))
BITMAPINFOHEADER;

typedef struct{
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;