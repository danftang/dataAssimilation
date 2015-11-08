/*
 * FourDVar.cpp
 *
 *  Created on: 4 Nov 2015
 *      Author: daniel
 */

#include <iostream>
#include "FourDVar.h"

FourDVar::FourDVar(Model &m, ObservationOperator &obs, std::vector<VectorXd> &observations, MatrixXd &P0i, VectorXd &b0i) :
	model(m),
	y(observations),
	H(obs),
	P0inv(P0i),
	b0(b0i)
//	lambda(m.state().size())
{
}

//void FourDVar::observe(std::vector<VectorXd> &observations) {
//	y = observations;
//}

// --- do the non-linear optimization
void FourDVar::assimilate(VectorXd &x0) {
	int info;
	if(y.size() == 0) {
		std::cout << "No observations" << std::endl;
		return;
	}
	info = levmar_solve(x0,1);
	std::cout << "Solver returned " << info << std::endl;
}

// --- calculate the value of the objective function
int FourDVar::operator()(const VectorXd &x0, VectorXd &err) {
	unsigned int t;
	VectorXd dy(y[0].size());
	err[0] = (x0-b0).transpose()*P0inv*(x0-b0);

    // -- integrate forward
    model.state() = x0;
    for(t=0; t<y.size()-1; ++t) {
    	dy = H(model.state())-y[t];
    	err[0] += dy.transpose()*H.Rinv()*dy;
    	model.step();
    }
	return(0);
}

// --- calculate adjoint model (Jacobian of objective function)
int FourDVar::df(const VectorXd &x0, MatrixXd &lambda) {
	int t;
	int timesteps = y.size();
    std::vector<VectorXd> xt(timesteps,model.state()); // forward integral states
    std::vector<MatrixXd> Mt(timesteps,model.tangent()); // tangent linear models

    // -- calculate Jacobian
    // -- integrate forward
    model.state() = x0;
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
        lambda = Mt[t].transpose()*lambda + H.tangent(xt[t]).transpose()*H.Rinv()*(H(xt[t])-y[t]);
    }
    lambda += P0inv*xt[0];
    return(0);
}
