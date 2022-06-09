#include <cmath>
#include <cstdlib>
#include "helpers.h"

// Defination for grayscale filter
// Write code below this comment

// Defination for Reflect filter (Horizontally)
// Write code below this comment

// Defination for Blur Filter
// Write code below this comment

// stops max value at 255 preventing overflow
int limitRGB(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }

    return RGB;
}
// Defination for Edges filter
// Write code below this comment

// Defination for Sepia
// Write code below this comment