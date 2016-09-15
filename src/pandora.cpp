#include <cstdlib>
#include <cmath>
#include "pandora.h"

double pandora()        // This function uses the Box-Muller method to generate
{                       // Gaussianly distributed pseudo-random numbers.
    double v1, v2;
    double x;

    do
    {
        v1 = 2 * drand48() - 1;
        v2 = 2 * drand48() - 1;
    
        x = v1 * v1 + v2 * v2;
    }
    while (x >= 1);

    x = sqrt(-2 * log(x) / x) * v1;
    
    return x;
}

