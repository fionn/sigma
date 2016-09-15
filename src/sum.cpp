#include "field.h"
#include "sum.h"

double sigmasum(Field phi)
{
    double sigma = 0;
    
    for (int x1 = 0; x1 < phi.x1; x1++)
        for (int x2 = 0; x2 < phi.x2; x2++)
            for (int x3 = 0; x3 < phi.x3; x3++)
                for (int x4 = 0; x4 < phi.x4; x4++)
                    for (int N = 0; N < phi.N; N++)
                        sigma += phi(x1, x2, x3, x4, N) * phi(x1, x2, x3, x4, N);
    
    sigma /= (phi.x1 * phi.x2 * phi.x3);
    
    return sigma;
}

