//============================================================================
// Name        : dataAssimilation.cpp
// Author      : Daniel Tang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>
#include "Planet.h"

using namespace Eigen;

void randomize(VectorXd &v, std::default_random_engine &gen) {
	int i;
	std::normal_distribution<> gaussian(0,1.0);
	for(i=0; i<v.size(); ++i) {
		v[i] = gaussian(gen);
	}
}




int main()
{
    const int TIMESTEPS = 3;
    int t;
	std::default_random_engine gen;

    VectorXd x(12); 		// state vector
    MatrixXd H(8,12); 		// obervation operator
    MatrixXd M(12,12);		// Tangent linear model
    MatrixXd R(8,8);		// co-variance matrix of the observation error
    MatrixXd Rinv(8,8);		// inverse of co-variance matrix of the observation error
    MatrixXd P0(12,12);		// co-variance of background state error
    VectorXd b0(12);		// background state
    VectorXd noise(8);
    VectorXd x0t(12);		// true start state
    VectorXd lambda(12);

    std::vector<VectorXd> y(TIMESTEPS,VectorXd(8)); // observations
    std::vector<VectorXd> xt(TIMESTEPS,x); // forward integral states
    std::vector<MatrixXd> Mt(TIMESTEPS,M); // tangent linear models


    Planet p1(x,M,0);			// planet abstractions
    Planet p2(x,M,4);
    Planet p3(x,M,8);

    // --- initialise matrices
    // -----------------------
    H.setIdentity();
    std::cout << "Observation operator = " << std::endl << H << std::endl;

    R.setZero();
    R.block(0,0,2,2) = pow(1e-4*Planet::AU,2)*Matrix2d::Identity(); // uncertainty in position observation
    R.block(2,2,2,2) = R.block(0,0,2,2)/pow(Planet::dt,2); // uncertainty in velocity observations
    R.block(4,4,4,4) = R.block(0,0,4,4); // uncertainty is same for both planets
    std::cout << "Observation co-variance = " << std::endl << R << std::endl;

    P0.setZero();
    P0.block(0,0,2,2) = pow(Planet::l,2)*Matrix2d::Identity(); // position variance
    P0.block(2,2,2,2) = pow(1e-3*Planet::l/Planet::dt,2)*Matrix2d::Identity(); // velocity variance
    P0.block(4,4,4,4) = P0.block(0,0,4,4);
    P0.block(8,8,4,4) = P0.block(0,0,4,4);

    b0.setZero();

    x0t = x;
    std::cout << "True start state =" << std::endl << x0t << std::endl;

    // -- create observations
    // ----------------------

    for(t=0; t<TIMESTEPS; ++t) {
    	randomize(noise,gen);
    	y[t] = H*x + R*noise;
        p1.step(p2,p3);
        p2.step(p3,p1);
        p3.step(p1,p2);

        std::cout << "Observation = " << std::endl;
        std::cout << y[t] << std::endl;
    }


    // -- now do data analysis
    // -----------------------

    // -- first guess
    x.head<8>() = y[0];
    p3.initState();

    // -- calculate Jacobian
    // -- integrate forward
    for(t=0; t<TIMESTEPS-1; ++t) {
    	xt[t] = x;
        p1.step(p2,p3);
        p2.step(p3,p1);
        p3.step(p1,p2);
    	Mt[t] = M;
    }
    xt[t] = x;
    Mt[t].setZero();

    // -- project error backwards
    Rinv = R.inverse();
    lambda.setZero();
    for(t=TIMESTEPS-1; t>=0; --t) {
        lambda = Mt[t].transpose()*lambda + H.transpose()*Rinv*(H*xt[t]-y[t]);
    }
    lambda += P0.inverse()*xt[0];

    return 0;
}
