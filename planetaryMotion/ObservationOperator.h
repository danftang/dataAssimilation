/*
 * ObservationOperator.h
 *
 *  Created on: 4 Nov 2015
 *      Author: daniel
 */

#ifndef OBSERVATIONOPERATOR_H_
#define OBSERVATIONOPERATOR_H_
#include <eigen3/Eigen/Dense>

using namespace Eigen;

class ObservationOperator {
public:
	virtual ~ObservationOperator() {};
	virtual VectorXd operator ()(VectorXd &)=0;
	virtual MatrixXd &tangent(VectorXd &)=0; // tangent linear
	virtual MatrixXd &R()=0; // covariance matrix
	virtual MatrixXd &Rinv()=0; // inverse covariance matrix
};



#endif /* OBSERVATIONOPERATOR_H_ */
