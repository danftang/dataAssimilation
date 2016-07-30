#ifndef TWOSTEPOBSERVATION_H
#define TWOSTEPOBSERVATION_H

#include <eigen3/Eigen/Core>
#include "observationOperator.h"

/**
 * Makes a composite observation at time t and t+1
 **/
class TwoStepObservation : public ObservationOperator {
public:
	TwoStepObservation(ObservationOperator &singleStepObs) : H(singleStepObs) {}

	Eigen::VectorXd operator()(Model &L) {
		Eigen::VectorXd obs0(H(L));
		Eigen::VectorXd state0(L.state());

		L.step();
		Eigen::VectorXd obs1(H(L));
		
		Eigen::VectorXd compositeObs(obs0.size() + obs1.size());
		
		compositeObs.head(obs0.size()) = obs0;
		compositeObs.tail(obs1.size()) = obs1;
		
		L.setState(state0);
		return(compositeObs);
	}
	
	Eigen::MatrixXd 	jacobian(Model &L) {
		Eigen::MatrixXd J0(H.jacobian(L));
		Eigen::MatrixXd	compositeJ(J0.rows()*2,J0.cols());
		Eigen::VectorXd state0(L.state());
		Eigen::MatrixXd	JX(L.jacobian());
			
		compositeJ.topRows(J0.rows()) = J0;
		L.step();
		compositeJ.bottomRows(J0.rows()) = H.jacobian(L)*JX;
		
		L.setState(state0);
		return(compositeJ);
	}
	
	ObservationOperator &H;
};

#endif
