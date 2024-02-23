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
    int* stateOfBalance;
    int maxInTreeByIdBigVal;
    int maxInTreeByIdMedVal;
    int maxInTreeByIdSmallVal;
    int minInTreeByIdBigVal;
    int minInTreeByIdMedVal;
    int minInTreeByIdSmallVal;

    int maxInTreeByStrengthSmallVal;
    int maxInTreeByStrengthMedVal;
    int maxInTreeByStrengthBigVal;
public:
    Team();
    Team(int teamId, Sport sport, int numParticipants, int countryId);
    ~Team() = default;
    int getCountryId() const;
    void updateStateOfBalance();
    void makePlaceInTreeByIdBigVal();
    void makePlaceInTreeByIdMedVal();
    void makePlaceInTreeByIdSmallVal();

    void updateTreeByStrengthSmallVal();
    void updateTreeByStrengthMedVal();
    void updateTreeByStrengthBigVal();
    void addContestant(int contestantId, int countryId, int strength, Sport sport);
    // about the Contestant
    int get_maxInTreeByStrengthBigVal() {
        return maxInTreeByStrengthBigVal;
    }
    int get_maxInTreeByStrengthMedVal() {
        return maxInTreeByStrengthMedVal;
    }
    int get_maxInTreeByStrengthSmallVal() {
        return maxInTreeByStrengthSmallVal;
    }
};

#endif //WINTERAVLTREE_TEAM_H
