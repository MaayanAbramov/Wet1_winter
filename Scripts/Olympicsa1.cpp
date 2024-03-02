#include "Olympicsa1.h"



Olympics::Olympics() : teams(nullptr), contestants(nullptr), countries(nullptr){}

Olympics::~Olympics(){}

StatusType Olympics::add_country(int countryId, int medals){
    if (countryId <= 0 || medals < 0) {
        return StatusType::INVALID_INPUT;
    }
    Country_Key countryKey = Country_Key(countryId);
    if (countries->find(countryKey, countries->root) != nullptr) {
        return StatusType::FAILURE;
    }
    try {
        Country* country1 = new Country(countryId, medals);

        countries->insertAux(countryKey, *country1);
        return StatusType::SUCCESS;
    }
    catch(...) { //std::bad_alloc& ba, remember to change it
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Olympics::remove_country(int countryId){
    if (countryId <= 0)
        return StatusType::INVALID_INPUT;
    Country_Key countryKey  = Country_Key(countryId);
    auto node = countries->find(countryKey, countries->root);
    if (node == nullptr)
        return StatusType::FAILURE;
    if (node->getValue()->getCountryContestants()->numOfNodes != 0 || node->getValue()->getCountryTeams()->numOfNodes
    != 0) {
        return StatusType::FAILURE; //meaning if there exists at least one contestant or one team, the country is not
        // empty, which leads to failure
    }

    try {
        countries->remove(countryKey);
    }
    catch (...){//std::bad_alloc& ba, remember to change it
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Olympics::add_team(int teamId,int countryId,Sport sport){
    if (teamId <= 0 || countryId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Team_Key keyToAdd = Team_Key(teamId);
    Country_Key keyToCountry = Country_Key(countryId);
    if (teams->find(keyToAdd, teams->root) != nullptr || countries->find(keyToCountry, countries->root) == nullptr) {
        return StatusType::FAILURE; //meaning if the team already existed or the country is not existing
    }
    try {
        Team toAdd = Team(teamId, sport, countryId); //numParticipant = 0
        teams->insertAux(keyToAdd, toAdd);
        AvlTree<Country_Key, Country>::Node* nodeOfCountry = countries->find(keyToCountry, countries->root);
        if (nodeOfCountry == nullptr) {
            return StatusType::FAILURE;
        }
        auto ptrToTeamForInsert = teams->find(keyToAdd, teams->root);
        nodeOfCountry->value.getCountryTeams()->insertAux(keyToAdd, *(ptrToTeamForInsert->getValue()));
        return StatusType::SUCCESS;
    }
    catch(...) {//std::bad_alloc& ba, remember to change it
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Olympics::remove_team(int teamId){ //remember there are more teams than countries
    //O(logm) = O(logk + logm)
    if (teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Team_Key teamKey = Team_Key(teamId);
    auto toRemove = teams->find(teamKey, teams->root);
    if ( toRemove == nullptr || toRemove->getValue()->get_team_whole_contestants_by_id()->numOfNodes != 0) {
        return StatusType::FAILURE;
    }
    try {
        Country_Key countryKey = Country_Key(toRemove->value.getCountryId());
        auto nodeOfCountry = countries->find(countryKey, countries->root);
        nodeOfCountry->getValue()->getCountryTeams()->remove(teamKey);
        teams->remove(teamKey);
    }
    catch(...) {//std::bad_alloc& ba, remember to change it
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Olympics::add_contestant(int contestantId ,int countryId,Sport sport,int strength){
    try {
        if (contestantId <=0 || countryId <=0 || strength < 0) {
            return StatusType::INVALID_INPUT;
        }
        Contestant_Key contestantKey = Contestant_Key(contestantId, strength, false);
        auto isContestantFound = contestants->find(contestantKey, contestants->root);
        if (isContestantFound != nullptr) {
            return StatusType::FAILURE;
        }
        Country_Key countryKey = Country_Key(countryId);
        auto isCountryFound = countries->find(countryKey, countries->root);
        if (isCountryFound == nullptr) {
            return StatusType::FAILURE;
        }
        Contestant toAdd = Contestant(contestantId, countryId, strength, sport, false); //the bool does not matter
        contestants->insertAux(contestantKey, toAdd);
        isCountryFound->getValue()->getCountryContestants()->insertAux(contestantKey, toAdd);
    }
    catch(...) {//std::bad_alloc& ba, remember to change it
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Olympics::remove_contestant(int contestantId){
    try {
        if (contestantId <= 0) {
            return StatusType::INVALID_INPUT;
        }
        Contestant_Key contestantKeyId = Contestant_Key(contestantId, -2, false);
        auto isContestantFound = contestants->find(contestantKeyId, contestants->root);
        if (isContestantFound == nullptr) {
            return StatusType::FAILURE;
        }
        for (int i = 0 ; i < 3 ; i++) {
            if (isContestantFound->getValue()->get_teamsIParticipate(i) != -2) {
                return StatusType::FAILURE;
            }
        }
        Country_Key countryKey = Country_Key(isContestantFound->getValue()->get_countryId());
        countries->find(countryKey, countries->root)->getValue()->getCountryContestants()->remove(contestantKeyId);
        contestants->remove(contestantKeyId);
    }
    catch(...) {//std::bad_alloc& ba, remember to change it
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::FAILURE;
}

bool Olympics::compare_country_ids_and_sports(int teamId, int contestantId){
    Contestant_Key contestantKeyToFind = Contestant_Key(contestantId, -2, false);
    auto contestantToAddToTeam = contestants->find(contestantKeyToFind, contestants->root);
    Contestant_Key contestantKey = *(contestantToAddToTeam->getKey());
    int countryIdOfContestant = contestantToAddToTeam->getValue()->get_countryId();
    Team_Key keyOfTeamToAddTo = Team_Key(teamId);
    auto teamToAddTo = teams->find(keyOfTeamToAddTo, teams->root);
    int countryIdOfTeamToAddTo = teamToAddTo->getValue()->getCountryId();
    Sport contestantSport = contestantToAddToTeam->getValue()->get_sport();
    Sport teamSport = *(teamToAddTo->getValue()->getSport());
    return countryIdOfContestant == countryIdOfTeamToAddTo && teamSport == contestantSport;
}

StatusType Olympics::add_contestant_to_team(int teamId,int contestantId){
    if (teamId <= 0 || contestantId <= 0) {
        return StatusType::FAILURE;
    }
    /*----------------------all this to compare the countryIds of contestant and team----------------------*/
    bool same_countryid_and_sports = this->compare_country_ids_and_sports(teamId,contestantId);
    if (!same_countryid_and_sports) {
        return StatusType::FAILURE;
    }
//    /*----------------------all this to compare the sports of contestant and team----------------------*/

    /*----------------------------now getting the last index------------------------------*/
    //int counter = 0;
    int first_empty_index = -1;
    Contestant_Key contestantKeyToFind = Contestant_Key(contestantId, -2, false);
    auto contestantToAddToTeam = contestants->find(contestantKeyToFind, contestants->root);
    int countryIdOfContestant = contestantToAddToTeam->getValue()->get_countryId();
    Team_Key keyOfTeamToAddTo = Team_Key(teamId);
    auto teamToAddTo = teams->find(keyOfTeamToAddTo, teams->root);
    int countryIdOfTeamToAddTo = teamToAddTo->getValue()->getCountryId();
    Contestant_Key contestantKey = *(contestantToAddToTeam->getKey());
    for (int i = 0; i < NUM_OF_MAX_TEAMS; i++) {
        if(contestantToAddToTeam->getValue()->get_teamsIParticipate(i) == teamId) {
            return StatusType::FAILURE;
        }
        if (contestantToAddToTeam->getValue()->get_teamsIParticipate(i) == -2 && first_empty_index == -1) {
            first_empty_index =i;
        }
    }
    if (first_empty_index == -1) {
        return StatusType::FAILURE;

    }
    try {
        /*--------------here we updating teams of olympics, only last elem in array----------------------------*/
        int contestantStrength = contestantToAddToTeam->getValue()->get_strength();
        teamToAddTo->getValue()->addContestantToATeam(contestantKey, contestantToAddToTeam->getValue() , false);
        //now also need to add contestant to the country
        /*-----------here we updating teams in country, only last elem in array------------------------------------*/
        Country_Key countryKey = Country_Key(countryIdOfContestant);
        auto countryToUpdate = countries->find(countryKey, countries->root);
        auto teamInCountry = countryToUpdate->getValue()->getCountryTeams()->find(keyOfTeamToAddTo,
                                                                                  countryToUpdate->getValue()->getCountryTeams()->root);
        teamInCountry->getValue()->addContestantToATeam(contestantKey, contestantToAddToTeam->getValue() , false);
        /*------------------------now we are updating all the left teams in the array----------------------------*/

        //also need to update it in all the past teams
        for (int i = 0 ; i < NUM_OF_MAX_TEAMS  ; i++){

            int pastTeamId = contestantToAddToTeam->getValue()->get_teamsIParticipate(i);
            if (pastTeamId == -2)
            {
                continue;
            }
            //need to update in the country teams tree
            //and also in the teams olympics teams
            Team_Key pastTeamKey = Team_Key(pastTeamId);
            auto pastTeamToUpdate = teams->find(pastTeamKey, teams->root)->getValue();
            pastTeamToUpdate->update_contestant_team_array(contestantId,first_empty_index,teamId);
            auto rootOfCountry = countryToUpdate->getValue()->getCountryTeams();
            rootOfCountry->find(pastTeamKey, rootOfCountry->root)->getValue()->update_contestant_team_array
            (contestantId,first_empty_index,teamId);
        }
    }
    catch(...) {//std::bad_alloc& ba, remember to change it
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Olympics::remove_contestant_from_team(int teamId,int contestantId){
    try {
        if (contestantId <= 0 || teamId <= 0) {
            return StatusType::INVALID_INPUT;
        }
        Team_Key teamKey = Team_Key(teamId);
        auto isTeamFound = teams->find(teamKey, teams->root);
        if (isTeamFound == nullptr) {
            return StatusType::FAILURE;
        }
        Contestant_Key contestantKeyToFind = Contestant_Key(contestantId, -2, false);
        auto contestantToFind = contestants->find(contestantKeyToFind, contestants->root);
        if (contestantToFind == nullptr){
            return StatusType::FAILURE;
        }
        Contestant_Key contestantKey = *(contestantToFind->getKey());
        auto tree_of_contestants_in_team = isTeamFound->getValue()->get_team_whole_contestants_by_id();
        if (tree_of_contestants_in_team->find(contestantKey, tree_of_contestants_in_team->root) == nullptr) {
            return StatusType::FAILURE;
        }

        //first we remove the contestant from the specific team, updating his array to be -2 in index_to_delete
        //now we iterate on the array, and upate in the right index all the teams, like we did in
        // addcontestanttoteam, only now we update it to -2 instead.
        //remember to remove from the counrty tree and from the olympics tree
        //first to first we update the contestants
        int countryId = isTeamFound->getValue()->getCountryId();
        auto isCountryFound = countries->find(Country_Key(countryId), countries->root);
        assert(isCountryFound != nullptr);
        auto team_to_remove_from_in_country = isCountryFound->getValue()->getCountryTeams()->find(teamKey,
                                                                                                   isCountryFound->getValue()->getCountryTeams()->root );
        team_to_remove_from_in_country->getValue()->removeContestantFromTeam(contestantKey,false);
        isTeamFound->getValue()->removeContestantFromTeam(contestantKey,false);
        int index_to_update = -1;
        for (int i = 0; i < NUM_OF_MAX_TEAMS; ++i) {
            if(contestantToFind->getValue()->get_teamsIParticipate(i)==teamId){
                index_to_update = i;
            }
        }
        assert(index_to_update != -1);
        contestantToFind->getValue()->set_teamsIparticipate(index_to_update, -2);

        isCountryFound->getValue()->getCountryContestants()->find(contestantKey, isCountryFound->getValue()
        ->getCountryContestants()->root)->getValue()->set_teamsIparticipate(index_to_update, -2);
        for (int i = 0 ; i < NUM_OF_MAX_TEAMS ; i++) {
            int teamId_to_update = contestantToFind->getValue()->get_teamsIParticipate(i);
            if (teamId_to_update == -2) {
                continue;
            }
            Team_Key pastTeamKey = Team_Key(teamId_to_update);
            auto pastTeamToUpdate = teams->find(pastTeamKey, teams->root)->getValue();
            pastTeamToUpdate->update_contestant_team_array(contestantId,index_to_update,-2);
            auto rootOfCountry = isCountryFound->getValue()->getCountryTeams();
            rootOfCountry->find(pastTeamKey, rootOfCountry->root)->getValue()->update_contestant_team_array
                    (contestantId,index_to_update,-2);

        }
    }
    catch(...) {//std::bad_alloc& ba, remember to change it
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Olympics::update_contestant_strength(int contestantId ,int change){
    try {
        if (contestantId <= 0) {
            return StatusType::INVALID_INPUT;
        }
        Contestant_Key contestantKeyToFind = Contestant_Key(contestantId, -2, false);
        auto isContestantFound = contestants->find(contestantKeyToFind, contestants->root);
        if (isContestantFound == nullptr) {
            return StatusType::FAILURE;
        }
        Contestant_Key contestantKey = *(isContestantFound->getKey());
        if (contestantKey.strength + change < 0) {
            return StatusType::FAILURE;
        }
        /*------------------update in contestants--------------------------------*/
        auto contestantInContestants = contestants->find(contestantKey, contestants->root);
        assert(contestantInContestants != nullptr);
        contestantInContestants->getValue()->set_change_strength(change);
        contestantInContestants->getKey()->strength += change;
        /*-----------------update in country contestants--------------------------*/
        Country_Key countryKey = Country_Key(isContestantFound->getValue()->get_countryId());
        auto countryToUpdate = countries->find(countryKey, countries->root);
        countryToUpdate->getValue()->getCountryContestants()->find(contestantKey,countryToUpdate->getValue()
        ->getCountryContestants()->root)->getValue()->set_change_strength(change);
        countryToUpdate->getValue()->getCountryContestants()->find(contestantKey,countryToUpdate->getValue()
                ->getCountryContestants()->root)->getKey()->strength += change;
        /*--------------update in country teams and teams---------------------------*/
        for (int i = 0 ; i < NUM_OF_MAX_TEAMS ; i++) {
            int teamId_to_update = contestantInContestants->getValue()->get_teamsIParticipate(i);
            if (teamId_to_update == -2) {
                continue;
            }
            Team_Key pastTeamKey = Team_Key(teamId_to_update);
            auto pastTeamToUpdate = teams->find(pastTeamKey, teams->root);
            //please notice that contestantKey still doesnt contain the new strength
            pastTeamToUpdate->getValue()->removeContestantFromTeam(contestantKey, false);
            Contestant_Key contestantKeyUpdated = *(contestantInContestants->getKey());
            pastTeamToUpdate->getValue()->addContestantToATeam(contestantKeyUpdated,contestantInContestants->getValue
            (), false);

            auto rootOfCountry = countryToUpdate->getValue()->getCountryTeams();
            rootOfCountry->find(pastTeamKey, rootOfCountry->root)->getValue()->removeContestantFromTeam
            (contestantKey, false);
            rootOfCountry->find(pastTeamKey, rootOfCountry->root)->getValue()->addContestantToATeam(contestantKeyUpdated,contestantInContestants->getValue
                    (), false);

        }

    }
    catch(...) {//std::bad_alloc& ba, remember to change it
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

output_t<int> Olympics::get_strength(int contestantId){
    try {
        if (contestantId <= 0) {
            return output_t<int>(StatusType::INVALID_INPUT);
        }
        auto isContestantFound = contestants->find(Contestant_Key(contestantId), contestants->root);
        if (isContestantFound == nullptr) {
            return output_t<int>(StatusType::FAILURE);
        }
    }
    catch(...) {//std::bad_alloc& ba, remember to change it
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }
    return output_t<int>(contestants->find(Contestant_Key(contestantId,-2,false),contestants->root)->getKey()
    ->strength);
}

output_t<int> Olympics::get_medals(int countryId){
    try {
        if (countryId <= 0) {
            return output_t<int>(StatusType::INVALID_INPUT);
        }
        auto isCountryFound = countries->find(Country_Key(countryId), countries->root);
        if (isCountryFound == nullptr) {
            return output_t<int>(StatusType::FAILURE);
        }

    }
    catch(...) {//std::bad_alloc& ba, remember to change it
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }
    return output_t<int>(countries->find(Country_Key(countryId),countries->root)->getValue()->getMedals());
}

output_t<int> Olympics::get_team_strength(int teamId){
    if (teamId <= 0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    auto node = this->teams->find(Team_Key(teamId),this->teams->root);
    if (node == nullptr) {
        return output_t<int>(StatusType::FAILURE);
    }
    auto team = this->teams->find(Team_Key(teamId),this->teams->root)->getValue();
    if (team->getNumParticipants()%3==0)
    {
        return output_t<int>(team->get_maxInTreeByStrengthSmallVal().strength + team->get_maxInTreeByStrengthMedVal()
        .strength +
        team->get_maxInTreeByStrengthBigVal().strength);
    }
    else {
        return output_t<int>(0);
    }
}

StatusType Olympics::unite_teams(int teamId1,int teamId2){
    try {
        if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) {
            return StatusType::FAILURE;
        }
        auto isTeamOneFound = teams->find(Team_Key(teamId1), teams->root);
        auto isTeamTwoFound = teams->find(Team_Key(teamId2), teams->root);
        if (isTeamOneFound == nullptr || isTeamTwoFound == nullptr) {
            return StatusType::FAILURE;
        }
        /*------------------------check if countryIds and Sports of both teams are not equal---------------*/
        Team_Key keyOfTeamToAddTo1 = Team_Key(teamId1);
        auto teamToAddTo1 = teams->find(keyOfTeamToAddTo1, teams->root);
        Team_Key keyOfTeamToAddTo2 = Team_Key(teamId2);
        auto teamToAddTo2 = teams->find(keyOfTeamToAddTo2, teams->root);
        int countryIdOf1 = teamToAddTo1->getValue()->getCountryId();
        int countryIdOf2 = teamToAddTo2->getValue()->getCountryId();
        Sport *sportOf1 = teamToAddTo1->getValue()->getSport();
        Sport *sportOf2 = teamToAddTo2->getValue()->getSport();
        if (countryIdOf1 != countryIdOf2 || *sportOf1 != *sportOf2) {
            return StatusType::FAILURE;
        }
        while(isTeamTwoFound->getValue()->getNumParticipants()!=0){
            auto team2_min_node = isTeamTwoFound->getValue()->get_team_whole_contestants_by_id()->findMin
                    (isTeamTwoFound->getValue()->get_team_whole_contestants_by_id()->root);
            Contestant team2_min_contestant = Contestant(*team2_min_node->getValue());
            Contestant_Key team2_min_Key = Contestant_Key(*team2_min_node->getKey());
            if(isTeamOneFound->getValue()->get_team_whole_contestants_by_id()->find(team2_min_Key,
                                                                                    isTeamOneFound->getValue()->get_team_whole_contestants_by_id()->root)==nullptr) {
                isTeamTwoFound->getValue()->removeContestantFromTeam(team2_min_Key, false);
                isTeamOneFound->getValue()->addContestantToATeam(team2_min_Key, &team2_min_contestant, false);
                //now do the same for team 1 and teams 2 in olympicsa->teams tree
                auto team2_min_node_from_teams = teamToAddTo2->getValue()->get_team_whole_contestants_by_id()->findMin
                        (teamToAddTo2->getValue()->get_team_whole_contestants_by_id()->root);

                Contestant team2_min_contestant_from_teams = Contestant(*team2_min_node_from_teams->getValue());
                Contestant_Key team2_min_Key_from_teams = Contestant_Key(*team2_min_node_from_teams->getKey());
                isTeamTwoFound->getValue()->removeContestantFromTeam(team2_min_Key_from_teams, false);
                isTeamOneFound->getValue()->addContestantToATeam(team2_min_Key_from_teams,
                                                                 &team2_min_contestant_from_teams, false);
            }

        }
        this->remove_team(teamId2);
    }
    catch(...) {//std::bad_alloc& ba, remember to change it
        return StatusType::ALLOCATION_ERROR;
    }



}

StatusType Olympics::play_match(int teamId1,int teamId2){
    try {
        if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) {
            return StatusType::FAILURE;
        }
        auto isTeamOneFound = teams->find(Team_Key(teamId1), teams->root);
        auto isTeamTwoFound = teams->find(Team_Key(teamId2), teams->root);
        if (isTeamOneFound == nullptr || isTeamTwoFound == nullptr) {
            return StatusType::FAILURE;
        }
        /*------------------------check if countryIds and Sports of both teams are not equal---------------*/
        Team_Key keyOfTeamToAddTo1 = Team_Key(teamId1);
        auto teamToAddTo1 = teams->find(keyOfTeamToAddTo1, teams->root);
        Team_Key keyOfTeamToAddTo2 = Team_Key(teamId2);
        auto teamToAddTo2 = teams->find(keyOfTeamToAddTo2, teams->root);
        int countryIdOf1 = teamToAddTo1->getValue()->getCountryId();
        int countryIdOf2 = teamToAddTo2->getValue()->getCountryId();
        Country_Key country_key1 = Country_Key(countryIdOf1);
        Country_Key country_key2 = Country_Key(countryIdOf2);
        auto country1_node = this->countries->find(country_key1,this->countries->root);
        auto country2_node = this->countries->find(country_key2,this->countries->root);
        assert(country1_node!=nullptr &&  country2_node!= nullptr);
        auto country1= country1_node->getValue();
        auto country2= country2_node->getValue();
        Sport *sportOf1 = teamToAddTo1->getValue()->getSport();
        Sport *sportOf2 = teamToAddTo2->getValue()->getSport();
        if (*sportOf1 != *sportOf2) {
            return StatusType::FAILURE;
        }
        int nikood_team_1=this->get_strength(teamId1).ans()+country1->getMedals();
        int nikood_team_2=this->get_strength(teamId2).ans()+country2->getMedals();
        if(nikood_team_1==nikood_team_2){
            //if equal, dont do anything, but return success(ki ze teko)
            return StatusType::SUCCESS;
        }
        else{
            nikood_team_1>nikood_team_2?country1->IncMedalCountByOne():country2->IncMedalCountByOne();
            return StatusType::SUCCESS;
        }
    }
    catch(...) {//std::bad_alloc& ba, remember to change it
        return StatusType::ALLOCATION_ERROR;
    }

}

output_t<int> Olympics::austerity_measures(int teamId){
    return this->teams->find(Team_Key(teamId),this->teams->root)->getValue()->get_optimalTeamStrength();
}



