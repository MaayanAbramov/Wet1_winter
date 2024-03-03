//
// Created by maaya on 19/02/2024.
//

#ifndef WINTERAVLTREE_COUNTRY_H
#define WINTERAVLTREE_COUNTRY_H




#include "AvlTree.h"
#include "Contestant.h"
#include "Team_Key.h"
#include "Team.h"

class Country {
    int countryId;
    int medals;
    int init_count;
    AvlTree<Contestant_Key, Contestant*>* country_contestants;
    AvlTree<Team_Key, Team*>* country_teams;
public:
    ~Country();
    Country();
    Country(int countryId, int medals);
    AvlTree<Team_Key, Team*>* getCountryTeams();
    AvlTree<Contestant_Key, Contestant*>* getCountryContestants();
    int getMedals();
    void IncMedalCountByOne();
};

#endif //WINTERAVLTREE_COUNTRY_H
