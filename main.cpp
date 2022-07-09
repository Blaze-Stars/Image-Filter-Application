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

        // checks the input file format
        if (!checkFile(argv[1])) {
             throw std::runtime_error {static_cast<std::string>(argv[1]) + ": unsupported File Format!"};
        }

        // Open input file 
        FILE *inFile {fopen(argv[1], "r")};

        // check readability
        if (inFile == nullptr) {
            throw std::runtime_error {"Could not read : " + static_cast<std::string>(argv[1])};
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
            throw std::runtime_error {static_cast<std::string>(argv[2]) + ": unsupported File Format!"};
        }

        // Open output file
        FILE *outFile {fopen(argv[2], "w")};
        
        // check writability
        if (outFile == nullptr) {
            throw std::runtime_error {"Could not create : " + static_cast<std::string>(argv[2])};
        }

        // Get filter option
        char filter {'\0'};

        // Define allowable filters
        std::string filtersOptions {"begrs"};

        // To read input option(s) from terminal
        std::string instr;

        while(true) {
            // Filter menu
            std::cout << "\n\n FILTER    : OPTION" << std::endl;
            std::cout << " ------------------" << std::endl;
            std::cout << " Blur        : b\n Edge        : e\n GrayScale   : g\n Reflect     : r\n Sepia       : s\n" << std::endl;
            std::cout << " To QUIT press    : [q]" << std::endl;
            std::cout << "Enter option :";
            std::cin  >> instr;

            // Ensure only one filter
            if (instr.length() != 1) {
                std::cout << "Only one option allowed.\nTry again..." << std::endl;
                continue;
            }

            filter = instr.at(0);
            filter = tolower(filter);
            
            // check validates option
            if (filtersOptions.find(filter) != std::string::npos) {
                break;
            }
            else if (filter == 'q') {
                throw std::runtime_error {"Process terminated..."};
            }
            else {
                std::cout << "Invalid filter option.\nTry again..." << std::endl;
            }
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
                std::cout << "Applied Blur filter successfully..." << std::endl;
                blur(height, width, image);
                break;

            // Edges
            case 'e':
                std::cout << "Applied Edge Filter successfully..." << std::endl;
                edges(height, width, image);
                break;

            // Grayscale
            case 'g':
                std::cout << "Applied Grayscale filter successfully..." << std::endl;
                grayscale(height, width, image);
                break;

            // Reflect
            case 'r':
                std::cout << "Applied Reflect filter successfully..." << std::endl;
                reflect(height, width, image);
                break;

            // Sepia
            case 's':
                std::cout << "Applied Sepia filter successfully..." << std::endl;
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
