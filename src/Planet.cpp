/*
 * Planet.cpp
 *
 *  Created on: 27 Oct 2015
 *      Author: daniel
 */

#include "Planet.h"
const double Planet::G = 6.674e-11;  // gravitational constant
const double Planet::AU = 1.496e11;  // Astronomical unit
std::default_random_engine Planet::gen;
std::normal_distribution<> Planet::gaussian(0,AU/20.0);

Planet::Planet()
{
    m = 5.972e24; // mass of Earth
    v.setZero();
    x[0] = gaussian(gen);
    x[1] = gaussian(gen);
}

void Planet::step(Planet &other, Planet &other2, double dt) {
    Eigen::Vector2d r1(other.x-x);
    Eigen::Vector2d r2(other2.x-x);
    Eigen::Vector2d a = G*(other.m*r1/pow(r1.norm(),3.0) + other2.m*r2/pow(r2.norm(),3.0));
    x += v*dt + 0.5*a*dt*dt;
    v += a*dt;
}

