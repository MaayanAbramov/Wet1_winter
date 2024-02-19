//
// Created by maaya on 19/02/2024.
//

#include "Contestant.h"

#include "wet1util.h"

Contestant::Contestant() {
    this->contestantId = 0;
    this->countryId = 0;
    this->strength = 0;
    this->sport = Sport::BOULDERING;
}

Contestant::Contestant(int contestantId, int countryId, int strength, Sport sport) {
    this->contestantId = contestantId;
    this->countryId = countryId;
    this->strength = strength;
    this->sport = sport;
}