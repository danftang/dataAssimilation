#include <iostream>
#include <random>
#include <numeric>
//#include "Agent.h"
#include "Population.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
std::vector<int> createObservations(Population &pop, int STEPS) {
    int step;
    std::vector<int> observations;

    for(step=0; step<STEPS; ++step) {
        pop.step();
        observations.push_back(pop.observe());

	std::cout << pop.nInfected() << " " << pop.nSuseptible() << " " << pop.nCrossImmune() << std::endl;

    }
    return(observations);
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
double distance(const std::vector<int> &observed, const std::vector<int> &simulated) {
    return(inner_product(observed.begin(), observed.end(), simulated.begin(), 0.0,
        [](double tot, double sqr1) {return(tot+sqr1);},
        [](double a, double b) {return(std::pow(a-b,2));}));
//    double r = 0.0;
//    for(int i=0; i<observed.size(); ++i) {
//        r += std::pow(observed[i]-simulated[i],2);
//    }
//    return(r);
}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
std::vector<int> nudgedSimulation(std::vector<int> &observations, Population simulatedPopulation, int STEPS) {
    std::vector<int> simulatedObs;
    for(int step=0; step<STEPS; ++step) {
      simulatedPopulation.step();
      simulatedObs.push_back(simulatedPopulation.observe());
  //    std::cout << observations[step] <<" "<< simulatedObs[step] << std::endl;
      simulatedPopulation.nudge(observations[step]);
    }
    return(simulatedObs);
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int main() {


    int                 STEPS = 400;
    PopulationDistribution trueStartState =
      {0.2526, 0.0067, 0.0061, 0.0001, 0.1839, 0.1794,
       0.0738, 0.0714, 0.0027, 0.0028, 0.2205};
    Population          observedPopulation = trueStartState;
    std::array<double,11> trueStartFrequencies = observedPopulation.getFrequencies();
    Population          simulatedPopulation;
    std::vector<int>    observations = createObservations(observedPopulation,STEPS);
    std::vector<int>    simObs;

    /**
    std::array<double,11> startState(trueStartFrequencies);

    double sum0_10 = trueStartState.probabilities()[0] + trueStartState.probabilities()[10];
    for(double p=0.25; p<0.75; p+=0.025) {
        startState[0] = p*sum0_10;
        startState[10] = (1-p)*sum0_10;
        simulatedPopulation.setFrequencies(startState);
        std::cout
            << p << " "
            << distance(observations, nudgedSimulation(observations, simulatedPopulation, STEPS))
            << std::endl;
    }
**/
    /**
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
**/

    return 0;
}
