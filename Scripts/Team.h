//
// Created by maaya on 19/02/2024.
//

#ifndef WINTERAVLTREE_TEAM_H
#define WINTERAVLTREE_TEAM_H

#include "wet1util.h"
#include "AvlTree.h"
#include "Contestant.h"

class Team {
    int teamId;
    Sport sport;
    int numParticipants;
    int myCountry;
    AvlTree<int, Contestant>* teamContestants;

    AvlTree<int, Contestant>* treeByIdBigVal;
    AvlTree<int, Contestant>* treeByIdMedVal;
    AvlTree<int, Contestant>* treeByIdSmallVal;
    AvlTree<int, Contestant>* treeByStrengthBigVal;
    AvlTree<int, Contestant>* treeByStrengthMedVal;
    AvlTree<int, Contestant>* treeByStrengthSmallVal;

public:
    Team();
    Team(int teamId, Sport sport, int numParticipants, int countryId);
    ~Team() = default;
    int getCountryId() const;
};

#endif //WINTERAVLTREE_TEAM_H
