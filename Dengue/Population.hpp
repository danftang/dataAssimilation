//
// Created by daniel on 08/04/16.
//

#ifndef DENGUE_POPULATION_H
#define DENGUE_POPULATION_H


#include <random>
#include <vector>
#include "Agent.hpp"
#include "PopulationDistribution.hpp"

class Population {
public:
  using ObservationType = int;
  
  static constexpr int N_AGENTS = 10000;
  static constexpr double dt = 0.1;
  static constexpr double mu = dt*0.02;//dt*1.0/(65.0*104.0); // mortality (per meeting)
  static PopulationDistribution defaultDistribution;
  
  Population();
  Population(PopulationDistribution &);
  
  void step();
  void nudge(ObservationType observation);
  std::array<double,11> getFrequencies();
  void setFrequencies(std::array<double,11> &);
  
  ObservationType observe();
  int nInfected();
  int nSuseptible();
  int nCrossImmune();
//	    Population &operator =(const Population &other);
  
  std::default_random_engine generator;
  std::uniform_int_distribution<> randAgent;
  Agent agents[N_AGENTS];
};


#endif //DENGUE_POPULATION_H
