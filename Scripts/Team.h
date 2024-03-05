//
// Created by maaya on 19/02/2024.
//

#ifndef WINTERAVLTREE_TEAM_H
#define WINTERAVLTREE_TEAM_H

#include "wet1util.h"
#include "AvlTree.h"
#include "Contestant_Key.h"
#include "Contestant.h"


class Team {
    int teamId;
    Sport sport;
    int numParticipants;
    int myCountry;
    AvlTree<Contestant_Key, Contestant*>* team_whole_contestants_by_id;
    AvlTree<Contestant_Key, Contestant*>* team_whole_contestants_by_strength;


    AvlTree<Contestant_Key, Contestant*>* treeByIdBigVal;
    AvlTree<Contestant_Key, Contestant*>* treeByIdMedVal;
    AvlTree<Contestant_Key, Contestant*>* treeByIdSmallVal;


    AvlTree<Contestant_Key, Contestant*>* treeByStrengthBigVal;
    AvlTree<Contestant_Key, Contestant*>* treeByStrengthMedVal;
    AvlTree<Contestant_Key, Contestant*>* treeByStrengthSmallVal;
    int stateOfBalanceForAdd[3];
    int stateOfBalanceForRemove[3];

    Contestant_Key maxInTreeByIdBigVal;
    Contestant_Key maxInTreeByIdMedVal;
    Contestant_Key maxInTreeByIdSmallVal;
    Contestant_Key minInTreeByIdBigVal;
    Contestant_Key minInTreeByIdMedVal;
    Contestant_Key minInTreeByIdSmallVal;

    Contestant_Key maxInTreeByStrengthSmallVal;
    Contestant_Key maxInTreeByStrengthMedVal;
    Contestant_Key maxInTreeByStrengthBigVal;

    int optimalTeamStrength; //the max strength of a team after deleting the three "weakest" members
public:
    Team();
    Team(int teamId, Sport sport, int countryId);
    ~Team();
    int getCountryId() const;
    Sport* getSport();
    int getNumParticipants() const;
    int getStateOfBalanceForAdd(int index);
    void updateStateOfBalanceForAdd();
    int getStateOfBalanceForRemove(int index);
    void updateStateOfBalanceForRemove();
    void makePlaceInTreeByIdBigValForAdd();
    void makePlaceInTreeByIdMedValForAdd();
    void makePlaceInTreeByIdSmallValForAdd();
    void makePlaceInTreeByIdBigValForRemove(); // you can understand it better with the name "make it able to delete
    // from big tree
    void makePlaceInTreeByIdMedValForRemove();
    void makePlaceInTreeByIdSmallValForRemove();

    void updateTreeByStrengthSmallValForAdd(); //notice : name not correct!. this one updates both of small trees
    void updateTreeByStrengthMedValForAdd();//notice : name not correct!. this one updates both of med trees
    void updateTreeByStrengthBigValForAdd(); //notice : name not correct!. this one updates both of big trees
    void updateTreeByStrengthSmallValForRemove(); //notice : name not correct!. this one updates both of small trees
    void updateTreeByStrengthMedValForRemove();//notice : name not correct!. this one updates both of med trees
    void updateTreeByStrengthBigValForRemove(); //notice : name not correct!. this one updates both of big trees
    //void addContestantToATeam(int contestantId, int countryId, int strength, Sport sport, bool called_from_optimal);
    void addContestantToATeam(const Contestant_Key&  keyToAdd, Contestant* contestantToAdd, bool
    called_from_optimal);
    void removeContestantFromTeam(const Contestant_Key & keyToRemove, bool called_from_optimal); //toRemove should be
    // contestant with flag 0
    void updateTreeByStrengthForTrivialTreesAfterRemove();
    void updateOptimalTeamStrength();
    // about the Contestant
    //updates the contestant's teams-array in index arrayIndex in this specific team, to teamID
    void update_contestant_team_array(int contestantId, int arrayIndex, int teamId);
    Contestant_Key get_maxInTreeByStrengthBigVal();
    Contestant_Key get_maxInTreeByStrengthMedVal();
    Contestant_Key get_maxInTreeByStrengthSmallVal();

    int get_optimalTeamStrength() const;
    void set_optimalTeamStrength(int optimalVal);

    AvlTree<Contestant_Key, Contestant*>* get_treeByIdBigVal();
    AvlTree<Contestant_Key, Contestant*>* get_treeByIdMedVal();
    AvlTree<Contestant_Key, Contestant*>* get_treeByIdSmallVal();


    AvlTree<Contestant_Key, Contestant*>* get_treeByStrengthBigVal();
    AvlTree<Contestant_Key, Contestant*>* get_treeByStrengthMedVal();
    AvlTree<Contestant_Key, Contestant*>* get_treeByStrengthSmallVal();

    AvlTree<Contestant_Key, Contestant*>* get_team_whole_contestants_by_id();
    AvlTree<Contestant_Key, Contestant*>* get_team_whole_contestants_by_strength();
    static void DestroyTeam(Team* team);

};

#endif //WINTERAVLTREE_TEAM_H
