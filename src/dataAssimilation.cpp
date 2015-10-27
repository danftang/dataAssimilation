//============================================================================
// Name        : dataAssimilation.cpp
// Author      : Daniel Tang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <eigen3/Eigen/Dense>
#include "Planet.h"

using namespace std;

int main()
{
    Planet x[3];
    const double dt = 3600.0*24*7;
    const double TMAX = dt*3;
    double t;

    for(t=0; t<TMAX; t += dt) {
        x[0].step(x[1],x[2],dt);
        x[1].step(x[2],x[0],dt);
        x[2].step(x[0],x[1],dt);
        cout << x[0].x << endl << x[1].x << endl << x[2].x << endl << endl;
    }



    return 0;
}
