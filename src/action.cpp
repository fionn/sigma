#include "field.h"
#include "action.h"

double gradient(Field phi, int x1, int x2, int x3, int x4, int N)
{
    double neighbours = 
        phi(x1 + 1, x2, x3, x4, N) + phi(x1 - 1, x2, x3, x4, N) +
        phi(x1, x2 + 1, x3, x4, N) + phi(x1, x2 - 1, x3, x4, N) +
        phi(x1, x2, x3 + 1, x4, N) + phi(x1, x2, x3 - 1, x4, N) +
        phi(x1, x2, x3, x4 + 1, N) + phi(x1, x2, x3, x4 - 1, N);

    double grad = phi(x1, x2, x3, x4, N) - neighbours / 8;

    return grad;
}

double action(Field phi, int x1, int x2, int x3, int x4, int N, double variation, double lambda, double v)
{
    phi(x1, x2, x3, x4, N) += variation;
    double dphi = gradient(phi, x1, x2, x3, x4, N);

    double S = 0, phi2 = 0;
    for(int i = 0; i < phi.N; ++i)
    {
        phi2 += phi(x1, x2, x3, x4, i) * phi(x1, x2, x3, x4, i);
        S += dphi * dphi;
    }

    S += lambda * (phi2 - v * v) * (phi2 - v * v);

    return S;
}

