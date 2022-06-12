/*
    Defination of the filters used in this Application.
    Prototype can be found in `helpers.h`
*/
#include <cmath>
#include <cstdlib>
#include "helpers.h"

// Defination for grayscale filter
void grayscale(int height, int width, RGBTRIPLE **image) {
    // code to be written
}

// Defination for Reflect filter (Horizontally)
void reflect(int height, int width, RGBTRIPLE **image) {
    // code to be written
}

// Defination for Blur Filter
void blur(int height, int width, RGBTRIPLE **image) {
    // code to be written
}

// stops max value at 255 preventing overflow
int limitRGB(int RGB) {
    if (RGB > 255) {
        RGB = 255;
    }

    return RGB;
}

// Defination for Edges filter
void edges(int height, int width, RGBTRIPLE **image) {
    // code to be written
}

// Defination for Sepia filter
void sepia(int height, int width, RGBTRIPLE **image) {
    for (int i {0}; i < height; ++i) {
        for (int j {0}; j < width; ++j) {
            int sepiaRed   {.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue};
            int sepiaGreen {.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue};
            int sepiaBlue  {.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue};

            image[i][j].rgbtRed   = sepiaRed > 255 ? 255 : round(sepiaRed);
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : round(sepiaGreen);
            image[i][j].rgbtBlue  = sepiaBlue > 255 ? 255 : round(sepiaBlue);
        }
    }
}
