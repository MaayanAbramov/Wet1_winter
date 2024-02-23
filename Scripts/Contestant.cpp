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
    this->is_by_strength_sorted = -1;
}

Contestant::Contestant(int contestantId, int countryId, int strength, Sport sport, bool is_by_strength_sorted_) {
    this->contestantId = contestantId;
    this->countryId = countryId;
    this->strength = strength;
    this->sport = sport;
    this->is_by_strength_sorted = is_by_strength_sorted_;
}
Contestant::Contestant(const Contestant& other) {
    this->contestantId = other.contestantId;
    this->countryId = other.countryId;
    this->strength = other.strength;
    this->sport = other.sport;
    this->is_by_strength_sorted = other.is_by_strength_sorted;
}

bool operator<(const Contestant& num1, const Contestant& num2) {
    if (num1.is_by_strength_sorted) {
        return num1.strength < num2.strength || ((num1.strength < num2.strength) && (num1.contestantId < num2
        .contestantId));

    }
    assert(num1.is_by_strength_sorted != -1);
    return num1.contestantId < num2.contestantId;
}


bool operator>(const Contestant& num1, const Contestant& num2) {
    if (num1.is_by_strength_sorted) {
        return num1.strength > num2.strength || ((num1.strength > num2.strength) && (num1.contestantId > num2.strength));
    }
    assert(num1.is_by_strength_sorted != -1);
    return num1.contestantId > num2.contestantId;
}
