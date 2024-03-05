//
// Created by maaya on 19/02/2024.
//

#include "Country.h"

Country::Country(int countryId, int medals) {
    this->countryId = countryId;
    this->medals = medals;
    this->country_contestants = new AvlTree<Contestant_Key, Contestant*>();
    this->country_teams = new AvlTree<Team_Key, Team*>();
}


AvlTree<Contestant_Key, Contestant*>* Country::getCountryContestants() {
    return this->country_contestants;
}

AvlTree<Team_Key, Team*>* Country::getCountryTeams() {
    return this->country_teams;
}
int Country:: getMedals(){
    return  this->medals;
}
void Country::IncMedalCountByOne(){
    this->medals += 1;
}

Country::~Country() {
    AvlTree<Contestant_Key,Contestant*>::destroy_the_tree_and_values(this->country_contestants->root);
    delete this->country_contestants;
    this->country_contestants=nullptr;
    Country::DestroyTreeOfTeams(this->country_teams->root);
    delete this->country_teams;
    this->country_teams=nullptr;
}

void Country::DestroyTreeOfTeams(typename AvlTree<Team_Key, Team *>:: Node* root) {

    if(root==nullptr){
        return;
    }
    if(root->left!=nullptr) {
        DestroyTreeOfTeams(root->left);
    }
    if(root->right!=nullptr) {
        DestroyTreeOfTeams(root->right);
    }
    Team* team_to_delete = root->value;
    delete team_to_delete;

}
