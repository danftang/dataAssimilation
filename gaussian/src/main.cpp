#include <Eigen/Core>
#include "jet.h"
#include "Assimilation.h"

int main() {
	Assimilation<3,1>::Model lorenz(
		[] (Assimilation<3,1>::ModelState &S) {
				const double dt = 0.01;
				auto ddx = 10.0*(S[1]-S[0]);
				auto ddy = S[0]*(28.0-S[2])-S[1];
				auto ddz = S[0]*S[1] - 8.0*S[2]/3.0;
				S[0] += ddx*dt;
				S[1] += ddy*dt;
				S[2] += ddz*dt;
		}
	);

	Assimilation<3,1>::ObservationOp H(
		[](Assimilation<3,1>::ModelState &S)->Assimilation<3,1>::Observation {
				Assimilation<3,1>::Observation result;
				result[0] = S[0];
				return(result);
		}
	);

	Assimilation<3,1>::ModelState myV;
	myV[0] = ceres::Jet<double,3>(10.3, 0);
	myV[1] = ceres::Jet<double,3>(8.91, 1);
	myV[2] = ceres::Jet<double,3>(30.8, 2);

	lorenz(myV);

//	myV[1] = myV[0]*3.9 + myV[1]*myV[1];
	std::cout << myV[0] << std::endl;
	std::cout << myV[1] << std::endl;
	std::cout << myV[2] << std::endl;
			
	return(0);
}
