#ifndef LORENZ_H
#define LORENZ_H

#include <eigen3/Eigen/Core>
#include "model.h"

class Lorenz : public Model {
public:
	Lorenz();
	Lorenz(double Sigma, double Rho, double Beta);
	
	void step();
	Eigen::VectorXd	state() {return(S);}
	void setState(const Eigen::VectorXd &state);
	Eigen::MatrixXd jacobian();

	double 						dt;
	double 						sigma;
	double						beta;
	double						rho;
	Eigen::Vector3d  	S;
	Eigen::Vector3d		dS_dt;
};

#endif
