//
// Created by daniel on 06/04/16.
//

#ifndef DENGUE_AGENT_H
#define DENGUE_AGENT_H

#include "ImmuneState.h"

class Agent {
public:

    Agent();
    void step(Agent other);
    bool isSuseptible() {return strain1.isSuseptible();}
    bool isInfected() { return strain1.isInfected() || strain2.isInfected();}

    ImmuneState strain1;
    ImmuneState strain2;

    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> distribution;

};


#endif //DENGUE_AGENT_H
