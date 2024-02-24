//
// Created by USER on 12/02/2024.
//

#include "Team.h"


Team::Team() {
    this->teamId = 0;
    this->numParticipants = 0;
    this->sport = Sport::BOULDERING; //only for initialization
    this->myCountry = 0;
    for (int i = 0 ; i < 3 ; i++) {
        this->stateOfBalance[i] = 0;
    }
    this->treeByIdBigVal = new AvlTree<int, Contestant>();
    this->treeByIdMedVal = new AvlTree<int, Contestant>();
    this->treeByIdSmallVal = new AvlTree<int, Contestant>();
    this->treeByStrengthBigVal = new AvlTree<int, Contestant>();
    this->treeByStrengthMedVal = new AvlTree<int, Contestant>();
    this->treeByStrengthSmallVal = new AvlTree<int, Contestant>();

    this->maxInTreeByIdBigVal = 0;
    this->maxInTreeByIdMedVal = 0;
    this->maxInTreeByIdSmallVal = 0;
    this->minInTreeByIdBigVal = 0;
    this->minInTreeByIdMedVal = 0;
    this->minInTreeByIdSmallVal = 0;

    this->maxInTreeByStrengthSmallVal = 0;
    this->maxInTreeByStrengthMedVal = 0;
    this->maxInTreeByStrengthBigVal = 0;


}

Team::Team(int teamId, Sport sport, int numParticipants, int countryId) {
    this->teamId = teamId;
    this->sport = sport;
    this->numParticipants = numParticipants;
    this->myCountry = countryId;
    this->treeByIdBigVal = new AvlTree<int, Contestant>();
    this->treeByIdMedVal = new AvlTree<int, Contestant>();
    this->treeByIdSmallVal = new AvlTree<int, Contestant>();
    this->treeByStrengthBigVal = new AvlTree<int, Contestant>();
    this->treeByStrengthMedVal = new AvlTree<int, Contestant>();
    this->treeByStrengthSmallVal = new AvlTree<int, Contestant>();
    if (numParticipants == 0 ) {
        for (int i = 0 ; i < 3 ; i++) {
            stateOfBalance[i] = 0;
        }
    }
    this->maxInTreeByIdBigVal = 0;
    this->maxInTreeByIdMedVal = 0;
    this->maxInTreeByIdSmallVal = 0;
    this->minInTreeByIdBigVal = 0;
    this->minInTreeByIdMedVal = 0;
    this->minInTreeByIdSmallVal = 0;

    this->maxInTreeByStrengthSmallVal = 0;
    this->maxInTreeByStrengthMedVal = 0;
    this->maxInTreeByStrengthBigVal = 0;


}

int Team::getCountryId() const{
    return this->myCountry;
}
int Team::get_maxInTreeByStrengthBigVal() {
    return maxInTreeByStrengthBigVal;
}
int Team::get_maxInTreeByStrengthMedVal() {
    return maxInTreeByStrengthMedVal;
}
int Team::get_maxInTreeByStrengthSmallVal() {
    return maxInTreeByStrengthSmallVal;
}
int Team::getStateOfBalance(int index) {
    return stateOfBalance[index];
}
AvlTree<int, Contestant>* Team::get_treeByIdBigVal() {
    return this->treeByIdBigVal;
}
AvlTree<int, Contestant>* Team::get_treeByIdMedVal() {
    return this->treeByIdMedVal;
}
AvlTree<int, Contestant>* Team::get_treeByIdSmallVal() {
    return this->treeByIdSmallVal;
}


AvlTree<int, Contestant>* Team::get_treeByStrengthBigVal() {
    return this->treeByStrengthBigVal;
}
AvlTree<int, Contestant>* Team::get_treeByStrengthMedVal() {
    return this->treeByStrengthMedVal;
}
AvlTree<int, Contestant>* Team::get_treeByStrengthSmallVal() {
    return this->treeByStrengthSmallVal;
}

void Team::updateStateOfBalance() {
    int numSmall = treeByIdSmallVal->numOfNodes;
    int numMed = treeByIdMedVal->numOfNodes;
    int numBig = treeByIdBigVal->numOfNodes;
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
/*
void makePlaceInTreeByIdBigVal() {

}
void makePlaceInTreeByIdMedVal() {

}*/
void Team::makePlaceInTreeByIdSmallVal() {
    if (stateOfBalance[1] != 1) {
        //delete the elem with max Id in smallTree and insert it to Med tree
        //update the states
        //update the max fiels in small tree, update the min field in med tree
        //update the max power in small tree, udate the max power field in mid tree
        auto NodeToDonate = treeByIdSmallVal->find(maxInTreeByIdSmallVal, treeByIdSmallVal->root);
        Contestant toDonate = *(NodeToDonate->getValue()); //copyConstructor?
        treeByIdSmallVal->remove(maxInTreeByIdSmallVal);
        treeByStrengthSmallVal->remove(toDonate.get_strength());
        treeByIdMedVal->insertAux(toDonate.get_contestantId(), toDonate);//remmember to insert to both of the trees
        toDonate.set_is_by_strength_sorted(true);
        treeByStrengthMedVal->insertAux(toDonate.get_strength(), toDonate);
        if (treeByIdSmallVal->numOfNodes == 0) {
            this->maxInTreeByStrengthSmallVal = 0;
            this->maxInTreeByIdSmallVal = 0;
            this->minInTreeByIdSmallVal = 0;
            updateStateOfBalance();
        }
        else {
            updateTreeByStrengthSmallVal(); //this one also updates the stated array
        }
        updateTreeByStrengthMedVal();
    }
    else { //if stateOfBalnce[1] == 1, Med must donate to Big. And Small must donate to Med.
        //ask from mid to donate his maxId to big tree
        //ask from small to donatee his maxId to med tree
        //update states
        //update max and min fields Id of three trees
        //update max fields power of three trees
        auto NodeToMoveToBig = treeByIdMedVal->find(maxInTreeByIdMedVal,treeByIdMedVal->root);
        Contestant toMoveToBig = *(NodeToMoveToBig->getValue()); //copyConstructor?
        treeByIdMedVal->remove(maxInTreeByIdMedVal);
        treeByStrengthMedVal->remove(toMoveToBig.get_strength());
        treeByIdBigVal->insertAux(toMoveToBig.get_contestantId(), toMoveToBig);
        toMoveToBig.set_is_by_strength_sorted(true);
        treeByStrengthBigVal->insertAux(toMoveToBig.get_strength(), toMoveToBig);
        if (treeByIdMedVal->numOfNodes == 0) {
            this->maxInTreeByStrengthMedVal = 0;
            this->maxInTreeByIdMedVal = 0;
            this->minInTreeByIdMedVal = 0;
            updateStateOfBalance();
        }
        else {
            updateTreeByStrengthMedVal();
        }
        updateTreeByStrengthBigVal();
        //this one also updates the stated array
        //now donating from small to med(now must be state[1] != 1)
        auto NodeToMoveToMed = treeByIdSmallVal->find(maxInTreeByIdSmallVal, treeByIdSmallVal->root);
        Contestant toMoveToMed = *(NodeToMoveToMed->getValue());
        treeByIdSmallVal->remove(toMoveToMed.get_contestantId());
        treeByStrengthSmallVal->remove(toMoveToMed.get_strength());
        treeByIdMedVal->insertAux(toMoveToMed.get_contestantId(), toMoveToMed);
        toMoveToMed.set_is_by_strength_sorted(true);
        treeByStrengthMedVal->insertAux(toMoveToMed.get_strength(), toMoveToMed);
        if (treeByIdSmallVal->numOfNodes == 0) {
            this->maxInTreeByStrengthSmallVal = 0;
            this->maxInTreeByIdSmallVal = 0;
            this->minInTreeByIdSmallVal = 0;
            updateStateOfBalance();
        }
        else {
            updateTreeByStrengthSmallVal(); //this one also updates the stated array
        }//this one also updates the stated array
        updateTreeByStrengthMedVal();

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
void Team::updateTreeByStrengthMedVal() { //need to be here an update to the min max of by Id
    //and also for max By strength
    this->maxInTreeByStrengthMedVal = (this->treeByStrengthMedVal->findMax
            (this->treeByStrengthMedVal->root))->key;
    this->maxInTreeByIdMedVal = (this->treeByIdMedVal->findMax(treeByIdMedVal->root))->key;
    this->minInTreeByIdMedVal = (this->treeByIdMedVal->findMin(treeByIdMedVal->root))->key;
    updateStateOfBalance();
}
void Team::updateTreeByStrengthBigVal() { //need to be here an update to the min max of by Id
    //and also for max By strength
    this->maxInTreeByStrengthBigVal = (this->treeByStrengthBigVal->findMax
            (this->treeByStrengthBigVal->root))->key;
    this->maxInTreeByIdBigVal = (this->treeByIdBigVal->findMax(treeByIdBigVal->root))->key;
    this->minInTreeByIdBigVal = (this->treeByIdBigVal->findMin(treeByIdBigVal->root))->key;
    updateStateOfBalance();
}
/*
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
}*/