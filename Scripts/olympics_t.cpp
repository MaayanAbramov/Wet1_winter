//
// Created by maaya on 19/02/2024.
//

#include "olympics_t.h"
olympics_t::olympics_t() : teams(nullptr), contestants(nullptr), countries(nullptr){}
olympics_t::~olympics_t() {}
StatusType olympics_t::add_country(int countryId, int medals) {
    if (countryId <= 0 || medals < 0) {
        return StatusType::INVALID_INPUT;
    }
    if (countries->find(countryId, countries->root) != nullptr) {
        return StatusType::FAILURE;
    }
    try {
        Country* country1 = new Country(countryId, medals);
        countries->insertAux(countryId, *country1);
        return StatusType::SUCCESS;
    }
    catch(std::bad_alloc& ba) {
        return StatusType::ALLOCATION_ERROR;
    }





}
StatusType olympics_t::remove_country(int countryId) {
    if (countryId <= 0)
        return StatusType::INVALID_INPUT;

    auto node = countries->find(countryId, countries->root);
    if (node == nullptr)
        return StatusType::FAILURE;
    if (node->getValue()->getContestant()->root != nullptr || node->getValue()->getTeam()->root != nullptr ) {
        return StatusType::FAILURE;
    }
    try {
        countries->remove(countryId);
    }
    catch (std::bad_alloc& ba){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType olympics_t::add_team(int teamId, int countryId, Sport sport) {
    if (teamId <= 0 || countryId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (teams->find(teamId, teams->root) != nullptr || countries->find(countryId, countries->root) != nullptr) {
        return StatusType::FAILURE;
    }
    try {
        Team* teamToAdd = Team()
        teams->insertAux(teamId, )
    }

}
StatusType olympics_t::remove_team(int teamId) {

}
StatusType add_contestant(int contestant, int countryId, Sport sport, int strength) {

}
StatusType remove_contestant(int contestantId) {

}
StatusType add_contestant_to_team(int teamId, int contestantId) {

}
StatusType remove_contestant_from_team(int teamId, int contestantId) {

}
StatusType update_contestant_strength(int contestantId, int change) {

}