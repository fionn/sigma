#include <cstdlib>
#include <cmath>
#include "field.hpp"
#include "pandora.hpp"
#include "action.hpp"
#include "metropolis.hpp"

bool metropolis(Field phi, int x1, int x2, int x3, int x4, int N, double lambda, double v, double delta)
{
    const int BETA = 1.0; // ahh!

    double variational = delta * pandora();
    double S = action(phi, x1, x2, x3, x4, N, 0, lambda, v);
    double S_prime = action(phi, x1, x2, x3, x4, N, variational, lambda, v);

    double r = exp(BETA * (S - S_prime));

    bool accept = false;
    if (r > drand48())
    {
        phi(x1, x2, x3, x4, N) += variational;
        accept = true;
    }

    return accept;
}

