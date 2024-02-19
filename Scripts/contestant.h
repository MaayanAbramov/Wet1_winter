//
// Created by USER on 12/02/2024.
//

#ifndef WET1_WINTER_CONTESTANT_H
#define WET1_WINTER_CONTESTANT_H

#include "wet1util.h"


class contestant {
    int contestantId{};
    int countryId{};
    int strength{};
    Sport sport;
public:
    contestant(){}
    contestant(int contestantId, int countryId, int strength, Sport sport){}
};




#endif //WET1_WINTER_CONTESTANT_H
