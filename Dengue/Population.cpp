//
// Created by daniel on 08/04/16.
//

#include "Population.h"

Population::Population() : randAgent(0, N_AGENTS - 1) {
    int m;
    int n;

    for(n=0; n<N_AGENTS/2; ++n) {
        m = randAgent(generator);
        agents[m].strain1.s = ImmuneState::RECOVERED;
        agents[m].strain2.s = ImmuneState::RECOVERED;
    }

    for(n=0; n<50; ++n) {
        m = randAgent(generator);
        agents[m].strain1.s = ImmuneState::INFECTED;
    }

    for(n=0; n<50; ++n) {
        m = randAgent(generator);
        agents[m].strain2.s = ImmuneState::INFECTED;
    }



}

void Population::step() {
    int n;
    int m;
    int t;
    for(t=0; t<1.0/dt; ++t) {
        for (n = 0; n < N_AGENTS; ++n) {
            m = randAgent(generator);
            agents[n].step(agents[m]);
        }
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


