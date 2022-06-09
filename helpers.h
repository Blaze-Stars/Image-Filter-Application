#include "bmp.h"
#include <vector>
using namespace std;

// Convert image to grayscale
void grayscale(int, int, std::vector<std::vector<RGBTRIPLE>>);

// Reflect image horizontally
void reflect(int, int, std::vector<std::vector<RGBTRIPLE>>);

// Detect edges
void edges(int, int, std::vector<std::vector<RGBTRIPLE>>);

// Blur image
void blur(int, int, std::vector<std::vector<RGBTRIPLE>>);

// Sepia image
void sepia(int, int, std::vector<std::vector<RGBTRIPLE>>);

