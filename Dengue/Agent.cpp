//
// Created by daniel on 06/04/16.
//

#include "Agent.h"

Agent::Agent() {
}

void Agent::step(Agent other) {
    strain1.step();
    strain2.step();
    strain1.meet(other.strain1);
    strain2.meet(other.strain2);
}



