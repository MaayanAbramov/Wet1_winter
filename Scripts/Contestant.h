//
// Created by maaya on 19/02/2024.
//

#ifndef WINTERAVLTREE_CONTESTANT_H
#define WINTERAVLTREE_CONTESTANT_H


//
// Created by USER on 12/02/2024.
//

#include "wet1util.h"


class Contestant {
    int contestantId;
    int countryId;
    int strength;
    Sport sport;
    //TO_DO::add boolean of < is_specail_sorted
public:
    Contestant();
    Contestant(int contestantId, int countryId, int strength, Sport sport);
    //TO_DO: add operatorOverloading

};



#endif //WINTERAVLTREE_CONTESTANT_H
