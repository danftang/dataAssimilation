/*
 * Model.cpp
 *
 *  Created on: 4 Nov 2015
 *      Author: daniel
 */

#include "ThreeBodyModel.h"

ThreeBodyModel::ThreeBodyModel() :
	x(12),
	M(12,12),
	p1(x,M,0),
	p2(x,M,4),
	p3(x,M,8)
{
	// TODO Auto-generated constructor stub

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
void ThreeBodyModel::firstGuess(VectorXd &initialObs) {
    x.head<8>() = initialObs;
    p3.initState();
}
