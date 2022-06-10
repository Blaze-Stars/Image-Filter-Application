#include <getopt.h>
#include <iostream>
#include <string>
// #include <cstdio>
// #include <stdexcept>
// #include <cstdlib>

#include "helpers.h"

// using namespace std;

// main file
int main(int argc, char **argv)
{
    try {
        // Define allowable filters
        const char *filtersOptions {"begrs"};

        // Get filter flag
        char filter {static_cast<char>(getopt(argc, argv, filtersOptions))};

        // check validity
        if (filter == '?') {
            throw std::string {"Invalid filter."};
        }

        // Ensure only one filter
        if (getopt(argc, argv, filtersOptions) != -1) {
            throw std::string {"Only one filter allowed."};
        }

        // Ensure proper usage
        if (argc != optind + 2) {
            throw std::string {"Usage: filter [flag] infile outfile"};
        }

        // Open input file and check
        FILE *inptr {fopen(argv[optind], "r")};
        if (inptr == nullptr) {
            throw std::string {"Could not read : " + static_cast<std::string>(argv[optind])};
        }

        // open output file
        FILE *outptr {fopen(argv[optind + 1], "w")};
        if (outptr == nullptr) {
            throw std::string {"Could not create : " + static_cast<std::string>(argv[optind + 1])};
        }


    }
    catch(std::string &ex) {
        std::cerr << ex << std::endl;
        return 1;
    }
    

    return 0;
}
