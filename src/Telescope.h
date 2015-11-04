/*
 * Telescope.h
 *
 *  Created on: 4 Nov 2015
 *      Author: daniel
 */

#ifndef TELESCOPE_H_
#define TELESCOPE_H_

#include "ObservationOperator.h"

class Telescope: public ObservationOperator {
public:
	Telescope();
	virtual ~Telescope();

	VectorXd operator()(VectorXd &);
	MatrixXd &tangent(VectorXd &);
	MatrixXd &R();

	MatrixXd H;
	MatrixXd Rm;
};

#endif /* TELESCOPE_H_ */
