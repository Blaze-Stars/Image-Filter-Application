/*
    Defination of the filters used in this Application.
    Prototype can be found in `helpers.h`
*/
#include <cmath>
#include <cstdlib>
#include "helpers.h"

// Definition for grayscale filter
void grayscale(int height, int width, RGBTRIPLE **image) {
    // code to be written
}

// Definition for Reflect filter (Horizontally)
void reflect(int height, int width, RGBTRIPLE **image) {
    // code to be written
}

// Definition for Blur Filter
void blur(int height, int width, RGBTRIPLE **image) {
    // code to be written
}

// Stops max value at 255 preventing overflow
int limitRGB(int RGB) {
    if (RGB > 255) {
        RGB = 255;
    }

    return RGB;
}

// Definition for Edges filter
void edges(int height, int width, RGBTRIPLE **image) {
    
    // create temporary values to store the calculations
    float sumBlueX {0.0};
    float sumGreenX {0.0};
    float sumRedX {0.0};
    float sumBlueY {0.0};
    float sumGreenY {0.0};
    float sumRedY {0.0};
    int gX {0};
    int gY {0};

    // create a temporary table of colors to not alter the calculations
    RGBTRIPLE tempImg[height][width];

    for (int i {0}; i < width; i++) {
        for (int j {0}; j < height; j++) {
            
            // reinitialize to 0 again after each iteration
            sumBlueX = 0.0;
            sumGreenX = 0.0;
            sumRedX = 0.0;
            sumBlueY = 0.0;
            sumGreenY = 0.0;
            sumRedY = 0.0;
            // sums values of the pixel and 8 neighboring ones after applying a modifier, skips iteration if it goes outside the pic
            for (int k {-1}; k < 2; k++) {
                if (j + k < 0 || j + k > height - 1) {
                    continue;
                }

                for (int h {-1}; h < 2; h++) {
                    if (i + h < 0 || i + h > width - 1) {
                        continue;
                    }

                    // calculates modifiers for vertical and horizantal borders
                    gX = k + 1 * k - k * abs(h);
                    gY = h + 1 * h - h * abs(k);

                    sumBlueX += image[j + k][i + h].rgbtBlue * gX;
                    sumGreenX += image[j + k][i + h].rgbtGreen * gX;
                    sumRedX += image[j + k][i + h].rgbtRed * gX;

                    sumBlueY += image[j + k][i + h].rgbtBlue * gY;
                    sumGreenY += image[j + k][i + h].rgbtGreen * gY;
                    sumRedY += image[j + k][i + h].rgbtRed * gY;
                }
            }

            // obtains the final values of the pixels combining X and Y calculations
            tempImg[j][i].rgbtBlue = limitRGB(round(sqrt(sumBlueX * sumBlueX + sumBlueY * sumBlueY)));
            tempImg[j][i].rgbtGreen = limitRGB(round(sqrt(sumGreenX * sumGreenX + sumGreenY * sumGreenY)));
            tempImg[j][i].rgbtRed = limitRGB(round(sqrt(sumRedX * sumRedX + sumRedY * sumRedY)));
        }
    }

    // copies values from temporary table
    for (int i {0}; i < width; i++) {
        for (int j {0}; j < height; j++) {
            image[j][i].rgbtBlue = tempImg[j][i].rgbtBlue;
            image[j][i].rgbtGreen = tempImg[j][i].rgbtGreen;
            image[j][i].rgbtRed = tempImg[j][i].rgbtRed;
        }
    }
}

// Definition for Sepia filter
void sepia(int height, int width, RGBTRIPLE **image) {
    
    // Iterating over each pixel
    for (int i {0}; i < height; ++i) {
        for (int j {0}; j < width; ++j) {

            // separately stored modified colured channel
            int sepiaRed   = (.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue);
            int sepiaGreen = (.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue);
            int sepiaBlue  = (.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue);

            // checking for boundary limit i.e 255 and storing correct values to image
            image[i][j].rgbtRed   = sepiaRed > 255 ? 255 : round(sepiaRed);
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : round(sepiaGreen);
            image[i][j].rgbtBlue  = sepiaBlue > 255 ? 255 : round(sepiaBlue);
        }
    }
}
