//
// Created by USER on 12/02/2024.
//

#ifndef WET1_WINTER_CONTESTANT_H
#define WET1_WINTER_CONTESTANT_H


class contestant {
    int contestantId;
    int countryId;
    int strength;
    Sport sport;
public:
    contestant(int contestantId, int countryId, int strength, Sport sport){
        this->contestantId = contestantId;
        this->countryId = countryId;
        this->strength = strength;
        this->sport = sport;
    }
};




#endif //WET1_WINTER_CONTESTANT_H
