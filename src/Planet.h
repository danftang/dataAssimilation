/*
 * Planet.h
 *
 *  Created on: 27 Oct 2015
 *      Author: daniel
 */

#ifndef PLANET_H_
#define PLANET_H_

#include <random>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Core>

class Planet
{
    public:
        Planet(Eigen::VectorXd &, Eigen::MatrixXd &, int);

        void initState();
        void step(Planet &, Planet &);

        double m;           // mass
        Eigen::VectorBlock<Eigen::VectorXd,2> 	x;	// position
        Eigen::VectorBlock<Eigen::VectorXd,2> 	v;	// velocity
        Eigen::Block<Eigen::MatrixXd,4,12> 		M;	// Tangent linear model
        Eigen::Block<Eigen::MatrixXd,2,2> 		dxp_dx;		// dx'/dx
        Eigen::Block<Eigen::MatrixXd,2,2> 		dxp_dx1;	// dx'/dx1
        Eigen::Block<Eigen::MatrixXd,2,2> 		dxp_dx2;	// dx'/dx2
        Eigen::Block<Eigen::MatrixXd,2,2> 		dvp_dx;		// dv'/dx
        Eigen::Block<Eigen::MatrixXd,2,2> 		dvp_dx1;	// dv'/dx1
        Eigen::Block<Eigen::MatrixXd,2,2> 		dvp_dx2;	// dv'/dx2

        static const double G;  // gravitational constant
        static const double AU; // Astronomical unit
        static const double dt; // timestep
        static const double l; 	// characteristic length scale
        static std::default_random_engine gen;
        static std::normal_distribution<> gaussian;//(0,1);
};

#endif /* PLANET_H_ */
