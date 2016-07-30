#ifndef OBSERVATIONOP_H
#define OBSERVATIONOP_H

#include <eigen3/Eigen/Core>

template<int N>
class IObservationOp {
public:

	virtual Eigen::Vector<double,N>				operator()( &)=0; // observation operator
	virtual Eigen::Matrix<double,N,N> 		jacobian(Model &)=0;		// 

};

#endif
