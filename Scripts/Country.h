//
// Created by maaya on 19/02/2024.
//

#ifndef WINTERAVLTREE_COUNTRY_H
#define WINTERAVLTREE_COUNTRY_H




#include "AvlTree.h"
#include "Contestant.h"
#include "Team.h"

class Country {
    int countryId;
    int medals;
    AvlTree<int, Contestant>* Contestants;
    AvlTree<int, Team>* Teams;
public:
    Country();
    Country(int countryId, int medals);
    AvlTree<int, Team>* getTeam();
    AvlTree<int, Contestant>* getContestant();
};

#endif //WINTERAVLTREE_COUNTRY_H
