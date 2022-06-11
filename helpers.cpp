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
int limitRGB(int RGB)
{
    if (RGB > 255)
    {
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
    // code to be written
}