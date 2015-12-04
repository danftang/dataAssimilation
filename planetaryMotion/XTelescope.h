/*
 * Telescope.h
 *
 *  Created on: 4 Nov 2015
 *      Author: daniel
 */

#ifndef TELESCOPE_H_
#define TELESCOPE_H_

#include "ObservationOperator.h"

class XTelescope: public ObservationOperator {
public:
	XTelescope();
	virtual ~XTelescope();

	VectorXd operator()(VectorXd &);
	MatrixXd &tangent(VectorXd &);
	MatrixXd &R();
	MatrixXd &Rinv(); // inverse covariance matrix


	MatrixXd H;
	MatrixXd Rm;
	MatrixXd Rmi;
	static const int N_OBSERVABLES;
};

#endif /* TELESCOPE_H_ */
