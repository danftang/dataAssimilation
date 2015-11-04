/*
 * FourDVar.h
 *
 *  Created on: 4 Nov 2015
 *      Author: daniel
 */

#ifndef FOURDVAR_H_
#define FOURDVAR_H_
#include <eigen3/Eigen/Dense>
#include <vector>
using namespace Eigen;

class FourDVar {
public:
	FourDVar(Model &, ObservationOperator &, MatrixXd &, VectorXd &);

	void calcAdjoint(VectorXd &, std::vector<VectorXd> &);
	void assimilate(std::vector<VectorXd> &);

//	VectorXd lambda; 	// multi-timestep-error adjoint model
	Model &model;		// the model
//    std::vector<VectorXd> &y; // the observations
    ObservationOperator &H;
    MatrixXd &P0;		// co-variance of background state error
    VectorXd &b0;		// background state


};

#endif /* FOURDVAR_H_ */
