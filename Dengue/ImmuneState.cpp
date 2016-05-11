//
// Created by daniel on 06/04/16.
//

#include "ImmuneState.hpp"
#include "Population.hpp"

std::uniform_real_distribution<double> ImmuneState::distribution(0.0,1.0);
//std::default_random_engine ImmuneState::generator;
std::mt19937 ImmuneState::generator;

const double ImmuneState::alpha = Population::dt*2.0/104.0; // rate of loss of cross immunity
const double ImmuneState::gamma = Population::dt*1.0;//Population::dt*1.0/2.0; // rate of recovery
const double ImmuneState::beta = Population::dt*2.0;//Population::dt*1.0; // rate of infection
const double ImmuneState::phi = 3.0;//0.7; // factor of infectivity given cross immunity
const double ImmuneState::epsilon = Population::dt*0.001; // background infection rate

void ImmuneState::step(ImmuneState &crossState) {
    switch(s) {
        case CROSSIMMUNE:
            if(distribution(generator) < alpha) s = SUSEPTIBLE;
            break;
        case INFECTED:
            if(distribution(generator) < gamma) {
            	s = RECOVERED;
            	if(crossState.s == SUSEPTIBLE) {
            		crossState.s = CROSSIMMUNE;
            	}
            }
            // cross immunity
            break;
        default:
        	break;
    }
}

void ImmuneState::meet(ImmuneState &other, ImmuneState &otherCrossStrain) {
    if(s == SUSEPTIBLE) {
        if(other.s == INFECTED) {
            double p = beta;
            if (otherCrossStrain.s == RECOVERED) {
                p *= phi;
            }
            if (distribution(generator) < p) {
                s = INFECTED;
            }
        } else {
            if(distribution(generator) < epsilon) {
                s = INFECTED;
            }
        }
    }
}

std::ostream &operator <<(std::ostream &out, const ImmuneState &state) {
    switch(state.s) {
    case ImmuneState::CROSSIMMUNE:
            out << "c"; break;
    case ImmuneState::SUSEPTIBLE:
            out << "s"; break;
    case ImmuneState::INFECTED:
            out << "i"; break;
    case ImmuneState::RECOVERED:
            out << "r"; break;
    }
    return(out);
}

