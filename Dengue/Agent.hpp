//
// Created by daniel on 06/04/16.
//

#ifndef DENGUE_AGENT_H
#define DENGUE_AGENT_H

#include <ostream>
#include "ImmuneState.hpp"

class Agent {
public:

  Agent();
  Agent(ImmuneState::STATE, ImmuneState::STATE);
  void step(Agent other);
  bool isSuseptible() {return strain1.isSuseptible() || strain2.isSuseptible();}
  bool isInfected() { return strain1.isInfected() || strain2.isInfected();}
  bool isCrossImmune() {return strain1.isCrossImmune() || strain2.isCrossImmune();}

  bool operator ==(const Agent &other) const {return(strain1==other.strain1 && strain2==other.strain2);}
  bool operator !=(const Agent &other) const {return(!(*this == other));}

  ImmuneState strain1;
  ImmuneState strain2;

  static std::default_random_engine generator;
  static std::uniform_real_distribution<double> distribution;

};

std::ostream &operator <<(std::ostream &, const Agent &);

#endif //DENGUE_AGENT_H
