/*
 * Telescope.cpp
 *
 *  Created on: 4 Nov 2015
 *      Author: daniel
 */

#include <iostream>
#include "XTelescope.h"
#include "Planet.h"
#include "ThreeBodyModel.h"

const int XTelescope::N_OBSERVABLES = 6;

XTelescope::XTelescope() :
	H(N_OBSERVABLES,ThreeBodyModel::N_VARS),
	Rm(N_OBSERVABLES,N_OBSERVABLES),
	Rmi(N_OBSERVABLES,N_OBSERVABLES)
{
    H.setZero();
    H(0,0) = 1.0;
    H(1,1) = 1.0;
    H(2,4) = 1.0;
    H(3,5) = 1.0;
    H(4,6) = 1.0;
    H(5,9) = 1.0;
//    H(6,14) = 1.0;
    std::cout << "Observation operator = " << std::endl << H << std::endl;
    Rm.setIdentity();
    Rm(2,2) = 0.00001;
    Rm(5,5) = 0.00001;
//    Rm(6,6) = 0.0001;
    std::cout << "Observation co-variance = " << std::endl << Rm << std::endl;
    Rmi = Rm.inverse();
}

XTelescope::~XTelescope() {
	// TODO Auto-generated destructor stub
}

VectorXd XTelescope::operator()(VectorXd &x) {
	return(H*x);
}
MatrixXd &XTelescope::tangent(VectorXd &x) {
	return(H);
}
MatrixXd &XTelescope::R() {
	return(Rm);
}
MatrixXd &XTelescope::Rinv() {
	return(Rmi);
}
