//
// Created by daniel on 06/04/16.
//

#include "Agent.h"
#include "Population.h"

std::uniform_real_distribution<double> Agent::distribution(0.0,1.0);
std::default_random_engine Agent::generator;

Agent::Agent() {
}

void Agent::step(Agent other) {
	if(distribution(generator) < Population::mu) {
		strain1.s = ImmuneState::SUSEPTIBLE;
		strain2.s = ImmuneState::SUSEPTIBLE;
		return;
	}
    strain1.step(strain2);
    strain2.step(strain1);
    strain1.meet(other.strain2,other.strain1);
    strain2.meet(other.strain1,other.strain2);
}

