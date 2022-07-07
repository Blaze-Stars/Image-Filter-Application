#include "bmp.h"

// Convert Image to grayscale
void grayscale(const int &, const int &, RGBTRIPLE **);

// Reflect image horizontally
void reflect(const int &, const int &, RGBTRIPLE **);

// Blur image
void blur(const int &, const int &, RGBTRIPLE **);

// Detect edges
void edges(const int &, const int &, RGBTRIPLE **);

// Sepia image
void sepia(const int &, const int &, RGBTRIPLE **);

// To check the file Format
bool checkFile(char *);