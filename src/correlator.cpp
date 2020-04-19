#include "field.hpp"
#include "correlator.hpp"

double correlator(Field phi, int d)
{
    double C = 0;
    
    for (int x4 = 0; x4 < phi.x4; x4++)
        for (int x1 = 0; x1 < phi.x1; x1++)
            for (int x2 = 0; x2 < phi.x2; x2++)
                for (int x3 = 0; x3 < phi.x3; x3++)
                    for (int N = 0; N < phi.N; N++)
                        C += phi(x1, x2, x3, x4, N) * phi(x1, x2, x3, (x4 + d) % phi.x4, N);
    
    C /= (phi.x1 * phi.x2 * phi.x3);
    
    return C;
}

