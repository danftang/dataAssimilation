/*
 * FourDVar.cpp
 *
 *  Created on: 4 Nov 2015
 *      Author: daniel
 */

#include "FourDVar.h"

FourDVar::FourDVar(Model &m, ObservationOperator &obs, MatrixXd &P0i, VectorXd &b0i) :
	model(m),
//	y(observations),
	H(obs),
	P0(P0i),
	b0(b0i)
//	lambda(m.state().size())
{
}

void FourDVar::assimilate(std::vector<VectorXd> &observations) {
	if(observations.size() == 0) return;
	VectorXd lambda(observations[0].size()); // multi-timestep-error adjoint model


}

void FourDVar::calcAdjoint(VectorXd &lambda, std::vector<VectorXd> &y) {
	int t;
	int timesteps = y.size();
    std::vector<VectorXd> xt(timesteps,model.state()); // forward integral states
    std::vector<MatrixXd> Mt(timesteps,model.tangent()); // tangent linear models


    // -- calculate Jacobian
    // -- integrate forward
    for(t=0; t<timesteps-1; ++t) {
    	xt[t] = model.state();
    	model.step();
    	Mt[t] = model.tangent();
    }
    xt[t] = model.state();
    Mt[t].setZero();

    // -- project error backwards
    lambda.setZero();
    for(t=timesteps-1; t>=0; --t) {
        lambda = Mt[t].transpose()*lambda + H.tangent(xt[t]).transpose()*H.Rinv()*(H*xt[t]-y[t]);
    }
    lambda += P0.inverse()*xt[0];

}
