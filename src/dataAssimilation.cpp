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
    ThreeBodyModel myModel;
    Telescope H;
    MatrixXd P0(12,12);		// co-variance of background state error
    VectorXd b0(12);		// background state
    VectorXd noise(8);
    VectorXd x0t(12);		// true start state

    std::vector<VectorXd> y(TIMESTEPS,VectorXd(8)); // observations
    std::vector<VectorXd> xt(TIMESTEPS,myModel.state()); // forward integral states
    std::vector<MatrixXd> Mt(TIMESTEPS,myModel.tangent()); // tangent linear models
    FourDVar fdvar(myModel, y, H, P0, b0);


    // --- initialise matrices
    // -----------------------

    P0.setZero();
    P0.block(0,0,2,2) = pow(Planet::l,2)*Matrix2d::Identity(); // position variance
    P0.block(2,2,2,2) = pow(1e-3*Planet::l/Planet::dt,2)*Matrix2d::Identity(); // velocity variance
    P0.block(4,4,4,4) = P0.block(0,0,4,4);
    P0.block(8,8,4,4) = P0.block(0,0,4,4);

    b0.setZero();
    x0t = myModel.state();
    std::cout << "True start state =" << std::endl << x0t << std::endl;

    // -- create observations
    // ----------------------

    for(t=0; t<TIMESTEPS; ++t) {
    	randomize(noise,gen);
    	y[t] = H(myModel.state()) + H.R()*noise;
    	myModel.step();

        std::cout << "Observation = " << std::endl;
        std::cout << y[t] << std::endl;
    }

    // -- now do data analysis
    // -----------------------

    // -- first guess at state
    myModel.firstGuess(y[0]);

    return 0;
}
