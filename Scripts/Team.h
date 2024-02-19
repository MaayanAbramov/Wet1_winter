//
// Created by USER on 12/02/2024.
//

#ifndef WET1_WINTER_TEAMS_H
#define WET1_WINTER_TEAMS_H

#include "wet1util.h"
#include "AvlTree.h"

class Team {
    int teamId{};
    Sport sport;
    int numParticipants;
    AvlTree* contestant;
public:
    Team();
    Team(int teamId, Sport sport, int numParticipants);
};


#endif //WET1_WINTER_TEAMS_H
