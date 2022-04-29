#include <cstdint>


typedef uint8_t     BYTE;
typedef uint32_t    DWORD;
typedef int32_t     LONG;
typedef uint16_t    WORD;



class BITMAPFILEHEADER {

    public:

    WORD    bfType;
    DWORD   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfoffBits;

} __attribute__((__packed__));





class BITMAPINFOHEADER
{
    public:

    DWORD  biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
} __attribute__((__packed__));





class RGBTRIPLE
{
    public:

    BYTE  rgbtBlue;
    BYTE  rgbtGreen;
    BYTE  rgbtRed;
} __attribute__((__packed__));
