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
    AvlTree<int, Contestant>* team_whole_contestants;


    AvlTree<int, Contestant>* treeByIdBigVal;
    AvlTree<int, Contestant>* treeByIdMedVal;
    AvlTree<int, Contestant>* treeByIdSmallVal;


    AvlTree<int, Contestant>* treeByStrengthBigVal;
    AvlTree<int, Contestant>* treeByStrengthMedVal;
    AvlTree<int, Contestant>* treeByStrengthSmallVal;
    int stateOfBalance[3];
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
    ~Team();
    int getCountryId() const;
    int getStateOfBalance(int index);
    void updateStateOfBalance();
    void makePlaceInTreeByIdBigVal();
    void makePlaceInTreeByIdMedVal();
    void makePlaceInTreeByIdSmallVal();

    void updateTreeByStrengthSmallVal(); //notice : name not correct!. this one updates both of small trees
    void updateTreeByStrengthMedVal();//notice : name not correct!. this one updates both of med trees
    void updateTreeByStrengthBigVal(); //notice : name not correct!. this one updates both of big trees
    //void addContestantToATeam(int contestantId, int countryId, int strength, Sport sport);
    // about the Contestant
    int get_maxInTreeByStrengthBigVal();
    int get_maxInTreeByStrengthMedVal();
    int get_maxInTreeByStrengthSmallVal();
    AvlTree<int, Contestant>* get_treeByIdBigVal();
    AvlTree<int, Contestant>* get_treeByIdMedVal();
    AvlTree<int, Contestant>* get_treeByIdSmallVal();


    AvlTree<int, Contestant>* get_treeByStrengthBigVal();
    AvlTree<int, Contestant>* get_treeByStrengthMedVal();
    AvlTree<int, Contestant>* get_treeByStrengthSmallVal();
};

#endif //WINTERAVLTREE_TEAM_H
