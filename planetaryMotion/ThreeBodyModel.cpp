/*
 * Model.cpp
 *
 *  Created on: 4 Nov 2015
 *      Author: daniel
 */

#include "ThreeBodyModel.h"

const int ThreeBodyModel::N_VARS = 15;

ThreeBodyModel::ThreeBodyModel() :
	x(N_VARS),
	M(N_VARS,N_VARS),
	p1(x,M,0),
	p2(x,M,5),
	p3(x,M,10)
{
    // Fill in null part of tangent linear model (parameters)
    // M(12,12) = 1.0;
}

void ThreeBodyModel::step() {
    p1.step(p2,p3);
    p2.step(p3,p1);
    p3.step(p1,p2);
}

VectorXd &ThreeBodyModel::state() {
	return(x);
}

MatrixXd &ThreeBodyModel::tangent() {
	return(M);
}

/**
 * Set state to first guess given observation vector at time t=0
 */
//void ThreeBodyModel::firstGuess(VectorXd &initialObs) {
//    x.head<8>() = initialObs;
//    p3.initState();
//}
