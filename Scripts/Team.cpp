//
// Created by USER on 12/02/2024.
//

#include "Team.h"

Team::Team() {
    this->teamId = 0;
    this->numParticipants = 0;
    this->sport = Sport::BOULDERING;
    this->myCountry = 0;
    for (int i = 0 ; i < 3 ; i++) {
        stateOfBalance[i] = 0;
    }

}

Team::Team(int teamId, Sport sport, int numParticipants, int countryId) {
    this->teamId = teamId;
    this->sport = Sport::BOULDERING;
    this->numParticipants = numParticipants;
    this->myCountry = countryId;
    if (numParticipants == 0 ) {
        for (int i = 0 ; i < 3 ; i++) {
            stateOfBalance[i] = 0;
        }
    }


}

int Team::getCountryId() const{
    return this->myCountry;
}

void Team::updateStateOfBalance() {
    if (treeByStrengthSmallVal->numOfNodes - treeByStrengthMedVal->numOfNodes >= treeByStrengthSmallVal->numOfNodes -
    treeByStrengthBigVal->numOfNodes)
        stateOfBalance[0] = treeByStrengthSmallVal->numOfNodes - treeByStrengthMedVal->numOfNodes;
    else {
        stateOfBalance[0] = treeByStrengthSmallVal->numOfNodes - treeByStrengthBigVal->numOfNodes;
    }
    if (treeByStrengthMedVal->numOfNodes - treeByStrengthSmallVal->numOfNodes >= treeByStrengthMedVal->numOfNodes -
    treeByIdBigVal->numOfNodes) {
        stateOfBalance[1] = treeByStrengthMedVal->numOfNodes - treeByStrengthSmallVal->numOfNodes;
    }
    else {
        stateOfBalance[1] = treeByStrengthMedVal->numOfNodes - treeByIdBigVal->numOfNodes;
    }
    if (treeByStrengthBigVal->numOfNodes - treeByStrengthSmallVal->numOfNodes >= treeByStrengthBigVal->numOfNodes -
    treeByStrengthMedVal->numOfNodes) {
        stateOfBalance[2] = treeByStrengthBigVal->numOfNodes - treeByStrengthSmallVal->numOfNodes;
    }
    else {
        stateOfBalance[2] = treeByStrengthBigVal->numOfNodes - treeByStrengthMedVal->numOfNodes;
    }
    return;
}
void makePlaceInTreeByStrengthBigVal() {

}
void makePlaceInTreeByStrengthMedVal() {

}
void makePlaceInTreeByStrengthSmallVal() {

}

void Team::addContestant(int contestantId, int countryId, int strength, Sport sport) {
    Contestant toAdd = Contestant(contestantId, countryId, strength, sport, true);
    if (treeByStrengthSmallVal->numOfNodes == 0 && treeByStrengthMedVal->numOfNodes == 0 &&
    treeByStrengthBigVal->numOfNodes == 0) {
        treeByStrengthSmallVal->insertAux(strength, toAdd);
        return;
    }
    if (strength < this->maxInTreeByStrengthSmallVal) {
        if (stateOfBalance[0] < 1) {
            this->treeByStrengthSmallVal->insertAux(strength, toAdd);
        }
        else {
            makePlaceInTreeByStrengthSmallVal();
            this->treeByStrengthSmallVal->insertAux(strength, toAdd);
            //to_do : add here update for max field
        }
    }
}