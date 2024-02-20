//
// Created by maaya on 19/02/2024.
//

#include "Country.h"

Country::Country(int countryId, int medals) {
    this->countryId = countryId;
    this->medals = medals;
}

AvlTree<int, Contestant> *Country::getContestants() {
    return this->Contestants;
}

AvlTree<int, Team> *Country::getTeams() {
    return this->Teams;
}