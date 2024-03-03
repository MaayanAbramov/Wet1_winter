//
// Created by maaya on 19/02/2024.
//

#include "Country.h"

Country::Country(int countryId, int medals) {
    this->countryId = countryId;
    this->medals = medals;
    this->country_contestants = new AvlTree<Contestant_Key, Contestant>();
    this->country_teams = new AvlTree<Team_Key, Team>();
}

AvlTree<Contestant_Key, Contestant>* Country::getCountryContestants() {
    return this->country_contestants;
}

AvlTree<Team_Key, Team>* Country::getCountryTeams() {
    return this->country_teams;
}
int Country:: getMedals(){
    return  this->medals;
}
void Country::IncMedalCountByOne(){
    this->medals += 1;
}