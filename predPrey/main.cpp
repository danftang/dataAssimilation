////////////////////////////////////////////////////////
// Simulation of Giilpin, 1979: Spiral chaos in a predator
// pray model.
////////////////////////////////////////////////////////
#include <iostream>
#include <cmath>

#include "ContinuousModel.h"

using namespace std;


int main()
{
    ContinuousModel cm;

//    std::cout << "a[0][2]=" << cm.a[0][2] << std::endl;

    for(int step=0; step<40000; ++step) {
        if(step%3 == 0) std::cout <<
            cm.population[0] << " " <<
            cm.population[1] << " " <<
            cm.population[2] << " " << std::endl;
        cm.step();
    }
    return 0;
}
