#include <cstdlib>
#include "field.hpp"

Field::Field (int max1, int max2, int max3, int max4, int maxN)
{
    x1 = max1;
    x2 = max2;
    x3 = max3;
    x4 = max4;
    N = maxN;

    data = new double [max1 * max2 * max3 * max4 * maxN];
}

double& Field::operator() (int q1, int q2, int q3, int q4, int qN)
{
    q1 += x1;
    q2 += x2;
    q3 += x3;
    q4 += x4;

    return data[(q1 % x1) + x1 * ((q2 % x2) + x2 * ((q3 % x3) + x3 * ((q4 % x4) + x4 * qN)))]; 
}

void Field::cold_start()
{
    for (int x1_it = 0; x1_it < x1; x1_it++)
        for (int x2_it = 0; x2_it < x2; x2_it++)
            for (int x3_it = 0; x3_it < x3; x3_it++)
                for (int x4_it = 0; x4_it < x4; x4_it++)
                    for (int N_it = 0; N_it < N; N_it++)
                        data[(x1_it) + x1 * ((x2_it) + x2 * ((x3_it) + x3 * ((x4_it) + x4 * N_it)))] = 0.0;
}

void Field::hot_start()
{
    const double temperature = 1.0;
    for (int x1_it = 0; x1_it < x1; x1_it++)
        for (int x2_it = 0; x2_it < x2; x2_it++)
            for (int x3_it = 0; x3_it < x3; x3_it++)
                for (int x4_it = 0; x4_it < x4; x4_it++)
                    for (int N_it = 0; N_it < N; N_it++)
                        data[(x1_it) + x1 * ((x2_it) + x2 * ((x3_it) + x3 * ((x4_it) + x4 * N_it)))] = temperature * drand48();
}

