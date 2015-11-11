/*
 * FourDVar.h
 *
 *  Created on: 4 Nov 2015
 *      Author: daniel
 */

#ifndef FOURDVAR_H_
#define FOURDVAR_H_
#include <Eigen/Dense>
#include <vector>

//#include "LevMarSolver.h"
#include "ObservationOperator.h"
#include "Model.h"
#include "nloptEigen.hpp"

using namespace Eigen;

class FourDVar {
public:
	FourDVar(Model &, ObservationOperator &, std::vector<VectorXd> &, MatrixXd &, VectorXd &);

//	void observe(std::vector<VectorXd> &);
//	int df(const VectorXd &, MatrixXd &);		// jacobian of error
//	int operator()(const VectorXd &, VectorXd &); // error
    double operator()(Eigen::Map<const Eigen::VectorXd> &x, Eigen::Map<Eigen::VectorXd> &grad);
    double operator()(const Eigen::VectorXd &x, VectorXd &grad);


	void assimilate(VectorXd &);

//	VectorXd lambda; 	// multi-timestep-error adjoint model
	Model &model;		// the model
    std::vector<VectorXd> &y; // the observations
    ObservationOperator &H;
    MatrixXd &P0inv;	// inverse of co-variance of background state error
    VectorXd &b0;		// background state

    NloptEigen solver;


};

#endif /* FOURDVAR_H_ */
