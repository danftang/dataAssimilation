/***
As described in "Spiral chaos in a predator-rey model
Gilpin 1979

Phase space is 3 dimensional N1,N2,N3

Equations of motion are

dNi/dt = Ni(ri - sum_j aijNj)

where aij are coeffs in i and j, and ri are coeffs in i

Populations are stored as population[i] = si(log(Ni)+bi),
where si=scale, bi=base, so that

dpi/dt = s(ri - sum_j aij e^(pi/s-b))


***/

#include <cmath>
#include "ContinuousModel.h"


ContinuousModel::ContinuousModel() :
    // values in Gilpin '79
    population{324,687,434},
    a{  {0.001,     0.001,     0.01},
        {0.0015,    0.001,     0.001},
        {-0.005,    -0.0005,   0.0}},
    r{1.0,1.0,-1.0},
    b{0.0,0.0,60.0},
    s{100.0,100.0,10.0},
    dt(0.1)
{
}

void ContinuousModel::step() {
    double predation[3];
    int i,j;
    for(i=0; i<3; ++i) {
        predation[i] = 0.0;
        for(j=0; j<3; ++j) {
//            predation[i] += a[i][j]*population[j];
            predation[i] += a[i][j]*std::exp(population[j]/s[j]-b[j]);
        }
    }
    for(i=0; i<3; ++i) {
//        population[i] += dt*(population[i]*(r[i] - predation[i]) + b[i]);
        population[i] += dt*(r[i] - predation[i])*s[i];
    }
}


