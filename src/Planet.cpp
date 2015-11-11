/*
 * Planet.cpp
 *
 *  Created on: 27 Oct 2015
 *      Author: daniel
 */

#include "Planet.h"

using namespace Eigen;

//const double Planet::G = 6.674e-11;    	// gravitational constant
//const double Planet::AU = 1.496e11;    	// Astronomical unit
//const double Planet::dt = 3600.0*24*7; 	// timestep
//const double Planet::l  = AU/20.0;		// characteristic length scale
const double Planet::G = 1.0;
const double Planet::dt = 0.1;

std::default_random_engine Planet::gen;
std::normal_distribution<> Planet::gaussian(0,1.0);

Planet::Planet(VectorXd &state, MatrixXd &Jacobian, int j) :
		x(state,j),
		v(state,j+2),
		M(Jacobian,j,0),
		dxp_dx(Jacobian,j,j),
		dxp_dx1(Jacobian,j,(j+4)%12),
		dxp_dx2(Jacobian,j,(j+8)%12),
		dvp_dx(Jacobian,j+2,j),
		dvp_dx1(Jacobian,j+2,(j+4)%12),
		dvp_dx2(Jacobian,j+2,(j+8)%12)
{
    m = 1.0;//5.972e24; // mass of Earth
    initState();

    // --- fill in the constant parts of the Jacobian
    Jacobian.block(j,j+2,2,2) 		= dt*Matrix2d::Identity();	// dxp_dv
    Jacobian.block(j,(j+6)%12,2,2) 	= Matrix2d::Zero(); 		// dxp_dv1
    Jacobian.block(j,(j+10)%12,2,2) = Matrix2d::Zero(); 		// dxp_dv2
    Jacobian.block(j+2,j+2,2,2)		= Matrix2d::Identity(); 	// dvp_dv
    Jacobian.block(j+2,(j+6)%12,2,2)= Matrix2d::Zero(); 		// dvp_dv1
    Jacobian.block(j+2,(j+10)%12,2,2)= Matrix2d::Zero(); 		// dvp_dv2
}

void Planet::initState() {
//    x[0] = l*gaussian(gen);
//    x[1] = l*gaussian(gen);
//    v[0] = (1e-3*l/dt)*gaussian(gen);
//    v[1] = (1e-3*l/dt)*gaussian(gen);
    x[0] = gaussian(gen);
    x[1] = gaussian(gen);
    v[0] = gaussian(gen);
    v[1] = gaussian(gen);
}

void Planet::step(Planet &other1, Planet &other2) {
    Vector2d r1(other1.x-x);
    Vector2d r2(other2.x-x);
    Vector2d a = G*(other1.m*r1/pow(r1.norm(),3.0) + other2.m*r2/pow(r2.norm(),3.0));
    Matrix2d da_dr1;
    Matrix2d da_dr2;


    // -- update state
    x += v*dt + 0.5*a*dt*dt;
    v += a*dt;

    // -- update Tangent-linear model
    da_dr1 = G*other1.m*(1.0/pow(r1.norm(),3.0)*Matrix2d::Identity() - 3.0*r1*r1.transpose()/pow(r1.norm(),5));
    da_dr2 = G*other2.m*(1.0/pow(r2.norm(),3.0)*Matrix2d::Identity() - 3.0*r2*r2.transpose()/pow(r2.norm(),5));

    dxp_dx  = Matrix2d::Identity() - (0.5*dt*dt)*(da_dr1 + da_dr2);
    dxp_dx1 = (0.5*dt*dt)*da_dr1;
    dxp_dx2 = (0.5*dt*dt)*da_dr2;
    dvp_dx  = -dt*(da_dr1 + da_dr2);
    dvp_dx1 = dt*da_dr1;
    dvp_dx2 = dt*da_dr2;
}

