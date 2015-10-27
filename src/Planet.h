/*
 * Planet.h
 *
 *  Created on: 27 Oct 2015
 *      Author: daniel
 */

#ifndef PLANET_H_
#define PLANET_H_

#include <eigen3/Eigen/Dense>

class Planet
{
    public:
        Planet();

        void step(Planet &, Planet &, double);

        double m;           // mass
        Eigen::Vector2d x;  // position
        Eigen::Vector2d v;  // velocity

        static const double G;//= 6.674e-11;  // gravitational constant
        static const double AU;// = 1.496e11;  // Astronomicsl unit
        static std::default_random_engine gen;
        static std::normal_distribution<> gaussian;//(0,1);
};

#endif /* PLANET_H_ */
