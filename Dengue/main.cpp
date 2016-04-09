#include <iostream>
#include <random>
#include "Agent.h"
#include "Population.h"

using namespace std;

int main() {

    const int N_AGENTS = 1000;
    Population population;

    for(int step=0; step<1000; ++step) {
        population.step();
        std::cout << population.nInfected() << " " << population.nSuseptible() << std::endl;
    }

    return 0;
}