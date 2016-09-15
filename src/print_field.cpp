#include <iostream>
#include "field.h"

void print_field(Field phi)
{
    for(int x = 0; x < phi.x1; x++)
        for(int y = 0; y < phi.x2; y++)
            for(int z = 0; z < phi.x3; z++)
                for(int t = 0; t < phi.x4; t++)
                {
                    for(int i = 0; i < phi.N; i++)
                    {
                        std::cout << "Lattice site Λ(" << x << "," << y << "," << z<< "," << t
                                  << "): ϕ_" << i << " = " << phi(x,y,z,t,i) << std::endl;
                    }
                    std::cout << std::endl;
                }
}

