//
// Created by daniel on 08/04/16.
//

#include "Population.hpp"

PopulationDistribution Population::defaultDistribution{0.49,0.005,0.005,0,0,0,0,0,0,0,0.5};

Population::Population() : Population(defaultDistribution) { }

Population::Population(PopulationDistribution &dist) : randAgent(0, N_AGENTS - 1) {
    for(int n=0; n<N_AGENTS; ++n) {
        agents[n] = dist(generator);
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

/***
* Nudge the state towards the observed number of infected
* keeping the proportions of sub-states within both
* infected and uninfected sets roughly the same.
***/
void Population::nudge(int obsInfected) {
  double targetInfected, infectedMultiplier, uninfectedMultiplier;
  std::array<double,11> frequencies = getFrequencies();
  double pInfected = frequencies[1] + frequencies[2] + frequencies[3];

  targetInfected = (obsInfected*1.0/N_AGENTS + pInfected)/2.0;
  infectedMultiplier = targetInfected/pInfected;
  uninfectedMultiplier = (1.0-targetInfected)/(1.0-pInfected);

  frequencies[0] *= uninfectedMultiplier;
  frequencies[1] *= infectedMultiplier;
  frequencies[2] *= infectedMultiplier;
  frequencies[3] *= infectedMultiplier;
  frequencies[4] *= uninfectedMultiplier;
  frequencies[5] *= uninfectedMultiplier;
  frequencies[6] *= uninfectedMultiplier;
  frequencies[7] *= uninfectedMultiplier;
  frequencies[8] *= uninfectedMultiplier;
  frequencies[9] *= uninfectedMultiplier;
  frequencies[10]*= uninfectedMultiplier;

  setFrequencies(frequencies);
}


std::array<double,11> Population::getFrequencies() {
    int i;
    std::array<double,11> states;
    states.fill(0.0);
    for(int n=0; n<N_AGENTS; ++n) {
        i=0;
        while(PopulationDistribution::agent(i) != agents[n] && i<11) {
            ++i;
        }
        if(i<11) states[i] += 1.0/N_AGENTS;
    }
    return(states);
}

void Population::setFrequencies(std::array<double,11> &freq) {
  int i=0;
  double cdf = freq[0];
  for(int n=0; n<N_AGENTS; ++n) {
    if((n*1.0/N_AGENTS) > cdf) {
      cdf += freq[++i];
    }
    agents[n] = PopulationDistribution::agent(i);
  }
}

Population::ObservationType Population::observe() {
    return(nInfected());
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

int Population::nCrossImmune() {
    int i=0;
    for(int n=0; n<N_AGENTS; ++n) {
        if(agents[n].isCrossImmune()) ++i;
    }
    return i;
}

/*
Population &Population::operator =(const Population &other) {
    for(int i=0; i<N_AGENTS; ++i) {
        agents[i] = other.agents[i];
    }
}
*/
