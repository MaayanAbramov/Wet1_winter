//
// Created by USER on 12/02/2024.
//

#include "Team.h"

Team::Team() {
    this->teamId = 0;
    this->numParticipants = 0;
    this->sport = Sport::BOULDERING;
    this->myCountry = 0;

}

Team::Team(int teamId, Sport sport, int numParticipants, int countryId) {
    this->teamId = teamId;
    this->sport = Sport::BOULDERING;
    this->numParticipants = numParticipants;
    this->myCountry = countryId;

}

int Team::getCountryId() const{
    return this->myCountry;
}