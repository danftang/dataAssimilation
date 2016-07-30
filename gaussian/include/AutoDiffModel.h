#ifndef AUTODIFFMODEL_H
#define AUTODIFFMODEL_H

#include <functional>
#include "IModel.h"
#include "jet.h"

template<int D>
class AutoDiffModel : public IModel<D> {
public:
	typedef ceres::Jet<double,D> 					DualDouble;
	typedef Eigen::Matrix<DualDouble,D,1> State;
	
	AutoDiffModel(std::function<void(State &)> &StepFn) : stepFn(StepFn){}
	

	void step(State &state, Jacobian &jacobian);
	
	std::function<void(State &)> &stepFn;
};

template<int D>
void AutoDiffModel<D>::step(State &state, Jacobian &jacobian) {
	int i,j;
	
	// setup infinitesimals
	State s;
	for(i=0; i< D; ++i) {
		s[i] = DualDouble(state[i], i);
	}
	
	// step forward
	stepFn(s);
	
	// transfer new state back to 'state'
	for(i=0; i< D; ++i) {
		state[i] = s[i].a;
	}
	
	// construct the jacobian
	for(i=0; i< D; ++i) {
		for(j=0; j< D; ++j) {
			jacobian[i][j] = state[i].v[j];
		}
	}
}

#endif
