#include "field.hpp"
#include "metropolis.hpp"
#include "latticeupdate.hpp"

int latticeupdate(Field phi, double lambda, double v, double delta)
{
    int accept = 0;

    for (int x1 = 0; x1 < phi.x1; x1++)
        for (int x2 = 0; x2 < phi.x2; x2++)
            for (int x3 = 0; x3 < phi.x3; x3++)
                for (int x4 = 0; x4 < phi.x4; x4++)
                    for (int N = 0; N < phi.N; N++)
                    {
                        //metropolis(phi, x1, x2, x3, x4, N, lambda, nu, delta);
                        if(metropolis(phi, x1, x2, x3, x4, N, lambda, v, delta))
                            accept++;
                    }

    return accept;
}

