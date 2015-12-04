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
	b0(b0i),
//	solver(NLOPT_LD_MMA,12)
	solver(NLOPT_LD_SLSQP,m.state().size())
//	lambda(m.state().size())
{
}

//void FourDVar::observe(std::vector<VectorXd> &observations) {
//	y = observations;
//}

// --- do the non-linear optimization
// x0 - first guess
void FourDVar::assimilate(VectorXd &x0) {
	int info;
	if(y.size() == 0) {
		std::cout << "No observations" << std::endl;
		return;
	}
    solver.set_min_objective(*this);
    solver.set_ftol_abs(1e-10);
    solver.set_ftol_rel(1e-10);
    info = solver.optimize(x0);
	std::cout << "Solver returned " << info << std::endl;
//	std::cout << "x0 =" << x0 << std::endl;
}

double FourDVar::operator()(Eigen::Map<const Eigen::VectorXd> &x0, Eigen::Map<Eigen::VectorXd> &lambda) {
	int t;
    int timesteps = y.size();
	double err; // total error
	VectorXd dy(y[0].size());
    std::vector<VectorXd> xt(timesteps,model.state()); // forward integral states
    std::vector<MatrixXd> Mt(timesteps,model.tangent()); // tangent linear models

//	err = (x0-b0).transpose()*P0inv*(x0-b0);
    err = 0.0;

    // -- integrate forward
    model.state() = x0;
    for(t=0; t<timesteps-1; ++t)
    {
        xt[t] = model.state();
    	dy = H(xt[t])-y[t];
    	err += dy.transpose()*H.Rinv()*dy;
        model.step();
        Mt[t] = model.tangent();
    }
    xt[t] = model.state();
    Mt[t].setZero();

    if(lambda.size() > 0) { // -- calculate Jacobian
        // -- project error backwards
        lambda.setZero();
        for(t=timesteps-1; t>=0; --t) {
            lambda = Mt[t].transpose()*lambda + H.tangent(xt[t]).transpose()*H.Rinv()*(H(xt[t])-y[t]);
        }
//        lambda += P0inv*xt[0];
    }
//    std::cout << "Error & Jacobian = " << err << " & " << lambda.transpose() << std::endl;
 //   std::cout << "              x0 = " << x0.transpose() << std::endl;
    return(err);
}

double FourDVar::operator()(const VectorXd &x0, VectorXd &lambda) {
    Eigen::Map<const VectorXd> x0m(x0.data(),x0.size());
    Eigen::Map<VectorXd> lambdam(lambda.data(),lambda.size());
    return(operator()(x0m,lambdam));
}

/**
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
**/
