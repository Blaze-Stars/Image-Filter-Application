// To be Included the header file "bmp.h"
#include "bmp.h"

// Convert Image to grayscale
void grayscale(int height,int width,RGBTRIPLE **image);

// Reflect image horizontally
void reflect(int height,int width,RGBTRIPLE **image);

// Detect edges
void edges(int height,int width,RGBTRIPLE **image);

// Blur image
void blur(int height,int width,RGBTRIPLE **image);

// Sepia image
void sepia(int height,int width,RGBTRIPLE **image);