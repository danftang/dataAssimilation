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
        m(state(j+4)),
		x(state,j),
		v(state,j+2),
		dxp_dx(Jacobian,j,j),
		dxp_dx1(Jacobian,j,(j+5)%15),
		dxp_dm1(Jacobian,j,(j+9)%15),
		dxp_dx2(Jacobian,j,(j+10)%15),
		dxp_dm2(Jacobian,j,(j+14)%15),

		dvp_dx(Jacobian,j+2,j),
		dvp_dx1(Jacobian,j+2,(j+5)%15),
		dvp_dm1(Jacobian,j+2,(j+9)%15),
		dvp_dx2(Jacobian,j+2,(j+10)%15),
		dvp_dm2(Jacobian,j+2,(j+14)%15)
{
//    m = 1.0;//5.972e24; // mass of Earth
    initState();

    // --- fill in the constant parts of the Jacobian
    Jacobian.block(j, 0, 5, 15).setZero();
    Jacobian.block(j,j,5,5).setIdentity();
    Jacobian.block(j,j+2,2,2) 		= dt*Matrix2d::Identity();	// dxp_dv
//    Jacobian.block(j+2,j+2,2,2)		= Matrix2d::Identity(); 	// dvp_dv
//    Jacobian(j+4,j+4)               = 1.0;                      // dm_dm

//    Jacobian.block(j,(j+7)%15,2,2) 	= Matrix2d::Zero(); 		// dxp_dv1
//    Jacobian.block(j,(j+12)%15,2,2) = Matrix2d::Zero(); 		// dxp_dv2
//    Jacobian.block(j+2,(j+7)%15,2,2)= Matrix2d::Zero(); 		// dvp_dv1
//    Jacobian.block(j+2,(j+12)%15,2,2)= Matrix2d::Zero(); 		// dvp_dv2
//    Jacobian.block(j+4, 0, 15, 1)= Matrix2d::Zero(); 		// dvp_dv2
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
    m = 1.0;
}

void Planet::step(Planet &other1, Planet &other2) {
    Vector2d r1(other1.x-x);
    Vector2d r2(other2.x-x);
    double r1_3i = 1.0/pow(r1.norm(),3.0);
    double r2_3i = 1.0/pow(r2.norm(),3.0);
    Vector2d a = G*(other1.m*r1_3i*r1 + other2.m*r2_3i*r2);
    Matrix2d da_dr1;
    Matrix2d da_dr2;
    Vector2d da_dm1;
    Vector2d da_dm2;

    // -- update state
    x += v*dt + 0.5*a*dt*dt;
    v += a*dt;

    // -- update Tangent-linear model
    da_dr1 = G*other1.m*(r1_3i*Matrix2d::Identity() - 3.0*r1*r1.transpose()/pow(r1.norm(),5));
    da_dr2 = G*other2.m*(r2_3i*Matrix2d::Identity() - 3.0*r2*r2.transpose()/pow(r2.norm(),5));
    da_dm1 = G*r1_3i*r1;
    da_dm2 = G*r2_3i*r2;

    dxp_dx  = Matrix2d::Identity() - (0.5*dt*dt)*(da_dr1 + da_dr2);
    dxp_dx1 = (0.5*dt*dt)*da_dr1;
    dxp_dx2 = (0.5*dt*dt)*da_dr2;
    dxp_dm1 = (0.5*dt*dt)*da_dm1;
    dxp_dm2 = (0.5*dt*dt)*da_dm2;
    dvp_dx  = -dt*(da_dr1 + da_dr2);
    dvp_dx1 = dt*da_dr1;
    dvp_dx2 = dt*da_dr2;
    dvp_dm1 = dt*da_dm1;
    dvp_dm2 = dt*da_dm2;
}

