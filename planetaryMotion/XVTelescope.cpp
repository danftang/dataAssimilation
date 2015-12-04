/*
 * Telescope.cpp
 *
 *  Created on: 4 Nov 2015
 *      Author: daniel
 */

#include <iostream>
#include "XVTelescope.h"
#include "Planet.h"

const int XVTelescope::N_OBSERVABLES = 8;

XVTelescope::XVTelescope() :
	H(N_OBSERVABLES,12),
	Rm(N_OBSERVABLES,N_OBSERVABLES),
	Rmi(N_OBSERVABLES,N_OBSERVABLES)
{
    H.setIdentity();
    std::cout << "Observation operator = " << std::endl << H << std::endl;
    Rm.setIdentity();
//    Rm.setZero();
//    Rm.block(0,0,2,2) = pow(1e-11*Planet::AU,2)*Matrix2d::Identity(); // uncertainty in position observation
//    Rm.block(2,2,2,2) = Rm.block(0,0,2,2)/pow(Planet::dt,2); // uncertainty in velocity observations
//    Rm.block(4,4,4,4) = Rm.block(0,0,4,4); // uncertainty is same for both planets
    std::cout << "Observation co-variance = " << std::endl << Rm << std::endl;
    Rmi = Rm.inverse();
}

XVTelescope::~XVTelescope() {
	// TODO Auto-generated destructor stub
}

VectorXd XVTelescope::operator()(VectorXd &x) {
	return(H*x);
}
MatrixXd &XVTelescope::tangent(VectorXd &x) {
	return(H);
}
MatrixXd &XVTelescope::R() {
	return(Rm);
}
MatrixXd &XVTelescope::Rinv() {
	return(Rmi);
}
