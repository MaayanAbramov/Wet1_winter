//
// Created by maaya on 19/02/2024.
//

#ifndef WINTERAVLTREE_TEAM_H
#define WINTERAVLTREE_TEAM_H

#include "wet1util.h"
#include "AvlTree.h"
#include "Contestant.h"

class Team {
    int teamId{};
    Sport sport;
    int numParticipants;
    AvlTree<int, Contestant>* contestants;
    //TO_DO: add 6 fields
public:
    Team();
    Team(int teamId, Sport sport, int numParticipants);
};

#endif //WINTERAVLTREE_TEAM_H
