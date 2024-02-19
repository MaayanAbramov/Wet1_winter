//
// Created by USER on 12/02/2024.
//

#include "Team.h"

Team::Team() {
    this->teamId = 0;
    this->numParticipants = 0;
    this->sport = Sport::BOULDERING;
    this->contestant = NULL;
}

Team::Team(int teamId, Sport sport, int numParticipants) {
    this->teamId = teamId;
    this->sport = Sport::BOULDERING;
    this->numParticipants = numParticipants;
    this->contestant = NULL;
}
