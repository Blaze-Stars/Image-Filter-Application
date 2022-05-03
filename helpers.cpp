#include <math.h>
#include <stdlib.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE **image)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // averages the color intensity and then applies the same value to all the colors to get gray
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE **image)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // use of a temporary structure to swap values
            RGBTRIPLE tempImg;

            tempImg.rgbtBlue = image[i][j].rgbtBlue;
            tempImg.rgbtGreen = image[i][j].rgbtGreen;
            tempImg.rgbtRed = image[i][j].rgbtRed;

            // swap pixels with the ones on the opposite side of the picture and viceversa
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            image[i][width - j - 1].rgbtBlue = tempImg.rgbtBlue;
            image[i][width - j - 1].rgbtGreen = tempImg.rgbtGreen;
            image[i][width - j - 1].rgbtRed = tempImg.rgbtRed;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE **image)
{
    int sumBlue;
    int sumGreen;
    int sumRed;
    int count;
    //create a temporary table of colors to not alter the calculations
    RGBTRIPLE tempImg[height][width];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            count = 0;

            // sums values of the pixel and 8 neighboring ones, skips iteration if it goes outside the pic
            for (int k = -1; k < 2; k++)
            {
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }

                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)
                    {
                        continue;
                    }

                    sumBlue += image[j + k][i + h].rgbtBlue;
                    sumGreen += image[j + k][i + h].rgbtGreen;
                    sumRed += image[j + k][i + h].rgbtRed;
                    count++;
                }
            }

            // averages the sum to make picture look blurrier
            tempImg[j][i].rgbtBlue = round(sumBlue / (float)count);
            tempImg[j][i].rgbtGreen = round(sumGreen / (float)count);
            tempImg[j][i].rgbtRed = round(sumRed / (float)count);
        }
    }

    //copies values from temporary table
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = tempImg[j][i].rgbtBlue;
            image[j][i].rgbtGreen = tempImg[j][i].rgbtGreen;
            image[j][i].rgbtRed = tempImg[j][i].rgbtRed;
        }
    }
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

// Detect edges
void edges(int height, int width, RGBTRIPLE **image)
{
    // create temporary values to store the calculations
    float sumBlueX;
    float sumGreenX;
    float sumRedX;
    float sumBlueY;
    float sumGreenY;
    float sumRedY;
    int gX;
    int gY;

    // create a temporary table of colors to not alter the calculations
    RGBTRIPLE tempImg[height][width];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sumBlueX = 0.0;
            sumGreenX = 0.0;
            sumRedX = 0.0;
            sumBlueY = 0.0;
            sumGreenY = 0.0;
            sumRedY = 0.0;

            // sums values of the pixel and 8 neighboring ones after applying a modifier, skips iteration if it goes outside the pic
            for (int k = -1; k < 2; k++)
            {
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }

                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)
                    {
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
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = tempImg[j][i].rgbtBlue;
            image[j][i].rgbtGreen = tempImg[j][i].rgbtGreen;
            image[j][i].rgbtRed = tempImg[j][i].rgbtRed;
        }
    }
}
