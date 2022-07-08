#include "../include/helpers.h"

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
