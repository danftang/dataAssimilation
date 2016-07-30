#ifndef YOBSERVATION_H
#define YOBSERVATION_H

#include <eigen3/Eigen/Core>
#include "observationOperator.h"

class YObservation : public ObservationOperator {
public:

	Eigen::VectorXd operator()(Model &L) {
		Eigen::VectorXd obs(1);
		obs << L.state()[1];
		return(obs);
	}
	Eigen::MatrixXd 	jacobian(Model &L) {
			Eigen::MatrixXd j(1,3);
			j << 0.0, 1.0, 0.0;
			return(j);
	}
};

#endif
