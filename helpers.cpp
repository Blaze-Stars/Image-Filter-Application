/*
    Defination of the filters used in this Application.
    Prototype can be found in `helpers.h`
*/
#include <cmath>
#include <cstdlib>
#include <string>
#include "helpers.h"

// Definition for grayscale filter
void grayscale(const int &height, const int &width, RGBTRIPLE **image) {
    // Iterating over each pixel
    int avg {0};
    
    for (int i {0}; i < height; ++i) {
        for (int j {0}; j < width; ++j) {
            // Averages the color intensity and then applies the same value to all the colors to get gray
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0f);

            image[i][j].rgbtBlue  = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed   = avg;
         }
     }
}

// Definition for Reflect filter (Horizontally)
void reflect(const int &height, const int &width, RGBTRIPLE **image) {
   for (int i {0}; i < height; ++i) {
        for (int j {0}; j < width / 2; ++j) {
            // Use of a temporary structure to swap values
            RGBTRIPLE tempImg;

            tempImg.rgbtBlue  = image[i][j].rgbtBlue;
            tempImg.rgbtGreen = image[i][j].rgbtGreen;
            tempImg.rgbtRed   = image[i][j].rgbtRed;

            // Swap pixels with the ones on the opposite side of the picture and viceversa
            image[i][j].rgbtBlue  = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed   = image[i][width - j - 1].rgbtRed;

            image[i][width - j - 1].rgbtBlue  = tempImg.rgbtBlue;
            image[i][width - j - 1].rgbtGreen = tempImg.rgbtGreen;
            image[i][width - j - 1].rgbtRed   = tempImg.rgbtRed;
        }
    } 
}

// Definition for Blur Filter
void blur(const int &height, const int &width, RGBTRIPLE **image) {
    // Initialize variables to 0
    int sumBlue  {0};
    int sumGreen {0};
    int sumRed   {0};
    int count    {0};

    // Create a temporary table of colors to not alter the calculations
    RGBTRIPLE tempImg[height][width];

    for (int i {0}; i < width; ++i) {
        for (int j {0}; j < height; ++j) {
            // Reinitialization of variables after each iteration
            sumBlue  = 0;
            sumGreen = 0;
            sumRed   = 0;
            count    = 0;

            // Sums values of the pixel and 8 neighboring ones, skips iteration if it goes outside the image
            for (int k {-1}; k < 2; ++k) {
                if (j + k < 0 || j + k > height - 1) {
                    continue;
                }

                for (int h {-1}; h < 2; ++h) {
                    if (i + h < 0 || i + h > width - 1) {
                        continue;
                    }

                    sumBlue  += image[j + k][i + h].rgbtBlue;
                    sumGreen += image[j + k][i + h].rgbtGreen;
                    sumRed   += image[j + k][i + h].rgbtRed;
                    ++count;
                }
            }

            // Averages the sum to make picture look blurrier
            tempImg[j][i].rgbtBlue  = round(sumBlue  / static_cast<float>(count));
            tempImg[j][i].rgbtGreen = round(sumGreen / static_cast<float>(count));
            tempImg[j][i].rgbtRed   = round(sumRed   / static_cast<float>(count));
        }
    }
    // Copies values from temporary table
    for (int i {0}; i < width; ++i) {
        for (int j {0}; j < height; ++j) {
            image[j][i].rgbtBlue  = tempImg[j][i].rgbtBlue;
            image[j][i].rgbtGreen = tempImg[j][i].rgbtGreen;
            image[j][i].rgbtRed   = tempImg[j][i].rgbtRed;
        }
    }
}

// Stops max value at 255 preventing overflow
int limitRGB(int RGB) {
    if (RGB > 255) {
        RGB = 255;
    }

    return RGB;
}

// Definition for Edges filter
void edges(const int &height, const int &width, RGBTRIPLE **image) {
    // Create temporary values to store the calculations
    float sumBlueX  {0.0f};
    float sumGreenX {0.0f};
    float sumRedX   {0.0f};
    float sumBlueY  {0.0f};
    float sumGreenY {0.0f};
    float sumRedY   {0.0f};

    // Modifiers for vertical and horizantal borders
    int gX {0};
    int gY {0};

    // Create a temporary table of colors to not alter the calculations
    RGBTRIPLE tempImg[height][width];

    for (int i {0}; i < width; ++i) {
        for (int j {0}; j < height; ++j) {
            // Reinitialize to 0 again after each iteration
            sumBlueX  = 0.0f;
            sumGreenX = 0.0f;
            sumRedX   = 0.0f;
            sumBlueY  = 0.0f;
            sumGreenY = 0.0f;
            sumRedY   = 0.0f;

            // Sums values of the pixel and 8 neighboring ones after applying a modifier, skips iteration if it goes outside the image
            for (int k {-1}; k < 2; ++k) {
                if (j + k < 0 || j + k > height - 1) {
                    continue;
                }

                for (int h {-1}; h < 2; ++h) {
                    if (i + h < 0 || i + h > width - 1) {
                        continue;
                    }

                    // Calculates modifiers for vertical and horizantal borders
                    gX = k + 1 * k - k * abs(h);
                    gY = h + 1 * h - h * abs(k);

                    sumBlueX  += image[j + k][i + h].rgbtBlue * gX;
                    sumGreenX += image[j + k][i + h].rgbtGreen * gX;
                    sumRedX   += image[j + k][i + h].rgbtRed * gX;

                    sumBlueY  += image[j + k][i + h].rgbtBlue * gY;
                    sumGreenY += image[j + k][i + h].rgbtGreen * gY;
                    sumRedY   += image[j + k][i + h].rgbtRed * gY;
                }
            }

            // Obtains the final values of the pixels combining X and Y calculations
            tempImg[j][i].rgbtBlue  = limitRGB(round(sqrt(sumBlueX * sumBlueX + sumBlueY * sumBlueY)));
            tempImg[j][i].rgbtGreen = limitRGB(round(sqrt(sumGreenX * sumGreenX + sumGreenY * sumGreenY)));
            tempImg[j][i].rgbtRed   = limitRGB(round(sqrt(sumRedX * sumRedX + sumRedY * sumRedY)));
        }
    }

    // Copies values from temporary table
    for (int i {0}; i < width; ++i) {
        for (int j {0}; j < height; ++j) {
            image[j][i].rgbtBlue  = tempImg[j][i].rgbtBlue;
            image[j][i].rgbtGreen = tempImg[j][i].rgbtGreen;
            image[j][i].rgbtRed   = tempImg[j][i].rgbtRed;
        }
    }
}

// Definition for Sepia filter
void sepia(const int &height, const int &width, RGBTRIPLE **image) {
    // Iterating over each pixel
    for (int i {0}; i < height; ++i) {
        for (int j {0}; j < width; ++j) {
            // Separately stored modified colured channel
            int sepiaRed   {static_cast<int>(.393 * image[i][j].rgbtRed) + static_cast<int>(.769 * image[i][j].rgbtGreen) + static_cast<int>(.189 * image[i][j].rgbtBlue)};
            int sepiaGreen {static_cast<int>(.349 * image[i][j].rgbtRed) + static_cast<int>(.686 * image[i][j].rgbtGreen) + static_cast<int>(.168 * image[i][j].rgbtBlue)};
            int sepiaBlue  {static_cast<int>(.272 * image[i][j].rgbtRed) + static_cast<int>(.534 * image[i][j].rgbtGreen) + static_cast<int>(.131 * image[i][j].rgbtBlue)};

            // Checking for boundary limit i.e 255 and storing correct values to image
            image[i][j].rgbtRed   = sepiaRed > 255 ? 255 : round(sepiaRed);
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : round(sepiaGreen);
            image[i][j].rgbtBlue  = sepiaBlue > 255 ? 255 : round(sepiaBlue);
        }
    }
}

// This Function checks file format
bool checkFile(char * file) {
    
    std::string storeFormat {};

    for (int i{0}; file[i] != '\0'; i++)
    {
        if (file[i] == '.') {
            for (int j{i}; file[j] != '\0'; j++)
                storeFormat += file[j];
            break;
        }            
    }

    if (storeFormat == ".bmp")
        return true;
    
    return false;
}