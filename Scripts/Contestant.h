//
// Created by maaya on 19/02/2024.
//

#ifndef WINTERAVLTREE_CONTESTANT_H
#define WINTERAVLTREE_CONTESTANT_H


//
// Created by USER on 12/02/2024.
//
#include "AvlTree.h"
#include "wet1util.h"
#define TEAM_TYPE_INIT 5
#define NUM_OF_MAX_TEAMS 3

class Contestant {

    int contestantId;
    int countryId;
    int strength;
    Sport sport;
    bool is_by_strength_sorted;
    int teamsIParticipate[3];

public:
    Contestant();
    Contestant(int contestantId, int countryId, int strength, Sport sport, bool is_by_strength_sorted);
    Contestant(const Contestant& other);
    ~Contestant() = default;
    bool operator==(const Contestant& other) const;
    friend bool operator<(const Contestant& num1, const Contestant& num2);
    friend bool operator>(const Contestant& num1, const Contestant& num2);
    int get_contestantId() const;
    int get_countryId() const;
    int get_strength() const;
    Sport get_sport() const;
    bool get_is_by_strength_sorted() const;
    void set_is_by_strength_sorted(bool is_by_strength);
    int get_teamsIParticipate(int index) const;
    void set_teamsIparticipate(int index, int teamId);
    void set_change_strength(int change);

};



#endif //WINTERAVLTREE_CONTESTANT_H
