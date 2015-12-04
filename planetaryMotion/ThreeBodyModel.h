/*
 * Model.h
 *
 *  Created on: 4 Nov 2015
 *      Author: daniel
 */

#ifndef THREEBODYMODEL_H_
#define THREEBODYMODEL_H_

#include "Model.h"
#include "Planet.h"

class ThreeBodyModel : public Model {
public:
	ThreeBodyModel();

	void step();
	VectorXd &state();
	MatrixXd &tangent();
//	void firstGuess(VectorXd &);

    VectorXd x; 		// state vector
    MatrixXd M;			// Tangent linear model
    Planet p1;			// planet abstractions
    Planet p2;
    Planet p3;
    static const int N_VARS; // number of variables in the state

};

#endif /* THREEBODYMODEL_H_ */
