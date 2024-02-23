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
    if (treeByIdSmallVal->numOfNodes - treeByIdMedVal->numOfNodes >= treeByIdSmallVal->numOfNodes -
                                                                                 treeByIdBigVal->numOfNodes)
        stateOfBalance[0] = treeByIdSmallVal->numOfNodes - treeByIdMedVal->numOfNodes;
    else {
        stateOfBalance[0] = treeByIdSmallVal->numOfNodes - treeByIdBigVal->numOfNodes;
    }
    if (treeByIdMedVal->numOfNodes - treeByIdSmallVal->numOfNodes >= treeByIdMedVal->numOfNodes -
                                                                                 treeByIdBigVal->numOfNodes) {
        stateOfBalance[1] = treeByIdMedVal->numOfNodes - treeByIdSmallVal->numOfNodes;
    }
    else {
        stateOfBalance[1] = treeByIdMedVal->numOfNodes - treeByIdBigVal->numOfNodes;
    }
    if (treeByIdBigVal->numOfNodes - treeByIdSmallVal->numOfNodes >= treeByIdBigVal->numOfNodes -
                                                                                 treeByIdMedVal->numOfNodes) {
        stateOfBalance[2] = treeByIdBigVal->numOfNodes - treeByIdSmallVal->numOfNodes;
    }
    else {
        stateOfBalance[2] = treeByIdBigVal->numOfNodes - treeByIdMedVal->numOfNodes;
    }
    return;
}
void makePlaceInTreeByIdBigVal() {

}
void makePlaceInTreeByIdMedVal() {

}
void Team::makePlaceInTreeByIdSmallVal() {
    if (stateOfBalance[1] != 1) {
        //delete the elem with max Id in smallTree and insert it to Med tree
        //update the states
        //update the max fiels in small tree, update the min field in med tree
        //update the max power in small tree, udate the max power field in mid tree
        auto NodeToDonate = treeByIdSmallVal->find(maxInTreeByIdSmallVal, treeByIdSmallVal->root);
        Contestant toDonate = *(NodeToDonate->getValue());
        assert(treeByIdSmallVal->remove(maxInTreeByIdSmallVal) != nullptr);


    }
    else {
        //ask from mid to donate his maxId to big tree
        //ask from small to donatee his maxId to med tree
        //update states
        //update max and min fields Id of three trees
        //update max fields power of three trees
    }
}
void Team::updateTreeByStrengthSmallVal() { //need to be here an update to the min max of by Id
    //and also for max By strength
    this->maxInTreeByStrengthSmallVal = (this->treeByStrengthSmallVal->findMax
            (this->treeByStrengthSmallVal->root))->key;
    this->maxInTreeByIdSmallVal = (this->treeByIdSmallVal->findMax(treeByIdSmallVal->root))->key;
    this->minInTreeByIdSmallVal = (this->treeByIdSmallVal->findMin(treeByIdSmallVal->root))->key;
    updateStateOfBalance();
}

void Team::addContestant(int contestantId, int countryId, int strength, Sport sport) {
    //Please Notice this one is added to the trees by strength
    Contestant toAdd = Contestant(contestantId, countryId, strength, sport, true);
    //Please notice this one is added to the trees by Id
    Contestant toAddId = Contestant(contestantId, countryId, strength, sport, false);
    if (treeByIdSmallVal->numOfNodes == 0 && treeByIdMedVal->numOfNodes == 0 &&
        treeByIdBigVal->numOfNodes == 0) {
        treeByStrengthSmallVal->insertAux(strength, toAdd); //One Tree is the mirror of the other tree
        treeByIdSmallVal->insertAux(contestantId, toAddId);
        updateTreeByStrengthSmallVal();
        return;
    }
    if (contestantId < this->maxInTreeByIdSmallVal) {
        if (stateOfBalance[0] < 1) {
            this->treeByStrengthSmallVal->insertAux(strength, toAdd);
            this->treeByIdSmallVal->insertAux(contestantId, toAddId);
            updateTreeByStrengthSmallVal();
        }
        else {
            makePlaceInTreeByIdSmallVal();
            this->treeByStrengthSmallVal->insertAux(strength, toAdd);
            this->treeByIdSmallVal->insertAux(contestantId, toAddId);
            updateTreeByStrengthSmallVal();
        }
    }
    else if (this->maxInTreeByIdSmallVal <= contestantId &&
             minInTreeByIdMedVal >= contestantId) {
        if (treeByIdMedVal->numOfNodes >= treeByIdSmallVal->numOfNodes) {
            if (stateOfBalance[0] < 1) {
                this->treeByStrengthSmallVal->insertAux(strength, toAdd);
                this->treeByIdSmallVal->insertAux(contestantId, toAddId);
                updateTreeByStrengthSmallVal();
            }
            else {
                makePlaceInTreeByIdSmallVal();
                this->treeByStrengthSmallVal->insertAux(strength, toAdd);
                this->treeByIdSmallVal->insertAux(contestantId, toAddId);
                updateTreeByStrengthSmallVal();
            }
        }
        else {
            if (stateOfBalance[1] < 1) {
                this->treeByStrengthMedVal->insertAux(strength, toAdd);
                this->treeByIdMedVal->insertAux(contestantId, toAddId);
                updateTreeByStrengthMedVal();
            }
            else {
                makePlaceInTreeByIdMedVal();
                this->treeByStrengthMedVal->insertAux(strength, toAdd);
                this->treeByIdMedVal->insertAux(contestantId, toAddId);
                updateTreeByStrengthMedVal();
            }
        }
    }
    else if (minInTreeByIdMedVal <= contestantId && contestantId <= maxInTreeByIdMedVal) {
        if (stateOfBalance[1] < 1) {
            this->treeByStrengthMedVal->insertAux(strength, toAdd);
            this->treeByIdMedVal->insertAux(contestantId, toAddId);
            updateTreeByStrengthMedVal();
        }
        else {
            makePlaceInTreeByIdMedVal();
            this->treeByStrengthMedVal->insertAux(strength, toAdd);
            this->treeByIdMedVal->insertAux(contestantId, toAddId);
            updateTreeByStrengthMedVal();

        }
    }
    else if ( maxInTreeByIdMedVal <= contestantId  && contestantId <= minInTreeByIdBigVal) {
        if (treeByIdMedVal->numOfNodes >= treeByIdBigVal->numOfNodes) {
            if (stateOfBalance[2] < 1) {
                this->treeByStrengthBigVal->insertAux(strength, toAdd);
                this->treeByIdBigVal->insertAux(contestantId, toAddId);
                updateTreeByStrengthBigVal();
            }
            else {
                makePlaceInTreeByIdBigVal();
                this->treeByStrengthBigVal->insertAux(strength, toAdd);
                this->treeByIdBigVal->insertAux(contestantId, toAddId);
                updateTreeByStrengthBigVal();
            }
        }
        else {
            if (stateOfBalance[1] < 1) {
                this->treeByStrengthMedVal->insertAux(strength, toAdd);
                this->treeByIdMedVal->insertAux(contestantId, toAddId);
                updateTreeByStrengthBigVal();
            }
            else {
                makePlaceInTreeByIdBigVal();
                this->treeByStrengthBigVal->insertAux(strength, toAdd);
                this->treeByIdBigVal->insertAux(contestantId, toAddId);
                updateTreeByStrengthBigVal();
            }
        }
    }
    else { //which only left the case where strength is bigger that maxInTreeByStrengthBigVal
        if (stateOfBalance[2] < 1) {
            this->treeByStrengthBigVal->insertAux(strength, toAdd);
            this->treeByIdBigVal->insertAux(contestantId, toAddId);
            updateTreeByStrengthBigVal();
        }
        else {
            makePlaceInTreeByIdBigVal();
            this->treeByStrengthBigVal->insertAux(strength, toAdd);
            this->treeByIdBigVal->insertAux(contestantId, toAddId);
            updateTreeByStrengthBigVal();

        }
    }
}