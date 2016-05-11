#ifndef POPULATIONDISTRIBUTION_H
#define POPULATIONDISTRIBUTION_H

#include <random>
#include <array>
//#include "Population.h"
#include "Agent.hpp"

class PopulationDistribution : public std::discrete_distribution<int>
{
public:
    typedef const Agent & result_type;

    PopulationDistribution(std::initializer_list<double> li) : std::discrete_distribution<>(li) {}
    template<class ITERATOR> PopulationDistribution(ITERATOR first, ITERATOR last) : std::discrete_distribution<>(first,last) {}

    template<class GEN>
    result_type operator()(GEN &g) {return(prototypes[std::discrete_distribution<>::operator()(g)]);}
    static result_type agent(int i) {return(prototypes[i]);}

protected:

    static std::array<Agent,11> prototypes;
};

#endif // POPULATIONDISTRIBUTION_H
