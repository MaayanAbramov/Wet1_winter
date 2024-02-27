//
// Created by maaya on 19/02/2024.
//

#ifndef WINTERAVLTREE_COUNTRY_H
#define WINTERAVLTREE_COUNTRY_H




#include "AvlTree.h"
#include "Contestant.h"
#include "Team.h"

class Country_Key{
    int id;
public:
    explicit Country_Key(int id=-1): id(id) {
        assert(this->id!=-1);
    }

    Country_Key(const Country_Key& key) =default;
    ~Country_Key()=default;
    bool operator==(const Country_Key& key2){
        return this->id == key2.id;
    }
    friend bool operator<(const Country_Key& key1, const Country_Key& key2){
        return key1.id < key2.id;
    }
};
class Country {
    int countryId;
    int medals;
    AvlTree<Contestant_Key, Contestant>* Contestants;
    AvlTree<Team_Key, Team>* Teams;
public:
    Country();
    Country(int countryId, int medals);
    AvlTree<Team_Key, Team>* getTeams();
    AvlTree<Team_Key, Contestant>* getContestants();
};

#endif //WINTERAVLTREE_COUNTRY_H
