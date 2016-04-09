//
// Created by daniel on 08/04/16.
//

#ifndef DENGUE_POPULATION_H
#define DENGUE_POPULATION_H


#include <random>
#include "Agent.h"

class Population {
    public:

    static constexpr int N_AGENTS = 1000;

    Population();;
    void step();
    int nInfected();
    int nSuseptible();

    std::default_random_engine generator;
    std::uniform_int_distribution<> randAgent;
    Agent agents[N_AGENTS];


};


#endif //DENGUE_POPULATION_H
