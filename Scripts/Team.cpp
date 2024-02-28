//
// Created by USER on 12/02/2024.
//

#include "Team.h"

Team::~Team() {
    delete team_whole_contestants_by_id; //destructorOfAvlTree?
    delete team_whole_contestants_by_strength;
    delete treeByIdBigVal;
    delete treeByIdMedVal;
    delete treeByIdSmallVal;
    delete treeByStrengthBigVal;
    delete treeByStrengthMedVal;
    delete treeByStrengthSmallVal;
    delete contestantWithMaxInTreeByIdBigVal;
    delete contestantWithMaxInTreeByIdMedVal;
    delete contestantWithMaxInTreeByIdSmallVal;
    delete contestantWithMinInTreeByIdBigVal;
    delete contestantWithMinInTreeByIdMedVal;
    delete contestantWithMinInTreeByIdSmallVal;

    team_whole_contestants_by_id = nullptr; //destructorOfAvlTree?
    team_whole_contestants_by_strength = nullptr;
    treeByIdBigVal = nullptr;
    treeByIdMedVal = nullptr;
    treeByIdSmallVal = nullptr;
    treeByStrengthBigVal = nullptr;
    treeByStrengthMedVal = nullptr;
    treeByStrengthSmallVal = nullptr;
}

Team::Team() {
    this->teamId = 0;
    this->numParticipants = 0;
    this->sport = static_cast<Sport>(TEAM_TYPE_INIT); //only for initialization
    this->myCountry = 0;
    for (int i = 0 ; i < 3 ; i++) {
        this->stateOfBalanceForAdd[i] = 0;
    }
    for (int i = 0 ; i < 3 ; i++) {
        this->stateOfBalanceForRemove[i] = 0;
    }
    this->team_whole_contestants_by_id = new AvlTree<Contestant_Key, Contestant>();
    this->team_whole_contestants_by_strength = new AvlTree<Contestant_Key, Contestant>();
    this->treeByIdBigVal = new AvlTree<Contestant_Key, Contestant>();
    this->treeByIdMedVal = new AvlTree<Contestant_Key, Contestant>();
    this->treeByIdSmallVal = new AvlTree<Contestant_Key, Contestant>();
    this->treeByStrengthBigVal = new AvlTree<Contestant_Key, Contestant>();
    this->treeByStrengthMedVal = new AvlTree<Contestant_Key, Contestant>();
    this->treeByStrengthSmallVal = new AvlTree<Contestant_Key, Contestant>();

    this->contestantWithMaxInTreeByIdBigVal = new Contestant(0, 0, 0, Sport::SPINNING,0);
    this->contestantWithMaxInTreeByIdMedVal= new Contestant(0, 0, 0, Sport::SPINNING,0);
    this->contestantWithMaxInTreeByIdSmallVal= new Contestant(0, 0, 0, Sport::SPINNING,0);
    this->contestantWithMinInTreeByIdBigVal = new Contestant(0, 0, 0, Sport::SPINNING,0);
    this->contestantWithMinInTreeByIdMedVal= new Contestant(0, 0, 0, Sport::SPINNING,0);
    this->contestantWithMinInTreeByIdSmallVal= new Contestant(0, 0, 0, Sport::SPINNING,0);

    this->maxInTreeByIdBigVal = Contestant_Key(0,0,false);
    this->maxInTreeByIdMedVal = Contestant_Key(0,0,false);
    this->maxInTreeByIdSmallVal = Contestant_Key(0,0,false);
    this->minInTreeByIdBigVal = Contestant_Key(0,0,false);
    this->minInTreeByIdMedVal = Contestant_Key(0,0,false);
    this->minInTreeByIdSmallVal = Contestant_Key(0,0,false);
    this->maxInTreeByStrengthSmallVal =Contestant_Key(0,0,true);
    this->maxInTreeByStrengthMedVal = Contestant_Key(0,0,true);
    this->maxInTreeByStrengthBigVal = Contestant_Key(0,0,true);
    this->optimalTeamStrength = 0;


}

Team::Team(int teamId, Sport sport, int numParticipants, int countryId) {
    this->teamId = teamId;
    this->sport = sport;
    this->numParticipants = numParticipants;
    this->myCountry = countryId;
    this->team_whole_contestants_by_id = new AvlTree<Contestant_Key, Contestant>();
    this->team_whole_contestants_by_strength = new AvlTree<Contestant_Key, Contestant>();
    this->treeByIdBigVal = new AvlTree<Contestant_Key, Contestant>();
    this->treeByIdMedVal = new AvlTree<Contestant_Key, Contestant>();
    this->treeByIdSmallVal = new AvlTree<Contestant_Key, Contestant>();
    this->treeByStrengthBigVal = new AvlTree<Contestant_Key, Contestant>();
    this->treeByStrengthMedVal = new AvlTree<Contestant_Key, Contestant>();
    this->treeByStrengthSmallVal = new AvlTree<Contestant_Key, Contestant>();
    if (numParticipants == 0) {
        for (int i = 0 ; i < 3 ; i++) {
            stateOfBalanceForAdd[i] = 0;
        }
    }
    if (numParticipants == 0) {
        for (int i = 0 ; i < 3 ; i++) {
            stateOfBalanceForRemove[i] = 0;
        }
    }
    this->contestantWithMaxInTreeByIdBigVal = new Contestant(0, 0, 0, Sport::SPINNING,0);
    this->contestantWithMaxInTreeByIdMedVal= new Contestant(0, 0, 0, Sport::SPINNING,0);
    this->contestantWithMaxInTreeByIdSmallVal= new Contestant(0, 0, 0, Sport::SPINNING,0);
    this->contestantWithMinInTreeByIdBigVal = new Contestant(0, 0, 0, Sport::SPINNING,0);
    this->contestantWithMinInTreeByIdMedVal= new Contestant(0, 0, 0, Sport::SPINNING,0);
    this->contestantWithMinInTreeByIdSmallVal= new Contestant(0, 0, 0, Sport::SPINNING,0);

    this->maxInTreeByIdBigVal = Contestant_Key(0,0,false);
    this->maxInTreeByIdMedVal = Contestant_Key(0,0,false);
    this->maxInTreeByIdSmallVal = Contestant_Key(0,0,false);
    this->minInTreeByIdBigVal = Contestant_Key(0,0,false);
    this->minInTreeByIdMedVal = Contestant_Key(0,0,false);
    this->minInTreeByIdSmallVal = Contestant_Key(0,0,false);

    this->maxInTreeByStrengthSmallVal = Contestant_Key(0,0,true);
    this->maxInTreeByStrengthMedVal = Contestant_Key(0,0,true);
    this->maxInTreeByStrengthBigVal = Contestant_Key(0,0,true);
    optimalTeamStrength = 0;

}

int Team::getCountryId() const{
    return this->myCountry;
}
Contestant_Key Team::get_maxInTreeByStrengthBigVal() {
    return maxInTreeByStrengthBigVal;
}
Contestant_Key Team::get_maxInTreeByStrengthMedVal() {
    return maxInTreeByStrengthMedVal;
}
Contestant_Key Team::get_maxInTreeByStrengthSmallVal() {
    return maxInTreeByStrengthSmallVal;
}
int Team::getStateOfBalanceForAdd(int index) {
    return stateOfBalanceForAdd[index];
}
int Team::get_optimalTeamStrength() const {
    return optimalTeamStrength;
}
void Team::set_optimalTeamStrength(int optimalVal) {
    this->optimalTeamStrength = optimalVal;
}
AvlTree<Contestant_Key, Contestant>* Team::get_treeByIdBigVal() {
    return this->treeByIdBigVal;
}
AvlTree<Contestant_Key, Contestant>* Team::get_treeByIdMedVal() {
    return this->treeByIdMedVal;
}
AvlTree<Contestant_Key, Contestant>* Team::get_treeByIdSmallVal() {
    return this->treeByIdSmallVal;
}


AvlTree<Contestant_Key, Contestant>* Team::get_treeByStrengthBigVal() {
    return this->treeByStrengthBigVal;
}
AvlTree<Contestant_Key, Contestant>* Team::get_treeByStrengthMedVal() {
    return this->treeByStrengthMedVal;
}
AvlTree<Contestant_Key, Contestant>* Team::get_treeByStrengthSmallVal() {
    return this->treeByStrengthSmallVal;
}

void Team::updateStateOfBalanceForAdd() {
    int numSmall = treeByIdSmallVal->numOfNodes;
    int numMed = treeByIdMedVal->numOfNodes;
    int numBig = treeByIdBigVal->numOfNodes;
    if (treeByIdSmallVal->numOfNodes - treeByIdMedVal->numOfNodes >= treeByIdSmallVal->numOfNodes -
                                                                     treeByIdBigVal->numOfNodes)
        stateOfBalanceForAdd[0] = treeByIdSmallVal->numOfNodes - treeByIdMedVal->numOfNodes;
    else {
        stateOfBalanceForAdd[0] = treeByIdSmallVal->numOfNodes - treeByIdBigVal->numOfNodes;
    }
    if (treeByIdMedVal->numOfNodes - treeByIdSmallVal->numOfNodes >= treeByIdMedVal->numOfNodes -
                                                                     treeByIdBigVal->numOfNodes) {
        stateOfBalanceForAdd[1] = treeByIdMedVal->numOfNodes - treeByIdSmallVal->numOfNodes;
    }
    else {
        stateOfBalanceForAdd[1] = treeByIdMedVal->numOfNodes - treeByIdBigVal->numOfNodes;
    }
    if (treeByIdBigVal->numOfNodes - treeByIdSmallVal->numOfNodes >= treeByIdBigVal->numOfNodes -
                                                                     treeByIdMedVal->numOfNodes) {
        stateOfBalanceForAdd[2] = treeByIdBigVal->numOfNodes - treeByIdSmallVal->numOfNodes;
    }
    else {
        stateOfBalanceForAdd[2] = treeByIdBigVal->numOfNodes - treeByIdMedVal->numOfNodes;
    }
    return;
}

void Team::makePlaceInTreeByIdBigValForAdd() {
    if (stateOfBalanceForAdd[1] != 1) {
        //donate the min from big to med
        auto NodeToDonate = treeByIdBigVal->find(minInTreeByIdBigVal, treeByIdBigVal->root);
        Contestant toDonate = *(NodeToDonate->getValue());
        treeByIdBigVal->remove(minInTreeByIdBigVal);
        Contestant_Key toRemoveStr = Contestant_Key(minInTreeByIdBigVal.id,minInTreeByIdBigVal.strength, true );
        Contestant_Key toRemoveId = Contestant_Key(minInTreeByIdBigVal.id,minInTreeByIdBigVal.strength, false);
        toDonate.set_is_by_strength_sorted(true);
        treeByStrengthBigVal->remove(toRemoveStr);
        toDonate.set_is_by_strength_sorted(false);
        treeByIdMedVal->insertAux(toRemoveId, toDonate);
        toDonate.set_is_by_strength_sorted(true);
        treeByStrengthMedVal->insertAux(toRemoveStr, toDonate);
        if (treeByIdBigVal->numOfNodes == 0) {
            this->maxInTreeByStrengthBigVal = Contestant_Key(0, 0, true);
            this->maxInTreeByIdBigVal = Contestant_Key(0, 0, false);
            this->minInTreeByIdBigVal = Contestant_Key(0, 0, false);
            updateStateOfBalanceForAdd();
        }
        else {
            updateTreeByStrengthBigValForAdd(); //this one also updates the stated array
        }
        updateTreeByStrengthMedValForAdd();

    }
    else {
        //donate the min from med to small
        //donate the min from big to med
        auto NodeToDonate = treeByIdMedVal->find(minInTreeByIdMedVal, treeByIdMedVal->root);
        Contestant toDonate = *(NodeToDonate->getValue());
        treeByIdMedVal->remove(minInTreeByIdMedVal);
        Contestant_Key removeStr = Contestant_Key(minInTreeByIdMedVal.id, minInTreeByIdMedVal.strength, true);
        Contestant_Key removeId = Contestant_Key(minInTreeByIdMedVal.id, minInTreeByIdMedVal.strength, false);
        treeByStrengthMedVal->remove(removeStr);
        treeByIdSmallVal->insertAux(removeId, toDonate);
        treeByStrengthSmallVal->insertAux(removeStr, toDonate);
        if (treeByIdMedVal->numOfNodes == 0) {
            this->maxInTreeByStrengthMedVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdMedVal =Contestant_Key(0, 0, false);
            this->minInTreeByIdMedVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForAdd();
        }
        else {
            updateTreeByStrengthMedValForAdd(); //this one also updates the stated array
        }
        updateTreeByStrengthSmallValForAdd();
        /*----now the next step, donate the min from big to med--------*/
        auto NodeToDonate1 = treeByIdBigVal->find(minInTreeByIdBigVal, treeByIdBigVal->root);
        Contestant toDonate1 = *(NodeToDonate1->getValue());
        Contestant_Key toRemoveStr1 = Contestant_Key(minInTreeByIdBigVal.id, minInTreeByIdBigVal.strength, true);
        Contestant_Key toRemoveId1 = Contestant_Key(minInTreeByIdBigVal.id, minInTreeByIdBigVal.strength, false);
        treeByIdBigVal->remove(toRemoveId1);
        treeByStrengthBigVal->remove(toRemoveStr1);
        treeByIdMedVal->insertAux(toRemoveId1, toDonate1);
        treeByStrengthMedVal->insertAux(toRemoveStr1, toDonate1);
        if (treeByIdBigVal->numOfNodes == 0) {
            this->maxInTreeByStrengthBigVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdBigVal =Contestant_Key(0, 0, false);
            this->minInTreeByIdBigVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForAdd();
        }
        else {
            updateTreeByStrengthBigValForAdd(); //this one also updates the stated array
        }
        updateTreeByStrengthMedValForAdd();
    }
}
void Team::makePlaceInTreeByIdMedValForAdd() {
    if (stateOfBalanceForAdd[2] != 1) {
        //donate the max from med tree to big tree
        auto NodeToDonate = treeByIdMedVal->find(maxInTreeByIdMedVal, treeByIdMedVal->root);
        Contestant toDonate = *(NodeToDonate->getValue()); //copyConstructor?
        treeByIdMedVal->remove(maxInTreeByIdMedVal);
        Contestant_Key toRemoveStr = Contestant_Key(maxInTreeByIdMedVal.id, maxInTreeByIdMedVal.strength, true);
        Contestant_Key toRemoveId = Contestant_Key(maxInTreeByIdMedVal.id, maxInTreeByIdMedVal.strength, false);
        treeByStrengthMedVal->remove(toRemoveStr);
        treeByIdBigVal->insertAux(toRemoveId, toDonate);//remmember to insert to both of the trees
        treeByStrengthBigVal->insertAux(toRemoveStr, toDonate);
        if (treeByIdMedVal->numOfNodes == 0) {
            this->maxInTreeByStrengthMedVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdMedVal =Contestant_Key(0, 0, false);
            this->minInTreeByIdMedVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForAdd();
        }
        else {
            updateTreeByStrengthMedValForAdd(); //this one also updates the stated array
        }
        updateTreeByStrengthBigValForAdd();
    }
    else {
        //donate the min from med to small
        auto NodeToDonate = treeByIdMedVal->find(minInTreeByIdMedVal, treeByIdMedVal->root);
        Contestant toDonate = *(NodeToDonate->getValue());
        treeByIdMedVal->remove(minInTreeByIdMedVal);
        Contestant_Key toRemoveId= Contestant_Key(minInTreeByIdMedVal.id, minInTreeByIdMedVal.strength, false);
        Contestant_Key toRemoveStr= Contestant_Key(minInTreeByIdMedVal.id, minInTreeByIdMedVal.strength, true);
        treeByStrengthMedVal->remove(toRemoveStr);
        treeByIdSmallVal->insertAux(toRemoveId, toDonate);
        treeByStrengthSmallVal->insertAux(toRemoveStr, toDonate);
        if (treeByIdMedVal->numOfNodes == 0) {
            this->maxInTreeByStrengthMedVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdMedVal =Contestant_Key(0, 0, false);
            this->minInTreeByIdMedVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForAdd();
        }
        else {
            updateTreeByStrengthMedValForAdd(); //this one also updates the stated array
        }
        updateTreeByStrengthSmallValForAdd();


    }
}
void Team::makePlaceInTreeByIdSmallValForAdd() {
    if (stateOfBalanceForAdd[1] != 1) {
        //delete the elem with max Id in smallTree and insert it to Med tree
        //update the states
        //update the max fiels in small tree, update the min field in med tree
        //update the max power in small tree, udate the max power field in mid tree
        auto NodeToDonate = treeByIdSmallVal->find(maxInTreeByIdSmallVal, treeByIdSmallVal->root);
        Contestant toDonate = *(NodeToDonate->getValue()); //copyConstructor?
        treeByIdSmallVal->remove(maxInTreeByIdSmallVal);
        Contestant_Key toRemoveStr = Contestant_Key(maxInTreeByIdSmallVal.id, maxInTreeByIdSmallVal.strength, true);
        Contestant_Key toRemoveId = Contestant_Key(maxInTreeByIdSmallVal.id, maxInTreeByIdSmallVal.strength, false);
        treeByStrengthSmallVal->remove(toRemoveStr); ////-----------------change it to removeWithRepetition
        treeByIdMedVal->insertAux(toRemoveId, toDonate);//remmember to insert to both of the trees
        treeByStrengthMedVal->insertAux(toRemoveStr, toDonate);
        if (treeByIdSmallVal->numOfNodes == 0) {
            this->maxInTreeByStrengthSmallVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdSmallVal =Contestant_Key(0, 0, false);
            this->minInTreeByIdSmallVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForAdd();
        }
        else {
            updateTreeByStrengthSmallValForAdd(); //this one also updates the stated array
        }
        updateTreeByStrengthMedValForAdd();
    }
    else { //if stateOfBalnce[1] == 1, Med must donate to Big. And Small must donate to Med.
        //ask from med to donate his maxId to big tree
        //ask from small to donatee his maxId to med tree
        //update states
        //update max and min fields Id of three trees
        //update max fields power of three trees
        auto NodeToMoveToBig = treeByIdMedVal->find(maxInTreeByIdMedVal,treeByIdMedVal->root);
        Contestant toMoveToBig = *(NodeToMoveToBig->getValue()); //copyConstructor?
        Contestant_Key toRemoveId = Contestant_Key(maxInTreeByIdMedVal.id, maxInTreeByIdMedVal.strength, false);
        Contestant_Key toRemoveStr = Contestant_Key(maxInTreeByIdMedVal.id, maxInTreeByIdMedVal.strength, true);
        treeByIdMedVal->remove(toRemoveId);
        treeByStrengthMedVal->remove(toRemoveStr);
        treeByIdBigVal->insertAux(toRemoveId, toMoveToBig);
        treeByStrengthBigVal->insertAux(toRemoveStr, toMoveToBig);
        if (treeByIdMedVal->numOfNodes == 0) {
            this->maxInTreeByStrengthMedVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdMedVal=Contestant_Key(0, 0, false);
            this->minInTreeByIdMedVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForAdd();
        }
        else {
            updateTreeByStrengthMedValForAdd();
        }
        updateTreeByStrengthBigValForAdd();
        //this one also updates the stated array
        //now donating from small to med(now must be state[1] != 1)
        auto NodeToMoveToMed = treeByIdSmallVal->find(maxInTreeByIdSmallVal, treeByIdSmallVal->root);
        Contestant_Key toMoveStr = Contestant_Key(maxInTreeByIdSmallVal.id, maxInTreeByIdSmallVal.strength, true);
        Contestant_Key toMoveId = Contestant_Key(maxInTreeByIdSmallVal.id, maxInTreeByIdSmallVal.strength, false);
        Contestant toMoveToMed = *(NodeToMoveToMed->getValue());
        treeByIdSmallVal->remove(toMoveId);
        treeByStrengthSmallVal->remove(toMoveStr);
        treeByIdMedVal->insertAux(toMoveId, toMoveToMed);
        treeByStrengthMedVal->insertAux(toMoveStr, toMoveToMed);
        if (treeByIdSmallVal->numOfNodes == 0) {
            this->maxInTreeByStrengthSmallVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdSmallVal =Contestant_Key(0, 0, false);
            this->minInTreeByIdSmallVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForAdd();
        }
        else {
            updateTreeByStrengthSmallValForAdd(); //this one also updates the stated array
        }//this one also updates the stated array
        updateTreeByStrengthMedValForAdd();

    }
}

void Team::updateTreeByStrengthSmallValForAdd() { //need to be here an update to the min max of by Id
    //and also for max By strength
    this->maxInTreeByStrengthSmallVal = (this->treeByStrengthSmallVal->findMax
            (this->treeByStrengthSmallVal->root))->key;
    this->maxInTreeByIdSmallVal = (this->treeByIdSmallVal->findMax(treeByIdSmallVal->root))->key;
    this->contestantWithMaxInTreeByIdSmallVal = (this->treeByIdSmallVal->findMax(treeByIdSmallVal->root))->getValue();
    this->minInTreeByIdSmallVal = (this->treeByIdSmallVal->findMin(treeByIdSmallVal->root))->key;
    this->contestantWithMinInTreeByIdSmallVal = (this->treeByIdSmallVal->findMin(treeByIdSmallVal->root))->getValue();
    updateStateOfBalanceForAdd();
}
void Team::updateTreeByStrengthMedValForAdd() { //need to be here an update to the min max of by Id
    //and also for max By strength
    this->maxInTreeByStrengthMedVal = (this->treeByStrengthMedVal->findMax
            (this->treeByStrengthMedVal->root))->key;
    this->maxInTreeByIdMedVal = (this->treeByIdMedVal->findMax(treeByIdMedVal->root))->key;
    this->contestantWithMaxInTreeByIdMedVal = (this->treeByIdMedVal->findMax(treeByIdMedVal->root))->getValue();
    this->minInTreeByIdMedVal = (this->treeByIdMedVal->findMin(treeByIdMedVal->root))->key;
    this->contestantWithMinInTreeByIdMedVal = (this->treeByIdMedVal->findMin(treeByIdMedVal->root))->getValue();
    updateStateOfBalanceForAdd();
}
void Team::updateTreeByStrengthBigValForAdd() { //need to be here an update to the min max of by Id
    //and also for max By strength
    this->maxInTreeByStrengthBigVal = (this->treeByStrengthBigVal->findMax
            (this->treeByStrengthBigVal->root))->key;
    this->maxInTreeByIdBigVal = (this->treeByIdBigVal->findMax(treeByIdBigVal->root))->key;
    this->contestantWithMaxInTreeByIdBigVal = (this->treeByIdBigVal->findMax(treeByIdBigVal->root))->getValue();
    this->minInTreeByIdBigVal = (this->treeByIdBigVal->findMin(treeByIdBigVal->root))->key;
    this->contestantWithMinInTreeByIdBigVal = (this->treeByIdBigVal->findMin(treeByIdBigVal->root))->getValue();
    updateStateOfBalanceForAdd();
}

void Team::addContestantToATeam(int contestantId, int countryId, int strength, Sport sport) {
    //Please Notice this one is added to the trees by strength
    Contestant toAdd = Contestant(contestantId, countryId, strength, sport, true);
    Contestant_Key toAddKeyStr = Contestant_Key(contestantId, strength, true);
    //Please notice this one is added to the trees by Id
    Contestant_Key toAddKeyId = Contestant_Key(contestantId, strength, false);
    team_whole_contestants_by_id->insertAux(toAddKeyId, toAdd); //important for austerity_measures
    team_whole_contestants_by_strength->insertAux(toAddKeyStr, toAdd);
    if (treeByIdSmallVal->numOfNodes == 0 && treeByIdMedVal->numOfNodes == 0 &&
        treeByIdBigVal->numOfNodes == 0) {
        treeByStrengthSmallVal->insertAux(toAddKeyStr, toAdd); //One Tree is the mirror of the other tree
        treeByIdSmallVal->insertAux(toAddKeyId, toAdd);
        updateTreeByStrengthSmallValForAdd();
        return;
    }
    if (contestantId < this->maxInTreeByIdSmallVal.id) {
        if (stateOfBalanceForAdd[0] < 1) {
            this->treeByStrengthSmallVal->insertAux(toAddKeyStr, toAdd);
            this->treeByIdSmallVal->insertAux(toAddKeyId, toAdd);
            updateTreeByStrengthSmallValForAdd();
        }
        else {
            makePlaceInTreeByIdSmallValForAdd();
            this->treeByStrengthSmallVal->insertAux(toAddKeyStr, toAdd);
            this->treeByIdSmallVal->insertAux(toAddKeyId, toAdd);
            updateTreeByStrengthSmallValForAdd();
        }
    }
    else if (contestantId < maxInTreeByIdMedVal.id) {
        if (stateOfBalanceForAdd[1] < 1) {
            this->treeByStrengthMedVal->insertAux(toAddKeyStr, toAdd);
            this->treeByIdMedVal->insertAux(toAddKeyId, toAdd);
            updateTreeByStrengthMedValForAdd();
        } else {
            makePlaceInTreeByIdMedValForAdd();
            this->treeByStrengthMedVal->insertAux(toAddKeyStr, toAdd);
            this->treeByIdMedVal->insertAux(toAddKeyId, toAdd);
            updateTreeByStrengthMedValForAdd();
        }
    }
    else { //which only left the case where strength is bigger that maxInTreeByStrengthBigVal
        if (stateOfBalanceForAdd[2] < 1) {
            this->treeByStrengthBigVal->insertAux(toAddKeyStr, toAdd);
            this->treeByIdBigVal->insertAux(toAddKeyId, toAdd);
            updateTreeByStrengthBigValForAdd();
        }
        else {
            makePlaceInTreeByIdBigValForAdd();
            this->treeByStrengthBigVal->insertAux(toAddKeyStr, toAdd);
            this->treeByIdBigVal->insertAux(toAddKeyId, toAdd);
            updateTreeByStrengthBigValForAdd();

        }
    }
}
AvlTree<Contestant_Key, Contestant>* Team::get_team_whole_contestants_by_id() {
    return this->team_whole_contestants_by_id;
}
AvlTree<Contestant_Key, Contestant>* Team::get_team_whole_contestants_by_strength() {
    return this->team_whole_contestants_by_strength;
}
/*
void Team::updateStateOfBalanceForRemove() {
    int numSmall = treeByIdSmallVal->numOfNodes;
    int numMed = treeByIdMedVal->numOfNodes;
    int numBig = treeByIdBigVal->numOfNodes;
    if (treeByIdSmallVal->numOfNodes - treeByIdMedVal->numOfNodes >= treeByIdSmallVal->numOfNodes -
                                                                     treeByIdBigVal->numOfNodes)
        stateOfBalanceForRemove[0] = treeByIdSmallVal->numOfNodes - treeByIdBigVal->numOfNodes;
    else {
        stateOfBalanceForRemove[0] = treeByIdSmallVal->numOfNodes - treeByIdMedVal->numOfNodes;
    }
    if (treeByIdMedVal->numOfNodes - treeByIdSmallVal->numOfNodes >= treeByIdMedVal->numOfNodes -
                                                                     treeByIdBigVal->numOfNodes) {
        stateOfBalanceForRemove[1] = treeByIdMedVal->numOfNodes - treeByIdBigVal->numOfNodes;
    }
    else {
        stateOfBalanceForRemove[1] = treeByIdMedVal->numOfNodes - treeByIdSmallVal->numOfNodes;
    }
    if (treeByIdBigVal->numOfNodes - treeByIdSmallVal->numOfNodes >= treeByIdBigVal->numOfNodes -
                                                                     treeByIdMedVal->numOfNodes) {
        stateOfBalanceForRemove[2] = treeByIdBigVal->numOfNodes - treeByIdMedVal->numOfNodes;
    }
    else {
        stateOfBalanceForRemove[2] = treeByIdBigVal->numOfNodes - treeByIdSmallVal->numOfNodes;
    }
    return;
}
void Team::updateTreeByStrengthSmallValForRemove() { //need to be here an update to the min max of by Id
    //and also for max By strength
    this->maxInTreeByStrengthSmallVal = (this->treeByStrengthSmallVal->findMax
            (this->treeByStrengthSmallVal->root))->key;
    this->maxInTreeByIdSmallVal = (this->treeByIdSmallVal->findMax(treeByIdSmallVal->root))->key;
    this->contestantWithMaxInTreeByIdSmallVal = (this->treeByIdSmallVal->findMax(treeByIdSmallVal->root))->getValue();
    this->minInTreeByIdSmallVal = (this->treeByIdSmallVal->findMin(treeByIdSmallVal->root))->key;
    this->contestantWithMinInTreeByIdSmallVal = (this->treeByIdSmallVal->findMin(treeByIdSmallVal->root))->getValue();
    updateStateOfBalanceForRemove();
}
void Team::updateTreeByStrengthMedValForRemove() { //need to be here an update to the min max of by Id
    //and also for max By strength
    this->maxInTreeByStrengthMedVal = (this->treeByStrengthMedVal->findMax
            (this->treeByStrengthMedVal->root))->key;
    this->maxInTreeByIdMedVal = (this->treeByIdMedVal->findMax(treeByIdMedVal->root))->key;
    this->contestantWithMaxInTreeByIdMedVal = (this->treeByIdMedVal->findMax(treeByIdMedVal->root))->getValue();
    this->minInTreeByIdMedVal = (this->treeByIdMedVal->findMin(treeByIdMedVal->root))->key;
    this->contestantWithMinInTreeByIdMedVal = (this->treeByIdMedVal->findMin(treeByIdMedVal->root))->getValue();
    updateStateOfBalanceForRemove();
}
void Team::updateTreeByStrengthBigValForRemove() { //need to be here an update to the min max of by Id
    //and also for max By strength
    this->maxInTreeByStrengthBigVal = (this->treeByStrengthBigVal->findMax
            (this->treeByStrengthBigVal->root))->key;
    this->maxInTreeByIdBigVal = (this->treeByIdBigVal->findMax(treeByIdBigVal->root))->key;
    this->contestantWithMaxInTreeByIdBigVal = (this->treeByIdBigVal->findMax(treeByIdBigVal->root))->getValue();
    this->minInTreeByIdBigVal = (this->treeByIdBigVal->findMin(treeByIdBigVal->root))->key;
    this->contestantWithMinInTreeByIdBigVal = (this->treeByIdBigVal->findMin(treeByIdBigVal->root))->getValue();
    updateStateOfBalanceForRemove();
}*/
/*
void Team::removeContestantFromTeam(Contestant const& toRemove) {
    Contestant toRemoveId = toRemove;
    toRemoveId.set_is_by_strength_sorted(true);
    Contestant toRemoveStrength = toRemoveId;
    toRemoveId.set_is_by_strength_sorted(false);
    if (toRemoveId.get_contestantId() <= this->maxInTreeByIdSmallVal) {
        if (stateOfBalanceForRemove[0] > -1) { //meaning if we can remove from the small tree by Id
            this->treeByStrengthSmallVal->remove(toRemoveStrength);
            this->treeByIdSmallVal->remove(toRemoveId);
            updateTreeByStrengthSmallValForRemove();
        }
        else {
            makePlaceInTreeByIdSmallValForRemove();
            this->treeByStrengthSmallVal->remove(toRemoveStrength);
            this->treeByIdSmallVal->remove(toRemoveId);
            updateTreeByStrengthSmallValForRemove();
        }
    }
    else if (toRemove.get_contestantId() <= maxInTreeByIdMedVal) {
        if (stateOfBalanceForRemove[1] > -1) {
            this->treeByStrengthMedVal->remove(toRemoveStrength);
            this->treeByIdMedVal->remove(toRemoveId);
            updateTreeByStrengthMedValForRemove();
        } else {
            makePlaceInTreeByIdMedValForRemove();
            this->treeByStrengthMedVal->remove(toRemoveStrength);
            this->treeByIdMedVal->remove(toRemoveId);
            updateTreeByStrengthMedValForRemove();
        }
    }
    else { //which only left the case where id is bigger that maxInTreeByStrengthMedVal, therefore it must be in the
        // Big tree
        if (stateOfBalanceForAdd[2] > -1) {
            this->treeByStrengthBigVal->remove(toRemoveStrength);
            this->treeByIdBigVal->remove(toRemoveId);
            updateTreeByStrengthBigValForRemove();
        }
        else {
            makePlaceInTreeByIdBigValForRemove();
            this->treeByStrengthBigVal->remove(toRemoveStrength);
            this->treeByIdBigVal->remove(toRemoveId);
            updateTreeByStrengthBigValForRemove();

        }
    }
}
void Team::makePlaceInTreeByIdBigValForRemove() {

}
void Team::makePlaceInTreeByIdMedValForRemove() {

}
void Team::makePlaceInTreeByIdSmallValForRemove() {

}*/
/*
void Team::updateOptimalTeamStrength() {
    if (team_whole_contestants_by_id->numOfNodes == 0) {
        optimalTeamStrength = 0;
    } else {
        int counter = 0;
        auto minNodeToDelete = team_whole_contestants_by_strength->findMin
                    (team_whole_contestants_by_strength->root);
        Contestant copyOfFirstDeleted = *(minNodeToDelete->getValue());
        counter++;
        }
    }
}*/