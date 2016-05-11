#include "PopulationDistribution.hpp"

std::array<Agent,11> PopulationDistribution::prototypes = {
    Agent(ImmuneState::SUSEPTIBLE,  ImmuneState::SUSEPTIBLE),
    Agent(ImmuneState::SUSEPTIBLE,  ImmuneState::INFECTED),
    Agent(ImmuneState::INFECTED,    ImmuneState::SUSEPTIBLE),
    Agent(ImmuneState::INFECTED,    ImmuneState::INFECTED),
    Agent(ImmuneState::CROSSIMMUNE, ImmuneState::RECOVERED),
    Agent(ImmuneState::RECOVERED,   ImmuneState::CROSSIMMUNE),
    Agent(ImmuneState::SUSEPTIBLE,  ImmuneState::RECOVERED),
    Agent(ImmuneState::RECOVERED,   ImmuneState::SUSEPTIBLE),
    Agent(ImmuneState::INFECTED,    ImmuneState::RECOVERED),
    Agent(ImmuneState::RECOVERED,   ImmuneState::INFECTED),
    Agent(ImmuneState::RECOVERED,   ImmuneState::RECOVERED)
};

