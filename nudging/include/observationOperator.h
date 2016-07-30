#ifndef OBSERVATIONOP_H
#define OBSERVATIONOP_H

#include <eigen3/Eigen/Core>

class ObservationOperator {
public:

	virtual Eigen::VectorXd			operator()(Model &)=0; // observation operator
	virtual Eigen::MatrixXd 		jacobian(Model &)=0;		// 

};

#endif
