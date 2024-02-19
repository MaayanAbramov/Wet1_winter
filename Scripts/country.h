//
// Created by USER on 12/02/2024.
//

#ifndef WET1_WINTER_COUNTRY_H
#define WET1_WINTER_COUNTRY_H


#include "AvlTree.h"

class country {
    int countryId;
    int medals;
    AvlTree Contestant;
    AvlTree Team;
public:
    country(){}
    country(int countryId, int medals);
};


#endif //WET1_WINTER_COUNTRY_H
