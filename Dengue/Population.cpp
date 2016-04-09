//
// Created by daniel on 08/04/16.
//

#include "Population.h"

Population::Population() : randAgent(0, N_AGENTS - 1) {
    int m;

    for(int n=0; n<10; ++n) {
        m = randAgent(generator);
        agents[m].strain1.s = ImmuneState::INFECTED;
    }

    for(int n=0; n<10; ++n) {
        m = randAgent(generator);
        agents[m].strain2.s = ImmuneState::INFECTED;
    }

}

void Population::step() {
    int n;
    int m;

    for(n=0; n<N_AGENTS; ++n) {
        m = randAgent(generator);
        agents[n].step(agents[m]);
    }

}

int Population::nSuseptible() {
    int s=0;
    for(int n=0; n<N_AGENTS; ++n) {
        if(agents[n].isSuseptible()) ++s;
    }
    return s;
}

int Population::nInfected() {
    int i=0;
    for(int n=0; n<N_AGENTS; ++n) {
        if(agents[n].isInfected()) ++i;
    }
    return i;
}


