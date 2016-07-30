#include <iostream>
#include "synchronizedSystem.h"

void SynchronizedSystem::step() {
	Eigen::MatrixXd 		J;
	Eigen::VectorXd 		nudge;
	Eigen::MatrixXd 		Jh;
	Eigen::RowVectorXd 	dE_dXt;
	Eigen::VectorXd 		dH;
	double 							scale;
	
	J = driven.jacobian();
	driver.step();
	driven.step();

	Jh = H.jacobian(driven);
	dH = H(driven)-H(driver);
	
	dE_dXt = dH.transpose()*Jh*J;
	scale = dE_dXt*dE_dXt.transpose();
	if(scale < 1e-15) return;
	nudge = (J*dE_dXt.transpose())/scale;

//	nudge << 0.0, 1.0/dH[0], 0,0; // simple nudging

	driven.setState(driven.state() - nudge*dH.transpose()*dH);

// std::cout << dH.transpose() << " " << (H(driven)-H(driver)).transpose() << std::endl;
}


double SynchronizedSystem::err() {
	Eigen::VectorXd e(driven.state() - driver.state());
	return(e.transpose()*e);
}
