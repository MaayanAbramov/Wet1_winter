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
    for (int i = 0 ; i < 3 ; i++) {
        teamsIParticipate[i] = static_cast<Sport>(TEAM_TYPE_INIT);
    }
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
bool Contestant::operator==(const Contestant& other) const {
    if (this->is_by_strength_sorted) {
        return (this->strength == other.strength) && (this->contestantId == other.contestantId);
    }
    return this->contestantId == other.contestantId;
}

bool operator<(const Contestant& num1, const Contestant& num2) {
    if (num1.is_by_strength_sorted) {
        bool OK1 = num1.strength < num2.strength;
        bool OK2 = ((num1.strength == num2.strength) && (num1.contestantId < num2
                .contestantId));
        return  OK1 || OK2;

    }
    assert(num1.is_by_strength_sorted != -1);
    bool OK3 = num1.contestantId < num2.contestantId;
    return OK3;
}


bool operator>(const Contestant& num1, const Contestant& num2) {
    if (num1.is_by_strength_sorted) {
        bool OK1 = num1.strength > num2.strength;
        bool OK2 = ((num1.strength == num2.strength) && (num1.contestantId > num2.contestantId));
        return OK1 || OK2;
    }
    assert(num1.is_by_strength_sorted != -1);
    bool OK3 = num1.contestantId > num2.contestantId;
    return OK3;
}

int Contestant::get_contestantId() const {
    return contestantId;
}
int Contestant::get_countryId() const {
    return countryId;
}
int Contestant::get_strength() const {
    return strength;
}
Sport Contestant::get_sport() const {
    return sport;
}
bool Contestant::get_is_by_strength_sorted() const {
    return is_by_strength_sorted;
}
void Contestant::set_is_by_strength_sorted(bool is_by_strength) {
    this->is_by_strength_sorted = is_by_strength;
}

Sport* Contestant::get_teamsIParticipate(int index) const {
    return &(this->teamsIParticipate[index]);
}
void Contestant::set_teamsIparticipate(int index, const Sport& sport) {
    this->teamsIParticipate[index] = sport;
}
