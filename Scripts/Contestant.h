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


class Contestant {
    int contestantId;
    int countryId;
    int strength;
    Sport sport;
    bool is_by_strength_sorted;


public:
    Contestant();
    Contestant(int contestantId, int countryId, int strength, Sport sport, bool is_by_strength_sorted);
    Contestant(const Contestant& other);
    ~Contestant() = default;
    friend bool operator<(const Contestant& num1, const Contestant& num2);
    friend bool operator>(const Contestant& num1, const Contestant& num2);


};



#endif //WINTERAVLTREE_CONTESTANT_H
