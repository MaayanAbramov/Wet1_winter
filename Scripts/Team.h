//
// Created by maaya on 19/02/2024.
//

#ifndef WINTERAVLTREE_TEAM_H
#define WINTERAVLTREE_TEAM_H

#include "wet1util.h"
#include "AvlTree.h"
#include "Contestant.h"

class Team_Key{
    int id;
public:
    explicit Team_Key(int id=-1): id(id) {
        assert(this->id!=-1);
    }
    Team_Key(const Team_Key& key) =default;
    ~Team_Key()=default;
    friend bool operator<(const Team_Key& key1, const Team_Key& key2){
        return key1.id < key2.id;
    }
    friend bool operator>(const Team_Key& key1, const Team_Key& key2){
        return key1.id > key2.id;
    }
    bool operator==(const Team_Key& key2){
        return this->id == key2.id;
    }
};
class Team {
    int teamId;
    Sport sport;
    int numParticipants;
    int myCountry;
    AvlTree<Contestant_Key, Contestant>* team_whole_contestants_by_id;
    AvlTree<Contestant_Key, Contestant>* team_whole_contestants_by_strength;


    AvlTree<Contestant_Key, Contestant>* treeByIdBigVal;
    AvlTree<Contestant_Key, Contestant>* treeByIdMedVal;
    AvlTree<Contestant_Key, Contestant>* treeByIdSmallVal;


    AvlTree<Contestant_Key, Contestant>* treeByStrengthBigVal;
    AvlTree<Contestant_Key, Contestant>* treeByStrengthMedVal;
    AvlTree<Contestant_Key, Contestant>* treeByStrengthSmallVal;
    int stateOfBalanceForAdd[3];
    int stateOfBalanceForRemove[3];
    Contestant* contestantWithMaxInTreeByIdBigVal;
    Contestant* contestantWithMaxInTreeByIdMedVal;
    Contestant* contestantWithMaxInTreeByIdSmallVal;

    Contestant* contestantWithMinInTreeByIdBigVal;
    Contestant* contestantWithMinInTreeByIdMedVal;
    Contestant* contestantWithMinInTreeByIdSmallVal;

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
    Team(int teamId, Sport sport, int numParticipants, int countryId);
    ~Team();
    int getCountryId() const;
    int getStateOfBalanceForAdd(int index);
    void updateStateOfBalanceForAdd();
    void makePlaceInTreeByIdBigValForAdd();
    void makePlaceInTreeByIdMedValForAdd();
    void makePlaceInTreeByIdSmallValForAdd();
    //void makePlaceInTreeByIdBigValForRemove(); // you can understand it better with the name "make it able to delete
    // from big tree
    //void makePlaceInTreeByIdMedValForRemove();
    //void makePlaceInTreeByIdSmallValForRemove();

    void updateTreeByStrengthSmallValForAdd(); //notice : name not correct!. this one updates both of small trees
    void updateTreeByStrengthMedValForAdd();//notice : name not correct!. this one updates both of med trees
    void updateTreeByStrengthBigValForAdd(); //notice : name not correct!. this one updates both of big trees
    //void updateTreeByStrengthSmallValForRemove(); //notice : name not correct!. this one updates both of small trees
    //void updateTreeByStrengthMedValForRemove();//notice : name not correct!. this one updates both of med trees
    //void updateTreeByStrengthBigValForRemove(); //notice : name not correct!. this one updates both of big trees
    void addContestantToATeam(int contestantId, int countryId, int strength, Sport sport);
    //void updateStateOfBalanceForRemove();
    //void removeContestantFromTeam(Contestant const& toRemove); //toRemove should be contestant with flag 0
    //void updateOptimalTeamStrength();
    // about the Contestant
    Contestant_Key get_maxInTreeByStrengthBigVal();
    Contestant_Key get_maxInTreeByStrengthMedVal();
    Contestant_Key get_maxInTreeByStrengthSmallVal();

    int get_optimalTeamStrength() const;
    void set_optimalTeamStrength(int optimalVal);

    AvlTree<Contestant_Key, Contestant>* get_treeByIdBigVal();
    AvlTree<Contestant_Key, Contestant>* get_treeByIdMedVal();
    AvlTree<Contestant_Key, Contestant>* get_treeByIdSmallVal();


    AvlTree<Contestant_Key, Contestant>* get_treeByStrengthBigVal();
    AvlTree<Contestant_Key, Contestant>* get_treeByStrengthMedVal();
    AvlTree<Contestant_Key, Contestant>* get_treeByStrengthSmallVal();

    AvlTree<Contestant_Key, Contestant>* get_team_whole_contestants_by_id();
    AvlTree<Contestant_Key, Contestant>* get_team_whole_contestants_by_strength();
};

#endif //WINTERAVLTREE_TEAM_H
