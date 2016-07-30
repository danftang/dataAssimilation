#ifndef MODEL_H
#define MODEL_H

#include <eigen3/Eigen/Core>

template<int D>
class Model {
public:
	typedef Eigen::Matrix<double,D,1> State;
	typedef Eigen::Matrix<double,D,D> Jacobian;

	virtual void step(State &, Jacobian &)=0;
};

#endif
