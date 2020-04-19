#ifndef FIELD_H
#define FIELD_H

class Field
{
    public:
        double *data;
        int x1, x2, x3, x4, N;
        Field (int max1, int max2, int max3, int max4, int maxN);
        double& operator() (int q1, int q2, int q3, int q4, int qN);
        void cold_start();
        void hot_start();
};

#endif

