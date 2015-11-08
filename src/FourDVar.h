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

#include "LevMarSolver.h"
#include "ObservationOperator.h"
#include "Model.h"

using namespace Eigen;

class FourDVar : public LevMarSolver<FourDVar> {
public:
	FourDVar(Model &, ObservationOperator &, std::vector<VectorXd> &, MatrixXd &, VectorXd &);

//	void observe(std::vector<VectorXd> &);
	int df(const VectorXd &, MatrixXd &);		// jacobian of error
	int operator()(const VectorXd &, VectorXd &); // error


	void assimilate(VectorXd &);

//	VectorXd lambda; 	// multi-timestep-error adjoint model
	Model &model;		// the model
    std::vector<VectorXd> &y; // the observations
    ObservationOperator &H;
    MatrixXd &P0inv;	// inverse of co-variance of background state error
    VectorXd &b0;		// background state


};

#endif /* FOURDVAR_H_ */
