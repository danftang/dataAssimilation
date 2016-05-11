//
// Created by daniel on 06/04/16.
//

#ifndef DENGUE_IMMUNESTATE_H
#define DENGUE_IMMUNESTATE_H

#include <ostream>
#include <random>

class ImmuneState {
public:
  enum STATE {
    CROSSIMMUNE,
    SUSEPTIBLE,
    INFECTED,
    RECOVERED
  };

  ImmuneState() : s(SUSEPTIBLE) { }
  
  ImmuneState(STATE iState) : s(iState) { }
  
  void step(ImmuneState &crossState);
  void meet(ImmuneState &, ImmuneState &);
  bool isSuseptible() {return s == SUSEPTIBLE;}
  bool isInfected() {return s == INFECTED;}
  bool isCrossImmune() {return s == CROSSIMMUNE;}
  
  bool operator ==(const ImmuneState &other) const {return(s==other.s);}
  
  STATE s;
  
protected:
    static const double alpha;
    static const double gamma;
    static const double beta;
    static const double phi;
    static const double epsilon;

//    static std::default_random_engine generator;
    static std::mt19937 generator;
    static std::uniform_real_distribution<double> distribution;
};


std::ostream &operator <<(std::ostream &, const ImmuneState &);

#endif //DENGUE_IMMUNESTATE_H
