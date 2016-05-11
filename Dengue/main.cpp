#include <iostream>
#include <random>
//#include "Agent.h"
#include "Population.hpp"

using namespace std;

std::vector<int> createObservations(Population &pop, int STEPS) {
    int step;
    std::vector<int> observations;

    for(step=0; step<STEPS; ++step) {
        pop.step();
        observations.push_back(pop.observe());

	//	std::cout << pop.nInfected() << " " << pop.nSuseptible() << " " << pop.nCrossImmune() << std::endl;

    }
    return(observations);
}

int main() {


    int                 STEPS = 500;
    PopulationDistribution trueStartState =
      {0.2526, 0.0067, 0.0061, 0.0001, 0.1839, 0.1794,
       0.0738, 0.0714, 0.0027, 0.0028, 0.2205};
    Population          observedPopulation = trueStartState;
    std::array<double,11> trueStartFrequencies = observedPopulation.getFrequencies();
    Population          simulatedPopulation;
    std::vector<int>    observations = createObservations(observedPopulation,STEPS);
    std::vector<int>    simObs;

    std::array<double,11> startState(trueStartFrequencies);
    startState[0] -= 0.05;
    startState[1] += 0.05;
    //simulatedPopulation.setFrequencies(startState);

    for(int step=0; step<STEPS; ++step) {
      simulatedPopulation.step();
      std::cout << observations[step] <<" "<< simulatedPopulation.observe() << std::endl;
      simulatedPopulation.nudge(observations[step]);
    }

    std::array<double,11> trueFinalState = observedPopulation.getFrequencies();
    std::array<double,11> simulatedFinalState = simulatedPopulation.getFrequencies();

    for(int i=0; i<11; ++i) {
      std::cout <<"# "<< trueFinalState[i] <<" "<< simulatedFinalState[i] << std::endl;
    }

    return 0;
}
