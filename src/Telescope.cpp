/*
 * Telescope.cpp
 *
 *  Created on: 4 Nov 2015
 *      Author: daniel
 */

#include <iostream>
#include "Telescope.h"
#include "Planet.h"

Telescope::Telescope() :
	H(8,12),
	Rm(8,8),
	Rmi(8,8)
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

Telescope::~Telescope() {
	// TODO Auto-generated destructor stub
}

VectorXd Telescope::operator()(VectorXd &x) {
	return(H*x);
}
MatrixXd &Telescope::tangent(VectorXd &x) {
	return(H);
}
MatrixXd &Telescope::R() {
	return(Rm);
}
MatrixXd &Telescope::Rinv() {
	return(Rmi);
}
