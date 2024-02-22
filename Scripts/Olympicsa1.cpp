#include "Olympicsa1.h"



Olympics::Olympics() : teams(nullptr), contestants(nullptr), countries(nullptr){}

Olympics::~Olympics(){}

StatusType Olympics::add_country(int countryId, int medals){
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

StatusType Olympics::remove_country(int countryId){
    if (countryId <= 0)
        return StatusType::INVALID_INPUT;

    auto node = countries->find(countryId, countries->root);
    if (node == nullptr || countries->numOfNodes == 0)
        return StatusType::FAILURE;
    if (node->getValue()->getContestants()->numOfNodes != 0 || node->getValue()->getTeams()->numOfNodes != 0) {
        return StatusType::FAILURE; //meaning if there exists at least one contestant or one team, the country is not
        // empty, which leads to failure
    }

    try {
        countries->remove(countryId);
    }
    catch (std::bad_alloc& ba){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Olympics::add_team(int teamId,int countryId,Sport sport){
    if (teamId <= 0 || countryId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (teams->find(teamId, teams->root) != nullptr || countries->find(countryId, countries->root) == nullptr) {
        return StatusType::FAILURE; //meaning if the team already existed or the country is not existing
    }
    try {
        Team toAdd = Team(teamId, sport, 0, countryId); //numParticipant = 0
        teams->insertAux(teamId, toAdd);
        AvlTree<int, Country>::Node* nodeOfCountry = countries->find(countryId, countries->root);
        if (nodeOfCountry == nullptr) {
            return StatusType::FAILURE;
        }
        nodeOfCountry->value.getTeams()->insertAux(teamId, toAdd);
        return StatusType::SUCCESS;
    }
    catch(std::bad_alloc& ba) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Olympics::remove_team(int teamId){
    if (teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    auto toRemove = teams->find(teamId, teams->root);
    if ( toRemove == nullptr || teams->numOfNodes != 0) {
        return StatusType::FAILURE;
    }
    try {
        if (teams->numOfNodes == 0 || teams->remove(teamId) == nullptr) {
            return StatusType::FAILURE;
        }
        if ( (countries->find(toRemove->value.getCountryId(), countries->root))->getValue()->getTeams()->numOfNodes
        == 0 ||
        (countries->find(toRemove->value.getCountryId(), countries->root))->getValue()->getTeams()->remove
        (teamId) == nullptr) //If removing the team from the specific country operation faild
            return StatusType::FAILURE;
    }
    catch(std::bad_alloc& ba) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Olympics::add_contestant(int contestantId ,int countryId,Sport sport,int strength){

}

StatusType Olympics::remove_contestant(int contestantId){
    return StatusType::FAILURE;
}

StatusType Olympics::add_contestant_to_team(int teamId,int contestantId){
    return StatusType::FAILURE;
}

StatusType Olympics::remove_contestant_from_team(int teamId,int contestantId){
    return StatusType::FAILURE;
}

StatusType Olympics::update_contestant_strength(int contestantId ,int change){
    return StatusType::FAILURE;
}

output_t<int> Olympics::get_strength(int contestantId){
    return 0;
}

output_t<int> Olympics::get_medals(int countryId){
    return 0;
}

output_t<int> Olympics::get_team_strength(int teamId){
    return 0;
}

StatusType Olympics::unite_teams(int teamId1,int teamId2){
    return StatusType::FAILURE;
}

StatusType Olympics::play_match(int teamId1,int teamId2){
    return StatusType::FAILURE;
}

output_t<int> Olympics::austerity_measures(int teamId){
    return 0;
}



