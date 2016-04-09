//
// Created by daniel on 06/04/16.
//

#ifndef DENGUE_IMMUNESTATE_H
#define DENGUE_IMMUNESTATE_H


#include <random>

class ImmuneState {
public:
    enum STATE {
        CROSSIMMUNE,
        SUSEPTIBLE,
        INFECTED,
        RECOVERED
    };

    ImmuneState() {
        s = SUSEPTIBLE;
    }

    void step();
    void meet(ImmuneState &);
    bool isSuseptible() {return s == SUSEPTIBLE;}
    bool isInfected() {return s == INFECTED;}

    STATE s;

protected:
    static constexpr double alpha = 2.0;
    static constexpr double gamma = 52.0;
    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> distribution;
};


#endif //DENGUE_IMMUNESTATE_H
