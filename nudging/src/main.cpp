#include <iostream>
#include <cmath>
#include "lorenz.h"
#include "synchronizedSystem.h"
#include "xyObservation.h"
#include "twoStepObservation.h"

int main() {
	Lorenz							driver, driven;
	XYObservation 			obs;
	TwoStepObservation  obs2(obs);
	SynchronizedSystem 	mySys(driver, obs2, driven);
	Eigen::Vector3d 		dS;
	
//	driver.sigma += 1.0;	
	driven.S.x() += 1.0;
	driven.S.y() += 1.0;
	driven.S.z() += 1.0;
	
	for(int i=0; i<20000; ++i) {
		std::cout << log(mySys.err()) << std::endl;
		mySys.step();
	}
	

/*
	Lorenz myLorenz;
	for(int i=0; i<10000; ++i) {
		std::cout << myLorenz.S.transpose() << std::endl;
		myLorenz.step(0.01);
	}
	*/
  return 0;
}
