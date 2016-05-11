//
// Created by daniel on 06/04/16.
//

#include "Agent.hpp"
#include "Population.hpp"

std::uniform_real_distribution<double> Agent::distribution(0.0,1.0);
std::default_random_engine Agent::generator;

Agent::Agent() { }

Agent::Agent(ImmuneState::STATE s1, ImmuneState::STATE s2) : strain1(s1), strain2(s2) { }

void Agent::step(Agent other) {
	if(distribution(generator) < Population::mu) { // death and rebirth
		strain1.s = ImmuneState::SUSEPTIBLE;
		strain2.s = ImmuneState::SUSEPTIBLE;
		return;
	}
    strain1.step(strain2);
    strain2.step(strain1);
    strain1.meet(other.strain2,other.strain1);
    strain2.meet(other.strain1,other.strain2);
}

std::ostream &operator <<(std::ostream &out, const Agent &a) {
    return(out << a.strain1 << a.strain2);
}

