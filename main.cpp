#include <getopt.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include "helpers.h"

// main file
int main(int argc, char **argv) {
    try {
        // Define allowable filters
        const char *filtersOptions {"begrs"};

        // Get filter flag
        char filter {static_cast<char>(getopt(argc, argv, filtersOptions))};

        // Check validity
        if (filter == '?') {
            throw std::runtime_error {"Invalid filter."};
        }

        // Ensure only one filter
        if (getopt(argc, argv, filtersOptions) != -1) {
            throw std::runtime_error {"Only one filter allowed."};
        }

        // Ensure proper usage
        if (argc != optind + 2) {
            throw std::runtime_error {"Usage: filter [flag] infile outfile"};
        }

        // Open input file 
        FILE *inFile {fopen(argv[optind], "r")};
        // check readability
        if (inFile == nullptr) {
            throw std::runtime_error {"Could not read : " + static_cast<std::string>(argv[optind])};
        }

        // Open output file
        FILE *outFile {fopen(argv[optind + 1], "w")};
        // check writability
        if (outFile == nullptr) {
            throw std::runtime_error {"Could not create : " + static_cast<std::string>(argv[optind + 1])};
        }

        // Read inFile's BITMAPFILEHEADER
        BITMAPFILEHEADER bf;
        fread(&bf, sizeof(BITMAPFILEHEADER), 1, inFile);

        // Read inFile's BITMAPINFOHEADER
        BITMAPINFOHEADER bi;
        fread(&bi, sizeof(BITMAPINFOHEADER), 1, inFile);

        // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
        if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0) {
            fclose(outFile);
            fclose(inFile);
            
            throw std::runtime_error {"Unsupported file format."};
        }

        int height {abs(bi.biHeight)};
        int width  {abs(bi.biWidth)};

        // Allocate memory for image 2D array
        RGBTRIPLE **image {new RGBTRIPLE*[height]};
        for (int i{0}; i < height; ++i) {
               image[i] = new RGBTRIPLE[width];
        }

        // Checks for successful memory allocation
        if (image == nullptr) {
            fclose(inFile);
            fclose(outFile);

            throw std::runtime_error {"Not enough memory to store image."};
        }

        // Determine padding for scanlines
        size_t padding {(4 - (width * sizeof(RGBTRIPLE)) % 4) % 4};

        // Iterate over infile's scanlines
        for (int i {0}; i < height; i++) {
            // Read row into pixel array
            fread(*(image + i), sizeof(RGBTRIPLE), width, inFile);

            // Skip over padding
            fseek(inFile, padding, SEEK_CUR);
        }

        // Filter image
        switch (filter) {
            // Blur
            case 'b':
                blur(height, width, image);
                break;
            // Edges
            case 'e':
                edges(height, width, image);
                break;
            // Grayscale
            case 'g':
                grayscale(height, width, image);
                break;
            // Reflect
            case 'r':
                reflect(height, width, image);
                break;
            // Sepia
            case 's':
                sepia(height, width, image);
                break;
        }

        // Write outfile's BITMAPFILEHEADER
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outFile);

        // Write outfile's BITMAPINFOHEADER
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outFile);

        // Write new pixels to outfile
        for (int i {0}; i < height; ++i) {
            // Write row to outfile
            fwrite(*(image + i), sizeof(RGBTRIPLE), width, outFile);

            // Write padding at end of row
            for (size_t j {0}; j < padding; ++j) {
                fputc(0x00, outFile);
            }
        }

        // Free memory for image
        for (int i {0}; i < height; ++i) {
            delete [] image[i];
        }
        delete [] image;

        // Close inFile
        fclose(inFile);

        // Close outFile
        fclose(outFile);

    }
    catch (std::exception const &ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    
    return 0;
}
