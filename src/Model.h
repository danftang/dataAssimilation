/*
 * Model.h
 *
 *  Created on: 4 Nov 2015
 *      Author: daniel
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <eigen3/Eigen/Dense>

using namespace Eigen;


class Model {
public:
	virtual ~Model() {};
	virtual void 		step()=0;
	virtual VectorXd &	state()=0;
	virtual MatrixXd &	tangent()=0;

};


#endif /* MODEL_H_ */
