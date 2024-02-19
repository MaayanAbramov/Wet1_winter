//
// Created by maaya on 19/02/2024.
//

#ifndef WINTERAVLTREE_OLYMPICS_T_H
#define WINTERAVLTREE_OLYMPICS_T_H

#include "AvlTree.h"
#include "wet1util.h"
#include "Team.h"
#include "Contestant.h"
#include "Country.h"



class olympics_t {
    AvlTree<int, Team>* teams;
    AvlTree<int, Contestant>* contestants;
    AvlTree<int, Country>* countries;

public:
    olympics_t(const olympics_t& other) = delete;
    olympics_t();
    virtual ~olympics_t();
    StatusType add_country(int countryId, int medals);
    StatusType remove_country(int countryId);
    StatusType add_team(int teamId, int countryId, Sport sport);
    StatusType remove_team(int teamId);
    StatusType add_contestant(int contestant, int countryId, Sport sport, int strength);
    StatusType remove_contestant(int contestantId);
    StatusType add_contestant_to_team(int teamId, int contestantId);
    StatusType remove_contestant_from_team(int teamId, int contestantId);
    StatusType update_contestant_strength(int contestantId, int change);



};


#endif //WINTERAVLTREE_OLYMPICS_T_H
