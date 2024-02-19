//
// Created by USER on 12/02/2024.
//

#include "contestant.h"
#include "wet1util.h"

contestant::contestant() {
    this->contestantId = 0;
    this->countryId = 0;
    this->strength = 0;
    this->sport = Sport::BOULDERING;
}

contestant::contestant(int contestantId, int countryId, int strength, Sport sport) {
    this->contestantId = contestantId;
    this->countryId = countryId;
    this->strength = strength;
    this->sport = sport;
}