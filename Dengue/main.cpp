#include <iostream>
#include <random>
#include "Agent.h"
#include "Population.h"

using namespace std;

int main() {

    Population population;

    for(int step=0; step<500; ++step) {
        population.step();
        std::cout << population.nInfected() << " " << population.nSuseptible() << std::endl;
    }

    return 0;
}
