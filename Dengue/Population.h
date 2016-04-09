//
// Created by daniel on 08/04/16.
//

#ifndef DENGUE_POPULATION_H
#define DENGUE_POPULATION_H


#include <random>
#include "Agent.h"

class Population {
    public:

    static constexpr int N_AGENTS = 10000;
    static constexpr double dt = 0.1;
    static constexpr double mu = dt*0.02;//dt*1.0/(65.0*104.0); // mortality (per meeting)

    Population();;
    void step();
    int nInfected();
    int nSuseptible();

    std::default_random_engine generator;
    std::uniform_int_distribution<> randAgent;
    Agent agents[N_AGENTS];


};


#endif //DENGUE_POPULATION_H
