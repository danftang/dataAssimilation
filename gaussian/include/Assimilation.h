#ifndef ASSIMILATION_H
#define ASSIMILATION_H

#include <functional>
#include <Eigen/Core>
#include "jet.h"
#include "Gaussian.h"

template<int D_MODEL, int D_OBS>
class Assimilation {
public:
	typedef ceres::Jet<double,D_MODEL> 									DualDouble;
	typedef Eigen::Matrix<DualDouble,D_MODEL,1> 				ModelState;
	typedef Eigen::Matrix<DualDouble,D_OBS,1> 					Observation;
//	typedef Eigen::Matrix<double, D_OBS, Eigen::Dynamic> Observations;

	typedef std::function<void(ModelState &)>						Model;
	typedef std::function<Observation(ModelState &)>		ObservationOp;

	Assimilation(Model m, ObservationOp h) :
		model(m), H(h) {}
	
	void step();
	void observe(Observation &);
	ModelState toState(Eigen::Matrix<double,D_MODEL,1> &state);
	//ModelState toVector(ModelState &state);
	
	Gaussian<D_MODEL>		pdf;
	Model								model;
	ObservationOp				H;
//	Observations				obs;
};

template<int D_MODEL, int D_OBS>
typename Assimilation<D_MODEL,D_OBS>::ModelState Assimilation<D_MODEL,D_OBS>::toState(Eigen::Matrix<double,D_MODEL,1> &state) {
	ModelState result;
	for(int i=0; i< D_MODEL; ++i) {
		result[i] = DualDouble(state[i],i);
	}
	return(result);
}


// step forward in time
// covariance is J^TSJ where J is the reverse time step operator
template<int D_MODEL, int D_OBS>
void Assimilation<D_MODEL,D_OBS>::step() {
	ModelState S(toState(pdf.M));
	Eigen::Matrix<double,D_MODEL,D_MODEL> J; // Jacobian
	
	model(S);
	
}

#endif
