#include <iostream>
#include <string>
#include <cctype>

#include "include/filters.h"
#include "include/helpers.h"

// main file
int main(int argc, char **argv) {
    try {
        // Ensure proper usage
        if (argc != 3) {
            throw std::invalid_argument {"Usage: ./filter infile outfile"};
        }

        // checks same input output file
        if (static_cast<std::string>(argv[1]) == static_cast<std::string>(argv[2])) {
            throw std::invalid_argument {static_cast<std::string>(argv[1]) + ": input file can't same as output file"};
        }

        // checks the input file format
        if (!checkFile(argv[1])) {
            throw std::invalid_argument {static_cast<std::string>(argv[1]) + ": unsupported File Format!"};
        }

        // Open input file 
        FILE *inFile {fopen(argv[1], "r")};

        // check readability
        if (inFile == nullptr) {
            throw std::invalid_argument {"Could not read : " + static_cast<std::string>(argv[1])};
        }

        // Read inFile's BITMAPFILEHEADER
        BITMAPFILEHEADER bf;
        fread(&bf, sizeof(BITMAPFILEHEADER), 1, inFile);

        // Read inFile's BITMAPINFOHEADER
        BITMAPINFOHEADER bi;
        fread(&bi, sizeof(BITMAPINFOHEADER), 1, inFile);

        // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
        if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0) {
            fclose(inFile);

            throw std::runtime_error {static_cast<std::string>(argv[1]) + "Unsupported file format."};
        }

        // checks the output file format
        if (!checkFile(argv[2])) {
            fclose(inFile);

            throw std::invalid_argument {static_cast<std::string>(argv[2]) + ": unsupported File Format!"};
        }

        // Open output file
        FILE *outFile {fopen(argv[2], "w")};
        
        // check writability
        if (outFile == nullptr) {
            fclose(inFile);

            throw std::runtime_error {"Could not create : " + static_cast<std::string>(argv[2])};
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

        // Ask user filter choice and store
        char filter {showFilterMenu()};
        
        // Apply filter only if the user not opted to quit 
        if (filter != 'q') {
            applyFilterMenu(filter, height, width, image);
        } else {
            std::cout << "Process terminated..." << std::endl;
            fclose(inFile);
            fclose(outFile);

            return 1;
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
        return 2;
    }
    
    return 0;
}
