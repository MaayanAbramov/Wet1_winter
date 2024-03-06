#include "Olympicsa1.h"


void fill_array_of_repeated_contestants(AvlTree<struct Contestant_Key, struct Contestant *> *pTree,
                                        AvlTree<Contestant_Key, Contestant *>::Node *pNode, Contestant **pContestant,
                                        Contestant_Key *pKey);

Olympics::Olympics()  {
    this->teams = new AvlTree<Team_Key, Team*>();
    this->contestants = new AvlTree<Contestant_Key, Contestant*>();
    this->countries = new AvlTree<Country_Key, Country*>();
}

Olympics::~Olympics(){
    AvlTree<Contestant_Key,Contestant*>::destroy_the_tree_and_values(contestants->root);
    delete contestants;
    Country::DestroyTreeOfTeams(teams->root);
    delete teams;
    AvlTree<Country_Key,Country*>::destroy_the_tree_and_values(countries->root);
    delete countries;
}

StatusType Olympics::add_country(int countryId, int medals){
    if (countryId <= 0 || medals < 0) {
        return StatusType::INVALID_INPUT;
    }
    Country_Key countryKey = Country_Key(countryId);
    if (countries->root != nullptr) {
        if (countries->find(countryKey, countries->root) != nullptr) {
            return StatusType::FAILURE;
        }
    }

    try {

        Country* country1 = new Country(countryId, medals);
        countries->insertAux(countryKey, country1);
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
    Country* country = *(node->getValue());
    if (country->getCountryContestants()->numOfNodes != 0 || country->getCountryTeams()->numOfNodes!= 0) {
        return StatusType::FAILURE; //meaning if there exists at least one contestant or one team, the country is not
        // empty, which leads to failure
    }

    try {
        auto to_delete = *(countries->find(countryKey,countries->root)->getValue());
        countries->remove(countryKey);
        delete to_delete;
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
        Team* toAddtoCountry = new Team(teamId, sport, countryId); //numParticipant = 0
        Team* toAddtoteams = new Team(teamId, sport, countryId);

        auto nodeOfCountry = countries->find(keyToCountry, countries->root);
        if (nodeOfCountry == nullptr) {
            delete toAddtoteams;
            delete toAddtoCountry;
            return StatusType::FAILURE;
        }
        teams->insertAux(keyToAdd, toAddtoteams);
        nodeOfCountry->value->getCountryTeams()->insertAux(keyToAdd, toAddtoCountry);
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
    Team_Key teamKey =  Team_Key(teamId);
    auto toRemove = teams->find(teamKey, teams->root);
    if ( toRemove == nullptr || toRemove->value->get_team_whole_contestants_by_id()->numOfNodes != 0) {
        return StatusType::FAILURE;
    }
    try {
        Country_Key countryKey = Country_Key(toRemove->value->getCountryId());
        auto nodeOfCountry = countries->find(countryKey, countries->root);
        Team* toDeleteInCountry = nodeOfCountry->value->getCountryTeams()->find(teamKey,
                                                                                nodeOfCountry->value->getCountryTeams
                                                                                ()->root)->value;
        (*(nodeOfCountry->getValue()))->getCountryTeams()->remove(teamKey);
        Team* to_delete = teams->find(teamKey,teams->root)->value;
        teams->remove(teamKey);
        delete toDeleteInCountry;
        delete to_delete;
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
        Contestant* Contestant_toAddcontestants = new Contestant(contestantId, countryId, strength, sport, false);
        //the bool does not matter
        Contestant* Contestant_toAddCountry = new Contestant(contestantId, countryId, strength, sport, false);
        contestants->insertAux(contestantKey, Contestant_toAddcontestants);
        (*isCountryFound->getValue())->getCountryContestants()->insertAux(contestantKey, Contestant_toAddCountry);
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
            if (isContestantFound->value->get_teamsIParticipate(i) != -2) {
                return StatusType::FAILURE;
            }
        }
        Country_Key countryKey = Country_Key(isContestantFound->value->get_countryId());
        auto country = countries->find(countryKey, countries->root)->value;
        Contestant* to_delete_country = country->getCountryContestants()->find(isContestantFound->key,
                                                                         country->getCountryContestants()
                ->root)->value;
        Contestant* to_delete_contestant = isContestantFound->value;
        (*countries->find(countryKey, countries->root)->getValue())->getCountryContestants()->remove(contestantKeyId);
        contestants->remove(contestantKeyId);
        delete to_delete_contestant;
        delete to_delete_country;
    }
    catch(...) {//std::bad_alloc& ba, remember to change it
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

bool Olympics::compare_country_ids_and_sports(int teamId, int contestantId){
    Contestant_Key contestantKeyToFind = Contestant_Key(contestantId, -2, false);
    auto contestantToAddToTeam = contestants->find(contestantKeyToFind, contestants->root);
    //Contestant_Key contestantKey = *(contestantToAddToTeam->getKey());
    int countryIdOfContestant = contestantToAddToTeam->value->get_countryId();
    Team_Key keyOfTeamToAddTo = Team_Key(teamId);
    auto teamToAddTo = teams->find(keyOfTeamToAddTo, teams->root);
    int countryIdOfTeamToAddTo = teamToAddTo->value->getCountryId();
    Sport contestantSport = contestantToAddToTeam->value->get_sport();
    Sport teamSport = *(teamToAddTo->value->getSport());
    return countryIdOfContestant == countryIdOfTeamToAddTo && teamSport == contestantSport;
}

StatusType Olympics::add_contestant_to_team(int teamId,int contestantId){
    if (teamId <= 0 || contestantId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    /*----------------------all this to compare the countryIds of contestant and team----------------------*/
    if (this->teams->find(Team_Key(teamId), teams->root) == nullptr) {
        return StatusType::FAILURE;
    }
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
    int countryIdOfContestant = contestantToAddToTeam->value->get_countryId();
    Team_Key keyOfTeamToAddTo = Team_Key(teamId);
    auto teamToAddTo = teams->find(keyOfTeamToAddTo, teams->root);
    int countryIdOfTeamToAddTo = teamToAddTo->value->getCountryId();
    Contestant_Key contestantKey = *(contestantToAddToTeam->getKey());
    for (int i = 0; i < NUM_OF_MAX_TEAMS; i++) {
        if(contestantToAddToTeam->value->get_teamsIParticipate(i) == teamId) {
            return StatusType::FAILURE;
        }
        if (contestantToAddToTeam->value->get_teamsIParticipate(i) == -2 && first_empty_index == -1) {
            first_empty_index =i;
            break;
        }
    }

    if (first_empty_index == -1) {
        return StatusType::FAILURE;
    }
    try {
        /*--------------here we updating teams of olympics, only last elem in array----------------------------*/
        int contestantStrength = contestantToAddToTeam->value->get_strength();
        teamToAddTo->value->addContestantToATeam(contestantKey, contestantToAddToTeam->value , false);
        contestantToAddToTeam->value->set_teamsIparticipate(first_empty_index, -2);//last line worked fine,
        //it updated the instance of contestant in all the team in teams. now I updates the copy to be just as before
        //now also need to add contestant to the country
        /*-----------here we updating teams in country, only last elem in array------------------------------------*/
        Country_Key countryKey = Country_Key(countryIdOfContestant);
        auto countryToUpdate = countries->find(countryKey, countries->root);
        auto teamInCountry = (*countryToUpdate->getValue())->getCountryTeams()->find(keyOfTeamToAddTo,
                                                                                     (*countryToUpdate->getValue())
                                                                                  ->getCountryTeams()->root);
        teamInCountry->value->addContestantToATeam(contestantKey, contestantToAddToTeam->value , false);
        /*countryToUpdate->value->getCountryContestants()->find(contestantKey,
                                                              countryToUpdate->value->getCountryContestants()->root)
                                                              ->value->set_teamsIparticipate(first_empty_index,
                                                              teamId);*/
        /*------------------------now we are updating all the left teams in the array----------------------------*/

        //also need to update it in all the past teams
        contestantToAddToTeam->value->set_teamsIparticipate(first_empty_index,teamId);
        for (int i = 0 ; i < NUM_OF_MAX_TEAMS  ; i++){

            int pastTeamId = contestantToAddToTeam->value->get_teamsIParticipate(i);
            if (pastTeamId == -2 || i == first_empty_index)
            {
                continue;
            }
            //need to update in the country teams tree
            //and also in the teams olympics teams
            Team_Key pastTeamKey = Team_Key(pastTeamId);
            auto pastTeamToUpdate = teams->find(pastTeamKey, teams->root)->value;
            pastTeamToUpdate->update_contestant_team_array(contestantId,first_empty_index,teamId);
            auto rootOfCountry = (*countryToUpdate->getValue())->getCountryTeams();
            rootOfCountry->find(pastTeamKey, rootOfCountry->root)->value->update_contestant_team_array
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
        auto tree_of_contestants_in_team = isTeamFound->value->get_team_whole_contestants_by_id();
        if (tree_of_contestants_in_team->find(contestantKey, tree_of_contestants_in_team->root) == nullptr) {
            return StatusType::FAILURE;
        }

        //first we remove the contestant from the specific team, updating his array to be -2 in index_to_delete
        //now we iterate on the array, and upate in the right index all the teams, like we did in
        // addcontestanttoteam, only now we update it to -2 instead.
        //remember to remove from the counrty tree and from the olympics tree
        //first to first we update the contestants
        int countryId = isTeamFound->value->getCountryId();
        auto isCountryFound = countries->find(Country_Key(countryId), countries->root);
        assert(isCountryFound != nullptr);
        auto team_to_remove_from_in_country = (*isCountryFound->getValue())->getCountryTeams()->find(teamKey,
                                                                                                     (*isCountryFound->getValue())->getCountryTeams()->root );
        team_to_remove_from_in_country->value->removeContestantFromTeam(contestantKey,false);
        isTeamFound->value->removeContestantFromTeam(contestantKey,false);
        int index_to_update = -1;
        for (int i = 0; i < NUM_OF_MAX_TEAMS; i++) {
            if(contestantToFind->value->get_teamsIParticipate(i) == -2 ){
                continue;
            }
            if(contestantToFind->value->get_teamsIParticipate(i)==teamId){
                index_to_update = i;
                break;
            }
        }
        assert(index_to_update != -1);
        contestantToFind->value->set_teamsIparticipate(index_to_update, -2);

        (*isCountryFound->getValue())->getCountryContestants()->find(contestantKey, (*isCountryFound->getValue())
        ->getCountryContestants()->root)->value->set_teamsIparticipate(index_to_update, -2);
        for (int i = 0 ; i < NUM_OF_MAX_TEAMS ; i++) {
            int teamId_to_update = contestantToFind->value->get_teamsIParticipate(i);
            if (teamId_to_update == -2) {
                continue;
            }
            Team_Key pastTeamKey = Team_Key(teamId_to_update);
            auto pastTeamToUpdate = teams->find(pastTeamKey, teams->root)->value;
            pastTeamToUpdate->update_contestant_team_array(contestantId,index_to_update,-2);
            auto rootOfCountry = (*isCountryFound->getValue())->getCountryTeams();
            rootOfCountry->find(pastTeamKey, rootOfCountry->root)->value->update_contestant_team_array
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
        contestantKey = (*contestantInContestants->getKey());//now contestantKey contains the old strength
        assert(contestantInContestants != nullptr);
        contestantInContestants->value->set_change_strength(change);
        contestantInContestants->getKey()->strength += change;
        /*-----------------update in country contestants--------------------------*/
        Country_Key countryKey = Country_Key(isContestantFound->value->get_countryId());
        auto countryToUpdate = countries->find(countryKey, countries->root);
        (*countryToUpdate->getValue())->getCountryContestants()->find(contestantKey,(*countryToUpdate->getValue()
        )->getCountryContestants()->root)->value->set_change_strength(change);
        (*countryToUpdate->getValue())->getCountryContestants()->find(contestantKey,(*countryToUpdate->getValue())
                ->getCountryContestants()->root)->getKey()->strength += change;
        /*--------------update in country teams and teams---------------------------*/
        for (int i = 0 ; i < NUM_OF_MAX_TEAMS ; i++) {
            int teamId_to_update = contestantInContestants->value->get_teamsIParticipate(i);
            if (teamId_to_update == -2) {
                continue;
            }
            Team_Key pastTeamKey = Team_Key(teamId_to_update);
            auto pastTeamToUpdate = teams->find(pastTeamKey, teams->root);
            //please notice that contestantKey still doesnt contain the new strength
            //this->remove_contestant_from_team(teamId_to_update, contestantId);
            pastTeamToUpdate->value->removeContestantFromTeam(contestantKey, false);
            Contestant_Key contestantKeyUpdated = *(contestantInContestants->getKey());
            //this->add_contestant_to_team(teamId_to_update, contestantId); //should work because uses contestants tree
            // which is updated
            pastTeamToUpdate->value->addContestantToATeam(contestantKeyUpdated,contestantInContestants->value
            , false);

            auto rootOfCountry = (*countryToUpdate->getValue())->getCountryTeams();
            rootOfCountry->find(pastTeamKey, rootOfCountry->root)->value->removeContestantFromTeam
            (contestantKey, false); //again contestantKey contain the old strength
            rootOfCountry->find(pastTeamKey, rootOfCountry->root)->value->addContestantToATeam(contestantKeyUpdated,contestantInContestants->value
                    , false);

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
    return output_t<int>((*countries->find(Country_Key(countryId),countries->root)->getValue())->getMedals());
}

output_t<int> Olympics::get_team_strength(int teamId){
    try {
        if (teamId <= 0) {
            return output_t<int>(StatusType::INVALID_INPUT);
        }
        auto node = this->teams->find(Team_Key(teamId),this->teams->root);
        if (node == nullptr) {
            return output_t<int>(StatusType::FAILURE);
        }
        auto team = this->teams->find(Team_Key(teamId),this->teams->root)->value;
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
    catch(...) {//std::bad_alloc& ba, remember to change it
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }

}
/*
void Olympics::calc_size_of_complete_tree(AvlTree<Contestant_Key, Contestant*>* team1_tree,AvlTree<Contestant_Key,
                                          Contestant*>::Node* team2_root, int* size) {
    if (team2_root == nullptr) {
        return;
    }
    calc_size_of_complete_tree(team1_tree, team2_root->right, size);
    if (team1_tree->find(*(team2_root->getKey()), team1_tree->root) != nullptr) {
        (*size)++;
    }
    calc_size_of_complete_tree(team1_tree, team2_root->left, size);

}
void Olympics::fill_array_of_repeated_contestants(AvlTree<Contestant_Key, Contestant*>* team1_tree,
                                                 AvlTree<Contestant_Key,
        Contestant*>::Node* team2_root, Contestant** array_obj, Contestant_Key* array_keys, int* size) {
    if (team2_root == nullptr) {
        return;
    }
    fill_array_of_repeated_contestants(team1_tree, team2_root->right, array_obj, array_keys, size);
    if (team1_tree->find(*(team2_root->getKey()), team1_tree->root) != nullptr) {
        array_obj[*size] = team2_root->value;
        array_keys[*size] = team2_root->key;
    }
    fill_array_of_repeated_contestants(team1_tree, team2_root->left, array_obj, array_keys, size);
}
*/

StatusType Olympics::unite_teams(int teamId1,int teamId2){
    try {
        if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) {
            return StatusType::INVALID_INPUT;
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
        int countryIdOf1 = teamToAddTo1->value->getCountryId();
        int countryIdOf2 = teamToAddTo2->value->getCountryId();
        Sport *sportOf1 = teamToAddTo1->value->getSport();
        Sport *sportOf2 = teamToAddTo2->value->getSport();
        if (countryIdOf1 != countryIdOf2 || *sportOf1 != *sportOf2) {
            return StatusType::FAILURE;
        }

        /*-----------------added today 5/3----------------------------*/
        /*auto tree_team_1 = isTeamOneFound->value->get_team_whole_contestants_by_id();
        auto team2_root = isTeamTwoFound->value->get_team_whole_contestants_by_id()->root;
        int num_of_nodes_in_complete_tree = 0;
        calc_size_of_complete_tree(tree_team_1, team2_root, &num_of_nodes_in_complete_tree );
        AvlTree<Contestant_Key, Contestant*>::createCompleteTree(num_of_nodes_in_complete_tree);
        Contestant** contestants_in_both_groups = new Contestant*[num_of_nodes_in_complete_tree];
        Contestant_Key* keys_in_both_groups = new Contestant_Key[num_of_nodes_in_complete_tree];
        int index = 0;
        fill_array_of_repeated_contestants(tree_team_1, team2_root, contestants_in_both_groups, keys_in_both_groups,
                                           &index);
*/

        /*-------------------------------------------------------------*/

        while(isTeamTwoFound->value->getNumParticipants()!=0){
            auto team2_min_node = isTeamTwoFound->value->get_team_whole_contestants_by_id()->findMin
                    (isTeamTwoFound->value->get_team_whole_contestants_by_id()->root);
            //Contestant* team2_min_contestant = *(team2_min_node->getValue());
            Contestant_Key team2_min_Key = *(team2_min_node->getKey());
            //if team2 contestnt does not exist already in team1, add him to team1
            if(isTeamOneFound->value->get_team_whole_contestants_by_id()->find(team2_min_Key,
                                                                                    isTeamOneFound->value->get_team_whole_contestants_by_id()->root)!=nullptr) { //changed here
                this->remove_contestant_from_team(teamId2, team2_min_Key.id);//added this line


            }
            else {
            this->remove_contestant_from_team(teamId2, team2_min_Key.id); //changed here from continue
            this->add_contestant_to_team(teamId1, team2_min_Key.id);
        }


        }
        this->remove_team(teamId2);
    }
    catch(...) {//std::bad_alloc& ba, remember to change it
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Olympics::play_match(int teamId1,int teamId2){
    try {
        if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) {
            return StatusType::INVALID_INPUT;
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
        int countryIdOf1 = teamToAddTo1->value->getCountryId();
        int countryIdOf2 = teamToAddTo2->value->getCountryId();
        Country_Key country_key1 = Country_Key(countryIdOf1);
        Country_Key country_key2 = Country_Key(countryIdOf2);
        auto country1_node = this->countries->find(country_key1,this->countries->root);
        auto country2_node = this->countries->find(country_key2,this->countries->root);
        assert(country1_node!=nullptr &&  country2_node!= nullptr);
        auto country1= country1_node->getValue();
        auto country2= country2_node->getValue();
        Sport *sportOf1 = teamToAddTo1->value->getSport();
        Sport *sportOf2 = teamToAddTo2->value->getSport();
        if (*sportOf1 != *sportOf2) {
            return StatusType::FAILURE;
        }
        int nikood_team_1=this->get_team_strength(teamId1).ans() + (*country1)->getMedals();
        int nikood_team_2=this->get_team_strength(teamId2).ans() + (*country2)->getMedals();
        if(nikood_team_1 == nikood_team_2){
            //if equal, dont do anything, but return success(ki ze teko)
            return StatusType::SUCCESS;
        }
        else{
            nikood_team_1 > nikood_team_2 ? (*country1)->IncMedalCountByOne() : (*country2)->IncMedalCountByOne();
            return StatusType::SUCCESS;
        }
    }
    catch(...) {//std::bad_alloc& ba, remember to change it
        return StatusType::ALLOCATION_ERROR;
    }

}

output_t<int> Olympics::austerity_measures(int teamId){
    if (teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Team_Key teamKey = Team_Key(teamId);
    auto is_team_found = teams->find(teamKey, teams->root);
    if (is_team_found == nullptr) {
        return output_t<int>(StatusType::FAILURE);
    }
    if (is_team_found->value->get_team_whole_contestants_by_id()->numOfNodes < 3) {
        return output_t<int>(StatusType::FAILURE);
    }
    int res = 0;
    try {
        res = is_team_found->value->get_optimalTeamStrength();
    }
    catch(...) {//std::bad_alloc& ba, remember to change it
        return StatusType::ALLOCATION_ERROR;
    }
    return output_t<int>(res);
}




