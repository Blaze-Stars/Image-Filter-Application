#pragma once

#include "bmp.h"


// To check the file Format
bool checkFile(char *);

// Display Filter Menu options
char showFilterMenu();

// Applies filter according to the user selected filter option
void applyFilter(const char &filter, const int &height, const int &width, RGBTRIPLE **image);
