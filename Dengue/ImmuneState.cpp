//
// Created by daniel on 06/04/16.
//

#include "ImmuneState.h"

std::uniform_real_distribution<double> ImmuneState::distribution(0.0,1.0);
std::default_random_engine ImmuneState::generator;

void ImmuneState::step() {
    switch(s) {
        case CROSSIMMUNE:
            if(distribution(generator) < alpha) s = SUSEPTIBLE;
            break;
        case INFECTED:
            if(distribution(generator) < gamma) s = RECOVERED;
            break;
    }
}

void ImmuneState::meet(ImmuneState &other) {
    if(s == SUSEPTIBLE && other.s == INFECTED) {
        s = INFECTED;
    }
}



