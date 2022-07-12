#include <iostream>

#include "../include/helpers.h"
#include "../include/filters.h"


// Extracts file extension and checks if file is bmp
bool checkFile(char *file) {
    std::string storeFormat {};

    for (int i {0}; file[i] != '\0'; ++i) {
        if (file[i] == '.') {
            for (int j {i + 1}; file[j] != '\0'; ++j) {
                storeFormat += file[j];
            }
            
            break;
        }            
    }

    if (storeFormat == "bmp") {
        return true;
    }
    
    return false;
}

// Display Filter Menu options
char showFilterMenu() {
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
            return filter;
        }
        else if (filter == 'q') {
            return filter;
        }
        else {
            std::cout << "Invalid filter option.\nTry again..." << std::endl;
        }
    }
}

// Applies filter according to the user selected filter option
void applyFilterMenu(char &filter, int &height, int &width, RGBTRIPLE **image) {
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
}
