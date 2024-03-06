//
// Created by USER on 12/02/2024.
//

#include "Team.h"

Team::~Team() {
    AvlTree<Contestant_Key,Contestant*>::destroy_the_tree_and_values( team_whole_contestants_by_id->root);
    //destructorOfAvlTree?
    AvlTree<Contestant_Key,Contestant*>::destroy_the_tree_and_values(team_whole_contestants_by_strength->root);
    AvlTree<Contestant_Key,Contestant*>::destroy_the_tree_and_values( treeByIdBigVal->root);
    AvlTree<Contestant_Key,Contestant*>::destroy_the_tree_and_values( treeByIdMedVal->root);
    AvlTree<Contestant_Key,Contestant*>::destroy_the_tree_and_values(treeByIdSmallVal->root);
    AvlTree<Contestant_Key,Contestant*>::destroy_the_tree_and_values(treeByStrengthBigVal->root);
    AvlTree<Contestant_Key,Contestant*>::destroy_the_tree_and_values(treeByStrengthMedVal->root);
    AvlTree<Contestant_Key,Contestant*>::destroy_the_tree_and_values(treeByStrengthSmallVal->root);
    delete team_whole_contestants_by_id;
    delete team_whole_contestants_by_strength;
    delete treeByIdBigVal;
    delete treeByIdMedVal;
    delete treeByIdSmallVal;
    delete treeByStrengthBigVal;
    delete treeByStrengthMedVal;
    delete treeByStrengthSmallVal;
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
    this->team_whole_contestants_by_id = new AvlTree<Contestant_Key, Contestant*>();
    this->team_whole_contestants_by_strength = new AvlTree<Contestant_Key, Contestant*>();
    this->treeByIdBigVal = new AvlTree<Contestant_Key, Contestant*>();
    this->treeByIdMedVal = new AvlTree<Contestant_Key, Contestant*>();
    this->treeByIdSmallVal = new AvlTree<Contestant_Key, Contestant*>();
    this->treeByStrengthBigVal = new AvlTree<Contestant_Key, Contestant*>();
    this->treeByStrengthMedVal = new AvlTree<Contestant_Key, Contestant*>();
    this->treeByStrengthSmallVal = new AvlTree<Contestant_Key, Contestant*>();

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

Team::Team(int teamId, Sport sport, int countryId) {
    this->teamId = teamId;
    this->sport = sport;
    this->numParticipants = 0;
    this->myCountry = countryId;
    this->team_whole_contestants_by_id = new AvlTree<Contestant_Key, Contestant*>();
    this->team_whole_contestants_by_strength = new AvlTree<Contestant_Key, Contestant*>();
    this->treeByIdBigVal = new AvlTree<Contestant_Key, Contestant*>();
    this->treeByIdMedVal = new AvlTree<Contestant_Key, Contestant*>();
    this->treeByIdSmallVal = new AvlTree<Contestant_Key, Contestant*>();
    this->treeByStrengthBigVal = new AvlTree<Contestant_Key, Contestant*>();
    this->treeByStrengthMedVal = new AvlTree<Contestant_Key, Contestant*>();
    this->treeByStrengthSmallVal = new AvlTree<Contestant_Key, Contestant*>();
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
int Team::getStateOfBalanceForRemove(int index) {
    return this->stateOfBalanceForRemove[index];
}


int Team::getCountryId() const{
    return this->myCountry;
}
Sport* Team::getSport(){
    return &(this->sport);
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
AvlTree<Contestant_Key, Contestant*>* Team::get_treeByIdBigVal() {
    return this->treeByIdBigVal;
}
AvlTree<Contestant_Key, Contestant*>* Team::get_treeByIdMedVal() {
    return this->treeByIdMedVal;
}
AvlTree<Contestant_Key, Contestant*>* Team::get_treeByIdSmallVal() {
    return this->treeByIdSmallVal;
}


AvlTree<Contestant_Key, Contestant*>* Team::get_treeByStrengthBigVal() {
    return this->treeByStrengthBigVal;
}
AvlTree<Contestant_Key, Contestant*>* Team::get_treeByStrengthMedVal() {
    return this->treeByStrengthMedVal;
}
AvlTree<Contestant_Key, Contestant*>* Team::get_treeByStrengthSmallVal() {
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
        Contestant* toDonate = *(NodeToDonate->getValue());
        treeByIdBigVal->remove(minInTreeByIdBigVal);
        Contestant_Key toRemoveStr = Contestant_Key(minInTreeByIdBigVal.id,minInTreeByIdBigVal.strength, true );
        Contestant_Key toRemoveId = Contestant_Key(minInTreeByIdBigVal.id,minInTreeByIdBigVal.strength, false);
        toDonate->set_is_by_strength_sorted(true);
        Contestant* toDonateStr = treeByStrengthBigVal->find(toRemoveStr,treeByStrengthBigVal->root)->value;
        treeByStrengthBigVal->remove(toRemoveStr);
        toDonate->set_is_by_strength_sorted(false);
        treeByIdMedVal->insertAux(toRemoveId, toDonate);
        toDonate->set_is_by_strength_sorted(true);
        treeByStrengthMedVal->insertAux(toRemoveStr, toDonateStr);
        if (treeByIdBigVal->numOfNodes == 0) {
            this->maxInTreeByStrengthBigVal = Contestant_Key(0, 0, true);
            this->maxInTreeByIdBigVal = Contestant_Key(0, 0, false);
            this->minInTreeByIdBigVal = Contestant_Key(0, 0, false);
            updateStateOfBalanceForAdd();
            updateStateOfBalanceForRemove();
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
        Contestant* toDonate = *(NodeToDonate->getValue());
        treeByIdMedVal->remove(minInTreeByIdMedVal);
        Contestant_Key removeStr = Contestant_Key(minInTreeByIdMedVal.id, minInTreeByIdMedVal.strength, true);
        Contestant_Key removeId = Contestant_Key(minInTreeByIdMedVal.id, minInTreeByIdMedVal.strength, false);
        Contestant* toDonateStr = treeByStrengthMedVal->find(removeStr,treeByStrengthMedVal->root)->value;
        treeByStrengthMedVal->remove(removeStr);
        treeByIdSmallVal->insertAux(removeId, toDonate);
        treeByStrengthSmallVal->insertAux(removeStr, toDonateStr);
        if (treeByIdMedVal->numOfNodes == 0) {
            this->maxInTreeByStrengthMedVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdMedVal =Contestant_Key(0, 0, false);
            this->minInTreeByIdMedVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForAdd();
            updateStateOfBalanceForRemove();
        }
        else {
            updateTreeByStrengthMedValForAdd(); //this one also updates the stated array
        }
        updateTreeByStrengthSmallValForAdd();
        /*----now the next step, donate the min from big to med--------*/
        auto NodeToDonate1 = treeByIdBigVal->find(minInTreeByIdBigVal, treeByIdBigVal->root);
        Contestant* toDonate1 = *(NodeToDonate1->getValue());
        Contestant_Key toRemoveStr1 = Contestant_Key(minInTreeByIdBigVal.id, minInTreeByIdBigVal.strength, true);
        Contestant_Key toRemoveId1 = Contestant_Key(minInTreeByIdBigVal.id, minInTreeByIdBigVal.strength, false);
        Contestant* toDonate1Str = treeByStrengthBigVal->find(toRemoveStr1,treeByStrengthBigVal->root)->value;
        treeByIdBigVal->remove(toRemoveId1);
        treeByStrengthBigVal->remove(toRemoveStr1);
        treeByIdMedVal->insertAux(toRemoveId1, toDonate1);
        treeByStrengthMedVal->insertAux(toRemoveStr1, toDonate1Str);
        if (treeByIdBigVal->numOfNodes == 0) {
            this->maxInTreeByStrengthBigVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdBigVal =Contestant_Key(0, 0, false);
            this->minInTreeByIdBigVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForAdd();
            updateStateOfBalanceForRemove();
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
        Contestant* toDonate = *(NodeToDonate->getValue()); //copyConstructor?
        treeByIdMedVal->remove(maxInTreeByIdMedVal);

        Contestant_Key toRemoveStr = Contestant_Key(maxInTreeByIdMedVal.id, maxInTreeByIdMedVal.strength, true);
        Contestant_Key toRemoveId = Contestant_Key(maxInTreeByIdMedVal.id, maxInTreeByIdMedVal.strength, false);
        Contestant* toDonateStr = treeByStrengthMedVal->find(toRemoveStr,treeByStrengthMedVal->root)->value;
        treeByStrengthMedVal->remove(toRemoveStr);
        treeByIdBigVal->insertAux(toRemoveId, toDonate);//remmember to insert to both of the trees
        treeByStrengthBigVal->insertAux(toRemoveStr, toDonateStr);
        if (treeByIdMedVal->numOfNodes == 0) {
            this->maxInTreeByStrengthMedVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdMedVal =Contestant_Key(0, 0, false);
            this->minInTreeByIdMedVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForAdd();
            updateStateOfBalanceForRemove();
        }
        else {
            updateTreeByStrengthMedValForAdd(); //this one also updates the stated array
        }
        updateTreeByStrengthBigValForAdd();
    }
    else {
        //donate the min from med to small
        auto NodeToDonate = treeByIdMedVal->find(minInTreeByIdMedVal, treeByIdMedVal->root);
        Contestant* toDonate = *(NodeToDonate->getValue());

        treeByIdMedVal->remove(minInTreeByIdMedVal);
        Contestant_Key toRemoveId= Contestant_Key(minInTreeByIdMedVal.id, minInTreeByIdMedVal.strength, false);
        Contestant_Key toRemoveStr= Contestant_Key(minInTreeByIdMedVal.id, minInTreeByIdMedVal.strength, true);
        Contestant* toDonateStr = treeByStrengthMedVal->find(toRemoveStr,treeByStrengthMedVal->root)->value;
        treeByStrengthMedVal->remove(toRemoveStr);
        treeByIdSmallVal->insertAux(toRemoveId, toDonate);
        treeByStrengthSmallVal->insertAux(toRemoveStr, toDonateStr);
        if (treeByIdMedVal->numOfNodes == 0) {
            this->maxInTreeByStrengthMedVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdMedVal =Contestant_Key(0, 0, false);
            this->minInTreeByIdMedVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForAdd();
            updateStateOfBalanceForRemove();
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
        Contestant* toDonate = *(NodeToDonate->getValue()); //copyConstructor?

        treeByIdSmallVal->remove(maxInTreeByIdSmallVal);
        Contestant_Key toRemoveStr = Contestant_Key(maxInTreeByIdSmallVal.id, maxInTreeByIdSmallVal.strength, true);
        Contestant_Key toRemoveId = Contestant_Key(maxInTreeByIdSmallVal.id, maxInTreeByIdSmallVal.strength, false);
        Contestant* toDonateStr =treeByStrengthSmallVal->find(toRemoveStr, treeByStrengthSmallVal->root)->value;
        treeByStrengthSmallVal->remove(toRemoveStr); ////-----------------change it to removeWithRepetition
        treeByIdMedVal->insertAux(toRemoveId, toDonate);//remmember to insert to both of the trees
        treeByStrengthMedVal->insertAux(toRemoveStr, toDonateStr);
        if (treeByIdSmallVal->numOfNodes == 0) {
            this->maxInTreeByStrengthSmallVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdSmallVal =Contestant_Key(0, 0, false);
            this->minInTreeByIdSmallVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForAdd();
            updateStateOfBalanceForRemove();
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
        Contestant* toMoveToBig = *(NodeToMoveToBig->getValue()); //copyConstructor?
        Contestant_Key toRemoveId = Contestant_Key(maxInTreeByIdMedVal.id, maxInTreeByIdMedVal.strength, false);
        Contestant_Key toRemoveStr = Contestant_Key(maxInTreeByIdMedVal.id, maxInTreeByIdMedVal.strength, true);
        Contestant* toMoveToBigStr =  treeByStrengthMedVal->find(toRemoveStr, treeByStrengthMedVal->root)->value;
        treeByIdMedVal->remove(toRemoveId);
        treeByStrengthMedVal->remove(toRemoveStr);
        treeByIdBigVal->insertAux(toRemoveId, toMoveToBig);
        treeByStrengthBigVal->insertAux(toRemoveStr, toMoveToBigStr);
        if (treeByIdMedVal->numOfNodes == 0) {
            this->maxInTreeByStrengthMedVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdMedVal=Contestant_Key(0, 0, false);
            this->minInTreeByIdMedVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForAdd();
            updateStateOfBalanceForRemove();
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
        Contestant* toMoveToMed = *(NodeToMoveToMed->getValue());
        treeByIdSmallVal->remove(toMoveId);
        Contestant* toMoveToMedStr = treeByStrengthSmallVal->find(toMoveStr,treeByStrengthSmallVal->root)->value;
        treeByStrengthSmallVal->remove(toMoveStr);
        treeByIdMedVal->insertAux(toMoveId, toMoveToMed);
        treeByStrengthMedVal->insertAux(toMoveStr, toMoveToMedStr);
        if (treeByIdSmallVal->numOfNodes == 0) {
            this->maxInTreeByStrengthSmallVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdSmallVal =Contestant_Key(0, 0, false);
            this->minInTreeByIdSmallVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForAdd();
            updateStateOfBalanceForRemove();
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
    this->minInTreeByIdSmallVal = (this->treeByIdSmallVal->findMin(treeByIdSmallVal->root))->key;
    updateStateOfBalanceForAdd();
    updateStateOfBalanceForRemove();
}
void Team::updateTreeByStrengthMedValForAdd() { //need to be here an update to the min max of by Id
    //and also for max By strength
    this->maxInTreeByStrengthMedVal = (this->treeByStrengthMedVal->findMax
            (this->treeByStrengthMedVal->root))->key;
    this->maxInTreeByIdMedVal = (this->treeByIdMedVal->findMax(treeByIdMedVal->root))->key;
    this->minInTreeByIdMedVal = (this->treeByIdMedVal->findMin(treeByIdMedVal->root))->key;
    updateStateOfBalanceForAdd();
    updateStateOfBalanceForRemove();
}
void Team::updateTreeByStrengthBigValForAdd() { //need to be here an update to the min max of by Id
    //and also for max By strength
    this->maxInTreeByStrengthBigVal = (this->treeByStrengthBigVal->findMax
            (this->treeByStrengthBigVal->root))->key;
    this->maxInTreeByIdBigVal = (this->treeByIdBigVal->findMax(treeByIdBigVal->root))->key;
    this->minInTreeByIdBigVal = (this->treeByIdBigVal->findMin(treeByIdBigVal->root))->key;
    updateStateOfBalanceForAdd();
    updateStateOfBalanceForRemove();
}
void Team::addContestantToATeam(const Contestant_Key&  keyToAdd, Contestant* toAdd, bool
called_from_optimal) {
    //Please Notice this one is added to the trees by strength
    //Contestant toAdd = Contestant(contestantId, countryId, strength, sport, true);
    int index = -1;
    for (int i = 0 ; i < NUM_OF_MAX_TEAMS ; i++) {

        if(toAdd->get_teamsIParticipate(i) == this->teamId){
            break;
        }
        if (toAdd->get_teamsIParticipate(i) == -2 && index == -1) {
            index=i;
            break;
        }
    }
    if(index!=-1) {
        toAdd->set_teamsIparticipate(index, this->teamId);
    }
    Contestant_Key toAddKeyStr = Contestant_Key(keyToAdd.id, keyToAdd.strength, true);
    //Please notice this one is added to the trees by Id
    Contestant_Key toAddKeyId = Contestant_Key(keyToAdd.id, keyToAdd.strength, false);
    Contestant* toAdd_team_whole_id = new Contestant(*toAdd);
    Contestant* toAdd_team_whole_str = new Contestant(*toAdd);
    Contestant* toAdd_str = new Contestant(*toAdd);
    Contestant* toAdd_id = new Contestant(*toAdd);

    team_whole_contestants_by_id->insertAux(toAddKeyId, toAdd_team_whole_id); //important for austerity_measures
    team_whole_contestants_by_strength->insertAux(toAddKeyStr, toAdd_team_whole_str);
    if (treeByIdSmallVal->numOfNodes == 0 && treeByIdMedVal->numOfNodes == 0 &&
        treeByIdBigVal->numOfNodes == 0) {
        treeByStrengthSmallVal->insertAux(toAddKeyStr, toAdd_str); //One Tree is the mirror of the other tree
        treeByIdSmallVal->insertAux(toAddKeyId, toAdd_id);
        updateTreeByStrengthSmallValForAdd();
        if(called_from_optimal == false) {
            updateOptimalTeamStrength();
        }
        this->numParticipants++;
        return;
    }
    if (keyToAdd.id < this->maxInTreeByIdSmallVal.id || (this->maxInTreeByIdSmallVal.id == 0 && keyToAdd.id <
        minInTreeByIdMedVal.id)) { //
        if (stateOfBalanceForAdd[0] < 1) {
            this->treeByStrengthSmallVal->insertAux(toAddKeyStr, toAdd_str);
            this->treeByIdSmallVal->insertAux(toAddKeyId, toAdd_id);
            updateTreeByStrengthSmallValForAdd();
        }
        else {
            makePlaceInTreeByIdSmallValForAdd();
            this->treeByStrengthSmallVal->insertAux(toAddKeyStr, toAdd_str);
            this->treeByIdSmallVal->insertAux(toAddKeyId, toAdd_id);
            updateTreeByStrengthSmallValForAdd();
        }
    }
    else if (keyToAdd.id < maxInTreeByIdMedVal.id || (( stateOfBalanceForAdd[2]==1) &&(keyToAdd.id < minInTreeByIdBigVal
            .id) || (keyToAdd.id > this->maxInTreeByIdSmallVal.id &&
                     maxInTreeByIdMedVal.id == 0))
    ) {
        if (stateOfBalanceForAdd[1] < 1) {
            this->treeByStrengthMedVal->insertAux(toAddKeyStr, toAdd_str);
            this->treeByIdMedVal->insertAux(toAddKeyId, toAdd_id);
            updateTreeByStrengthMedValForAdd();
        } else {
            makePlaceInTreeByIdMedValForAdd();
            this->treeByStrengthMedVal->insertAux(toAddKeyStr, toAdd_str);
            this->treeByIdMedVal->insertAux(toAddKeyId, toAdd_id);
            updateTreeByStrengthMedValForAdd();
        }
    }
    else { //which only left the case where strength is bigger that maxInTreeByStrengthBigVal

        if (stateOfBalanceForAdd[2] < 1) {
            this->treeByStrengthBigVal->insertAux(toAddKeyStr, toAdd_str);
            this->treeByIdBigVal->insertAux(toAddKeyId, toAdd_id);
            updateTreeByStrengthBigValForAdd();
        }
        else {
            makePlaceInTreeByIdBigValForAdd();
            this->treeByStrengthBigVal->insertAux(toAddKeyStr, toAdd_str);
            this->treeByIdBigVal->insertAux(toAddKeyId, toAdd_id);
            updateTreeByStrengthBigValForAdd();

        }
    }
    if(called_from_optimal == false) {
        updateOptimalTeamStrength();
    }
    this->numParticipants++;
    return;
}

void Team::update_contestant_team_array(int contestantId, int arrayIndex, int teamId){ //better to call this function
    // insert and remove
    Contestant_Key contestantKey = Contestant_Key(contestantId,-2, false);
    auto whole_id = (this->get_team_whole_contestants_by_id()->find(contestantKey,this->get_team_whole_contestants_by_id()->root));
    Contestant_Key contestantKeyStr = Contestant_Key(contestantId,whole_id->value->get_strength(), true);
    auto whole_str = (this->get_team_whole_contestants_by_strength()->find(contestantKeyStr,
                                                                   this->get_team_whole_contestants_by_strength()->root));
    AvlTree<Contestant_Key,Contestant*> *tree_to_find_id, *tree_to_find_str;
    if( contestantId <= this->maxInTreeByIdSmallVal.id){
        tree_to_find_id = this->treeByIdSmallVal;
        tree_to_find_str = this->treeByStrengthSmallVal;
    }
    else if( contestantId <= this->maxInTreeByIdMedVal.id){
            tree_to_find_id = this->treeByIdMedVal;
            tree_to_find_str = this->treeByStrengthMedVal;
        }
    else{
        tree_to_find_id = this->treeByIdBigVal;
        tree_to_find_str = this->treeByStrengthBigVal;
        }
    whole_id->value->set_teamsIparticipate(arrayIndex,teamId);
    whole_str->value->set_teamsIparticipate(arrayIndex,teamId);
    auto forTest = tree_to_find_id->find(contestantKey,tree_to_find_id->root);
    tree_to_find_id->find(contestantKey,tree_to_find_id->root)->value->set_teamsIparticipate(arrayIndex,teamId);
    tree_to_find_str->find(contestantKeyStr,tree_to_find_str->root)->value->set_teamsIparticipate(arrayIndex,teamId);

}
/*
void Team::addContestantToATeam(int contestantId, int countryId, int strength, Sport sport, bool called_from_optimal) {
    //Please Notice this one is added to the trees by strength
    Contestant toAdd = Contestant(contestantId, countryId, strength, sport, true);
    int index = 0;
    for (int i = 0 ; i < NUM_OF_MAX_TEAMS ; i++) {
        if ()
    }
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
        if(called_from_optimal == false) {
            updateOptimalTeamStrength();
        }
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
    if(called_from_optimal == false) {
        updateOptimalTeamStrength();
    }
}*/
AvlTree<Contestant_Key, Contestant*>* Team::get_team_whole_contestants_by_id() {
    return this->team_whole_contestants_by_id;
}
AvlTree<Contestant_Key, Contestant*>* Team::get_team_whole_contestants_by_strength() {
    return this->team_whole_contestants_by_strength;
}

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
void Team::updateTreeByStrengthForTrivialTreesAfterRemove() {
    if (treeByIdSmallVal->numOfNodes == 0) {
        this->maxInTreeByStrengthSmallVal =Contestant_Key(0, 0, true);
        this->maxInTreeByIdSmallVal =Contestant_Key(0, 0, false);
        this->minInTreeByIdSmallVal =Contestant_Key(0, 0, false);
        updateStateOfBalanceForAdd();
        updateStateOfBalanceForRemove();
    }
    if (treeByIdMedVal->numOfNodes == 0) {
        this->maxInTreeByStrengthMedVal =Contestant_Key(0, 0, true);
        this->maxInTreeByIdMedVal =Contestant_Key(0, 0, false);
        this->minInTreeByIdMedVal =Contestant_Key(0, 0, false);
        updateStateOfBalanceForAdd();
        updateStateOfBalanceForRemove();
    }
    if (treeByIdBigVal->numOfNodes == 0) {
        this->maxInTreeByStrengthBigVal =Contestant_Key(0, 0, true);
        this->maxInTreeByIdBigVal =Contestant_Key(0, 0, false);
        this->minInTreeByIdBigVal =Contestant_Key(0, 0, false);
        updateStateOfBalanceForAdd();
        updateStateOfBalanceForRemove();
    }

}
void Team::updateTreeByStrengthSmallValForRemove() { //need to be here an update to the min max of by Id
    //and also for max By strength
    this->maxInTreeByStrengthSmallVal = (this->treeByStrengthSmallVal->findMax
            (this->treeByStrengthSmallVal->root))->key;
    this->maxInTreeByIdSmallVal = (this->treeByIdSmallVal->findMax(treeByIdSmallVal->root))->key;
    this->minInTreeByIdSmallVal = (this->treeByIdSmallVal->findMin(treeByIdSmallVal->root))->key;
    updateStateOfBalanceForRemove();
    updateStateOfBalanceForAdd();
}
void Team::updateTreeByStrengthMedValForRemove() { //need to be here an update to the min max of by Id
    //and also for max By strength
    this->maxInTreeByStrengthMedVal = (this->treeByStrengthMedVal->findMax
            (this->treeByStrengthMedVal->root))->key;
    this->maxInTreeByIdMedVal = (this->treeByIdMedVal->findMax(treeByIdMedVal->root))->key;
    this->minInTreeByIdMedVal = (this->treeByIdMedVal->findMin(treeByIdMedVal->root))->key;
    updateStateOfBalanceForRemove();
    updateStateOfBalanceForAdd();
}
void Team::updateTreeByStrengthBigValForRemove() { //need to be here an update to the min max of by Id
    //and also for max By strength
    this->maxInTreeByStrengthBigVal = (this->treeByStrengthBigVal->findMax
            (this->treeByStrengthBigVal->root))->key;
    this->maxInTreeByIdBigVal = (this->treeByIdBigVal->findMax(treeByIdBigVal->root))->key;
    this->minInTreeByIdBigVal = (this->treeByIdBigVal->findMin(treeByIdBigVal->root))->key;
    updateStateOfBalanceForRemove();
    updateStateOfBalanceForAdd();
}

void Team::makePlaceInTreeByIdBigValForRemove() {
    if (stateOfBalanceForRemove[1] != -1) { //does it able to remove a node from the med tree?
        //donate the max from med to big
        auto NodeToDonate = treeByIdMedVal->find(maxInTreeByIdMedVal, treeByIdMedVal->root);
        Contestant* toDonate = *(NodeToDonate->getValue());
        treeByIdMedVal->remove(maxInTreeByIdMedVal);
        Contestant_Key toRemoveStr = Contestant_Key(maxInTreeByIdMedVal.id,maxInTreeByIdMedVal.strength, true );
        Contestant_Key toRemoveId = Contestant_Key(maxInTreeByIdMedVal.id,maxInTreeByIdMedVal.strength, false);
        Contestant* toDonateStr = treeByStrengthMedVal->find(toRemoveStr,treeByStrengthMedVal->root)->value;
        treeByStrengthMedVal->remove(toRemoveStr);
        treeByIdBigVal->insertAux(toRemoveId, toDonate);
        treeByStrengthBigVal->insertAux(toRemoveStr, toDonateStr);
        if (treeByIdMedVal->numOfNodes == 0) {
            this->maxInTreeByStrengthMedVal = Contestant_Key(0, 0, true);
            this->maxInTreeByIdMedVal = Contestant_Key(0, 0, false);
            this->minInTreeByIdMedVal = Contestant_Key(0, 0, false);
            updateStateOfBalanceForRemove();
            updateStateOfBalanceForAdd();
        }
        else {
            updateTreeByStrengthMedValForRemove(); //this one also updates the stated array
        }
        updateTreeByStrengthBigValForRemove();

    }
    else {
        //donate max from small to med
        //then donate max from med to big
        auto NodeToDonate = treeByIdSmallVal->find(maxInTreeByIdSmallVal, treeByIdSmallVal->root);
        Contestant* toDonate = *(NodeToDonate->getValue());
        treeByIdSmallVal->remove(maxInTreeByIdSmallVal);
        Contestant_Key removeStr = Contestant_Key(maxInTreeByIdSmallVal.id, maxInTreeByIdSmallVal.strength, true);
        Contestant_Key removeId = Contestant_Key(maxInTreeByIdSmallVal.id, maxInTreeByIdSmallVal.strength, false);
        Contestant* toDonateStr =treeByStrengthSmallVal->find(removeStr,treeByStrengthSmallVal->root)->value;
        treeByStrengthSmallVal->remove(removeStr);
        treeByIdMedVal->insertAux(removeId, toDonate);
        treeByStrengthMedVal->insertAux(removeStr, toDonateStr);
        if (treeByIdSmallVal->numOfNodes == 0) {
            this->maxInTreeByStrengthSmallVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdSmallVal =Contestant_Key(0, 0, false);
            this->minInTreeByIdSmallVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForRemove();
            updateStateOfBalanceForAdd();
        }
        else {
            updateTreeByStrengthSmallValForRemove(); //this one also updates the stated array
        }
        updateTreeByStrengthMedValForRemove();
        /*----now the next step, donate max from med to big--------*/
        auto NodeToDonate1 = treeByIdMedVal->find(maxInTreeByIdMedVal, treeByIdMedVal->root);
        Contestant* toDonate1 = *(NodeToDonate1->getValue());
        Contestant_Key toRemoveStr1 = Contestant_Key(maxInTreeByIdMedVal.id, maxInTreeByIdMedVal.strength, true);
        Contestant_Key toRemoveId1 = Contestant_Key(maxInTreeByIdMedVal.id, maxInTreeByIdMedVal.strength, false);
        Contestant* toDonate1Str =treeByStrengthMedVal->find(toRemoveStr1,treeByStrengthMedVal->root)->value;
        treeByIdMedVal->remove(toRemoveId1);
        treeByStrengthMedVal->remove(toRemoveStr1);
        treeByIdBigVal->insertAux(toRemoveId1, toDonate1);
        treeByStrengthBigVal->insertAux(toRemoveStr1, toDonate1Str);
        if (treeByIdMedVal->numOfNodes == 0) {
            this->maxInTreeByStrengthMedVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdMedVal =Contestant_Key(0, 0, false);
            this->minInTreeByIdMedVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForRemove();
            updateStateOfBalanceForAdd();
        }
        else {
            updateTreeByStrengthMedValForRemove(); //this one also updates the stated array
        }
        updateTreeByStrengthBigValForRemove();
    }
}

void Team::makePlaceInTreeByIdMedValForRemove() {
    if (stateOfBalanceForRemove[2] != -1) {
        //donate the min from big tree to med tree
        auto NodeToDonate = treeByIdBigVal->find(minInTreeByIdBigVal, treeByIdBigVal->root);
        Contestant* toDonate = *(NodeToDonate->getValue()); //copyConstructor?
        treeByIdBigVal->remove(minInTreeByIdBigVal);
        Contestant_Key toRemoveStr = Contestant_Key(minInTreeByIdBigVal.id, minInTreeByIdBigVal.strength, true);
        Contestant_Key toRemoveId = Contestant_Key(minInTreeByIdBigVal.id, minInTreeByIdBigVal.strength, false);
        Contestant* toDonateStr =treeByStrengthBigVal->find(toRemoveStr,treeByStrengthBigVal->root)->value;
        treeByStrengthBigVal->remove(toRemoveStr);
        treeByIdMedVal->insertAux(toRemoveId, toDonate);//remmember to insert to both of the trees
        treeByStrengthMedVal->insertAux(toRemoveStr, toDonateStr);
        if (treeByIdBigVal->numOfNodes == 0) {
            this->maxInTreeByStrengthBigVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdBigVal =Contestant_Key(0, 0, false);
            this->minInTreeByIdBigVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForRemove();
            updateStateOfBalanceForAdd();
        }
        else {
            updateTreeByStrengthBigValForRemove(); //this one also updates the stated array
        }
        updateTreeByStrengthMedValForRemove();
    }
    else {
        //donate the max from small to med
        auto NodeToDonate = treeByIdSmallVal->find(maxInTreeByIdSmallVal, treeByIdSmallVal->root);
        Contestant* toDonate = *(NodeToDonate->getValue());
        treeByIdSmallVal->remove(maxInTreeByIdSmallVal);
        Contestant_Key toRemoveId= Contestant_Key(maxInTreeByIdSmallVal.id, maxInTreeByIdSmallVal.strength, false);
        Contestant_Key toRemoveStr= Contestant_Key(maxInTreeByIdSmallVal.id, maxInTreeByIdSmallVal.strength, true);
        Contestant* toDonateStr =treeByStrengthSmallVal->find(toRemoveStr,treeByStrengthSmallVal->root)->value;
        treeByStrengthSmallVal->remove(toRemoveStr);
        treeByIdMedVal->insertAux(toRemoveId, toDonate);
        treeByStrengthMedVal->insertAux(toRemoveStr, toDonateStr);
        if (treeByIdSmallVal->numOfNodes == 0) {
            this->maxInTreeByStrengthSmallVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdSmallVal =Contestant_Key(0, 0, false);
            this->minInTreeByIdSmallVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForRemove();
            updateStateOfBalanceForAdd();
        }
        else {
            updateTreeByStrengthSmallValForRemove(); //this one also updates the stated array
        }
        updateTreeByStrengthMedValForRemove();


    }
}

void Team::makePlaceInTreeByIdSmallValForRemove() {
    if (stateOfBalanceForRemove[1] != -1) {
        //donate min from med to small
        auto NodeToDonate = treeByIdMedVal->find(minInTreeByIdMedVal, treeByIdMedVal->root);
        Contestant* toDonate = *(NodeToDonate->getValue()); //copyConstructor?
        treeByIdMedVal->remove(minInTreeByIdMedVal);
        Contestant_Key toRemoveStr = Contestant_Key(minInTreeByIdMedVal.id, minInTreeByIdMedVal.strength, true);
        Contestant_Key toRemoveId = Contestant_Key(minInTreeByIdMedVal.id, minInTreeByIdMedVal.strength, false);
        Contestant* toDonateStr =treeByStrengthMedVal->find(toRemoveStr,treeByStrengthMedVal->root)->value;
        treeByStrengthMedVal->remove(toRemoveStr); ////-----------------change it to removeWithRepetition
        treeByIdSmallVal->insertAux(toRemoveId, toDonate);//remmember to insert to both of the trees
        treeByStrengthSmallVal->insertAux(toRemoveStr, toDonateStr);
        if (treeByIdMedVal->numOfNodes == 0) {
            this->maxInTreeByStrengthMedVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdMedVal =Contestant_Key(0, 0, false);
            this->minInTreeByIdMedVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForRemove();
            updateStateOfBalanceForAdd();
        }
        else {
            updateTreeByStrengthMedValForRemove(); //this one also updates the stated array
        }
        updateTreeByStrengthSmallValForRemove();
    }
    else { //donate min from big to med
        //then donate min from med to small

        auto NodeToMoveToMed = treeByIdBigVal->find(minInTreeByIdBigVal,treeByIdBigVal->root);
        Contestant* toMoveToMed = *(NodeToMoveToMed->getValue()); //copyConstructor?
        Contestant_Key toRemoveId = Contestant_Key(minInTreeByIdBigVal.id, minInTreeByIdBigVal.strength, false);
        Contestant_Key toRemoveStr = Contestant_Key(minInTreeByIdBigVal.id, minInTreeByIdBigVal.strength, true);
        Contestant* toMoveToMedStr =treeByStrengthBigVal->find(toRemoveStr,treeByStrengthBigVal->root)->value;
        treeByIdBigVal->remove(toRemoveId);
        treeByStrengthBigVal->remove(toRemoveStr);
        treeByIdMedVal->insertAux(toRemoveId, toMoveToMed);
        treeByStrengthMedVal->insertAux(toRemoveStr, toMoveToMedStr);
        if (treeByIdBigVal->numOfNodes == 0) {
            this->maxInTreeByStrengthBigVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdBigVal=Contestant_Key(0, 0, false);
            this->minInTreeByIdBigVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForRemove();
            updateStateOfBalanceForAdd();
        }
        else {
            updateTreeByStrengthBigValForRemove();
        }
        updateTreeByStrengthMedValForRemove();
        //then donate min from med to small
        auto NodeToMoveToSmall = treeByIdMedVal->find(minInTreeByIdMedVal, treeByIdMedVal->root);
        Contestant_Key toMoveStr = Contestant_Key(minInTreeByIdMedVal.id, minInTreeByIdMedVal.strength, true);
        Contestant_Key toMoveId = Contestant_Key(minInTreeByIdMedVal.id, minInTreeByIdMedVal.strength, false);
        Contestant* toMoveToSmall = *(NodeToMoveToSmall->getValue());
        treeByIdMedVal->remove(toMoveId);
        Contestant* toMoveToSmallStr = treeByStrengthMedVal->find(toMoveStr,treeByStrengthMedVal->root)->value;
        treeByStrengthMedVal->remove(toMoveStr);
        treeByIdSmallVal->insertAux(toMoveId, toMoveToSmall);
        treeByStrengthSmallVal->insertAux(toMoveStr, toMoveToSmallStr);
        if (treeByIdMedVal->numOfNodes == 0) {
            this->maxInTreeByStrengthMedVal =Contestant_Key(0, 0, true);
            this->maxInTreeByIdMedVal =Contestant_Key(0, 0, false);
            this->minInTreeByIdMedVal =Contestant_Key(0, 0, false);
            updateStateOfBalanceForRemove();
            updateStateOfBalanceForAdd();
        }
        else {
            updateTreeByStrengthMedValForRemove(); //this one also updates the stated array
        }//this one also updates the stated array
        updateTreeByStrengthSmallValForRemove();

    }
}


void Team::removeContestantFromTeam(const Contestant_Key&  keyToRemove, bool called_from_optimal) { //Omer check
    // in olympics
    // if
    // the trees are
    // empty before calling to this function
    Contestant_Key toRemoveKeyStr = Contestant_Key(keyToRemove.id, keyToRemove.strength, true);
    //Please notice this one is added to the trees by Id
    Contestant_Key toRemoveKeyId = Contestant_Key(keyToRemove.id, keyToRemove.strength, false);
    Contestant *cont_team_whole_id_to_delete, *cont_team_whole_str_to_delete, *cont_id_to_delete, *cont_str_to_delete;
    cont_team_whole_id_to_delete = team_whole_contestants_by_id->find(toRemoveKeyId,team_whole_contestants_by_id->root)->value;
    auto forTest = team_whole_contestants_by_strength->find(toRemoveKeyStr,team_whole_contestants_by_strength->root);
    cont_team_whole_str_to_delete = team_whole_contestants_by_strength->find(toRemoveKeyStr,team_whole_contestants_by_strength->root)->value;
    team_whole_contestants_by_id->remove(toRemoveKeyId); //important for austerity_measures
    team_whole_contestants_by_strength->remove(toRemoveKeyStr);
    if (keyToRemove.id <= this->maxInTreeByIdSmallVal.id) {
        if (stateOfBalanceForRemove[0] > -1) {
            cont_str_to_delete = treeByStrengthSmallVal->find(toRemoveKeyStr,treeByStrengthSmallVal->root)->value;
            cont_id_to_delete = treeByIdSmallVal->find(toRemoveKeyId,treeByIdSmallVal->root)->value;
            this->treeByStrengthSmallVal->remove(toRemoveKeyStr);
            this->treeByIdSmallVal->remove(toRemoveKeyId);
            if (treeByIdSmallVal->numOfNodes == 0) {
                updateTreeByStrengthForTrivialTreesAfterRemove();
                if(called_from_optimal == false) {
                    updateOptimalTeamStrength();
                }
                this->numParticipants--;
                delete cont_team_whole_id_to_delete;
                delete cont_id_to_delete;
                delete cont_str_to_delete;
                delete cont_team_whole_str_to_delete;
                return;
            }
            updateTreeByStrengthSmallValForRemove();

        }
        else {
            makePlaceInTreeByIdSmallValForRemove();
            cont_str_to_delete = treeByStrengthSmallVal->find(toRemoveKeyStr,treeByStrengthSmallVal->root)->value;
            cont_id_to_delete = treeByIdSmallVal->find(toRemoveKeyId,treeByIdSmallVal->root)->value;
            this->treeByStrengthSmallVal->remove(toRemoveKeyStr);
            this->treeByIdSmallVal->remove(toRemoveKeyId);
            if (treeByIdSmallVal->numOfNodes == 0) {
                updateTreeByStrengthForTrivialTreesAfterRemove();
                if(called_from_optimal == false) {
                    updateOptimalTeamStrength();
                }
                this->numParticipants--;
                delete cont_team_whole_id_to_delete;
                delete cont_id_to_delete;
                delete cont_str_to_delete;
                delete cont_team_whole_str_to_delete;
                return;
            }
            updateTreeByStrengthSmallValForRemove();
        }

    }
    else if (keyToRemove.id <= maxInTreeByIdMedVal.id) {
        if (stateOfBalanceForRemove[1] > -1) {
            cont_str_to_delete = treeByStrengthMedVal->find(toRemoveKeyStr,treeByStrengthMedVal->root)->value;
            cont_id_to_delete = treeByIdMedVal->find(toRemoveKeyId,treeByIdMedVal->root)->value;
            this->treeByStrengthMedVal->remove(toRemoveKeyStr);
            this->treeByIdMedVal->remove(toRemoveKeyId);
            if (treeByIdMedVal->numOfNodes == 0) {
                updateTreeByStrengthForTrivialTreesAfterRemove();
                if(called_from_optimal == false) {
                    updateOptimalTeamStrength();
                }
                this->numParticipants--;
                delete cont_team_whole_id_to_delete;
                delete cont_id_to_delete;
                delete cont_str_to_delete;
                delete cont_team_whole_str_to_delete;
                return;
            }
            updateTreeByStrengthMedValForRemove();
        } else {
            makePlaceInTreeByIdMedValForRemove();
            cont_str_to_delete = treeByStrengthMedVal->find(toRemoveKeyStr,treeByStrengthMedVal->root)->value;
            cont_id_to_delete = treeByIdMedVal->find(toRemoveKeyId,treeByIdMedVal->root)->value;
            this->treeByStrengthMedVal->remove(toRemoveKeyStr);
            this->treeByIdMedVal->remove(toRemoveKeyId);
            if (treeByIdMedVal->numOfNodes == 0) {
                updateTreeByStrengthForTrivialTreesAfterRemove();
                if(called_from_optimal == false) {
                    updateOptimalTeamStrength();
                }
                this->numParticipants--;
                delete cont_team_whole_id_to_delete;
                delete cont_id_to_delete;
                delete cont_str_to_delete;
                delete cont_team_whole_str_to_delete;
                return;
            }
            updateTreeByStrengthMedValForRemove();
        }
    }
    else { //which only left the case where strength is bigger that maxInTreeByStrengthBigVal
        if (stateOfBalanceForRemove[2] > -1) {
            cont_str_to_delete = treeByStrengthBigVal->find(toRemoveKeyStr,treeByStrengthBigVal->root)->value;
            cont_id_to_delete = treeByIdBigVal->find(toRemoveKeyId,treeByIdBigVal->root)->value;
            this->treeByStrengthBigVal->remove(toRemoveKeyStr);
            this->treeByIdBigVal->remove(toRemoveKeyId);
            if (treeByIdBigVal->numOfNodes == 0) {
                updateTreeByStrengthForTrivialTreesAfterRemove();
                if(called_from_optimal== false) {
                    updateOptimalTeamStrength();
                }
                this->numParticipants--;
                delete cont_team_whole_id_to_delete;
                delete cont_id_to_delete;
                delete cont_str_to_delete;
                delete cont_team_whole_str_to_delete;
                return;
            }
            updateTreeByStrengthBigValForRemove();
        }
        else {
            makePlaceInTreeByIdBigValForRemove();
            cont_str_to_delete = treeByStrengthBigVal->find(toRemoveKeyStr,treeByStrengthBigVal->root)->value;
            cont_id_to_delete = treeByIdBigVal->find(toRemoveKeyId,treeByIdBigVal->root)->value;
            this->treeByStrengthBigVal->remove(toRemoveKeyStr);
            this->treeByIdBigVal->remove(toRemoveKeyId);
            if (treeByIdBigVal->numOfNodes == 0) {
                updateTreeByStrengthForTrivialTreesAfterRemove();
                if(called_from_optimal== false) {
                    updateOptimalTeamStrength();
                }
                this->numParticipants--;
                delete cont_team_whole_id_to_delete;
                delete cont_id_to_delete;
                delete cont_str_to_delete;
                delete cont_team_whole_str_to_delete;
                return;
            }
            updateTreeByStrengthBigValForRemove();

        }
    }
    if(called_from_optimal== false) {
        updateOptimalTeamStrength();
    }
    this->numParticipants--;
    delete cont_team_whole_id_to_delete;
    delete cont_id_to_delete;
    delete cont_str_to_delete;
    delete cont_team_whole_str_to_delete;
    return;
}


int Team::updateOptimalTeamStrength_aux(CHOICE choice1, CHOICE choice2, CHOICE choice3) {
    AvlTree<Contestant_Key,Contestant*> *T1,*T2,*T3;
       T1= this->choose_tree_by_choice(choice1);
       T2= this->choose_tree_by_choice(choice2);
       T3= this->choose_tree_by_choice(choice3);
       int optimalTeamStrength_aux;

    if (team_whole_contestants_by_id->numOfNodes == 0) {
        optimalTeamStrength_aux = 0;
        return optimalTeamStrength_aux;
    }
    else {
        if (team_whole_contestants_by_strength->numOfNodes % 3 != 0 || team_whole_contestants_by_strength->numOfNodes
                                                                       == 3) {
            optimalTeamStrength_aux = 0;
            return optimalTeamStrength_aux;
        }
        else {
            auto contestant_node_MinStrength1 = T1->findMin
                    (T1->root);
            auto contestant_MinStrength1 = Contestant(*contestant_node_MinStrength1->value);
            this->removeContestantFromTeam(Contestant_Key(*(contestant_node_MinStrength1->getKey())),true);
            /*------------------------------------------------------------------------------------*/

            auto contestant_node_MinStrength2 = T2->findMin
                    (T2->root);
            auto contestant_MinStrength2 =   Contestant(*contestant_node_MinStrength2->value);
            this->removeContestantFromTeam(Contestant_Key(*contestant_node_MinStrength2->getKey()),true);
            /*------------------------------------------------------------------------------------*/
            auto contestant_node_MinStrength3 = T3->findMin
                    (T3->root);
            auto contestant_MinStrength3 =  Contestant(*contestant_node_MinStrength3->value);
            this->removeContestantFromTeam(Contestant_Key(*(contestant_node_MinStrength3->getKey())),true);
            /*------------------------------------------------------------------------------------*/
             optimalTeamStrength_aux = this->maxInTreeByStrengthSmallVal.strength + this->maxInTreeByStrengthMedVal
                    .strength +
                                        this->maxInTreeByStrengthBigVal.strength;
            Contestant_Key firstKeyToAdd = Contestant_Key(contestant_MinStrength1.get_contestantId(),
                                                          contestant_MinStrength1.get_strength(), true);
            this->addContestantToATeam(firstKeyToAdd, &contestant_MinStrength1, true);
            Contestant_Key secondToAdd = Contestant_Key(contestant_MinStrength2.get_contestantId(),
                                                        contestant_MinStrength2.get_strength(), true);

            this->addContestantToATeam(secondToAdd, &contestant_MinStrength2, true);
            Contestant_Key thirdToAdd = Contestant_Key(contestant_MinStrength3.get_contestantId(),
                                                       contestant_MinStrength3.get_strength(), true);
            this->addContestantToATeam(thirdToAdd, &contestant_MinStrength3, true);
            /*this->addContestantToATeam(contestant_MinStrength1.get_contestantId(),
                                       contestant_MinStrength1.get_countryId(),
                                       contestant_MinStrength1.get_strength(), contestant_MinStrength1.get_sport(),
                                       true);
            this->addContestantToATeam(contestant_MinStrength2.get_contestantId(),
                                       contestant_MinStrength2.get_countryId(),
                                       contestant_MinStrength2.get_strength(), contestant_MinStrength2.get_sport(),
                                       true);
            this->addContestantToATeam(contestant_MinStrength3.get_contestantId(),
                                       contestant_MinStrength3.get_countryId(),
                                       contestant_MinStrength3.get_strength(), contestant_MinStrength3.get_sport(),
                                       true);*/
        return optimalTeamStrength_aux;
        }

    }
}

int Team::getNumParticipants() const {
    return this->numParticipants;
}

AvlTree<Contestant_Key, Contestant *> *Team::choose_tree_by_choice(CHOICE c) {
    switch(c)
    {
        case CHOICE::SMALL:
            return this->treeByStrengthSmallVal;
        case CHOICE::MEDIUM:
            return this->treeByStrengthMedVal;
        case CHOICE::BIG:
            return this->treeByStrengthBigVal;
        default:
            assert(false);//shouldn't get here.
    }
}

void Team::updateOptimalTeamStrength() {
    int array[10]={0,0,0,0,0,0,0,0,0,0};
    array[0]=this->updateOptimalTeamStrength_aux(CHOICE::SMALL,CHOICE::SMALL,CHOICE::SMALL);
    array[1]=this->updateOptimalTeamStrength_aux(CHOICE::SMALL,CHOICE::SMALL,CHOICE::MEDIUM);
    array[3]=this->updateOptimalTeamStrength_aux(CHOICE::SMALL,CHOICE::SMALL,CHOICE::BIG);
    array[4]=this->updateOptimalTeamStrength_aux(CHOICE::SMALL,CHOICE::MEDIUM,CHOICE::MEDIUM);
    array[5]=this->updateOptimalTeamStrength_aux(CHOICE::SMALL,CHOICE::BIG,CHOICE::BIG);
    array[6]=this->updateOptimalTeamStrength_aux(CHOICE::MEDIUM,CHOICE::MEDIUM,CHOICE::MEDIUM);
    array[7]=this->updateOptimalTeamStrength_aux(CHOICE::BIG,CHOICE::BIG,CHOICE::BIG);
    array[8]=this->updateOptimalTeamStrength_aux(CHOICE::MEDIUM, CHOICE::BIG,CHOICE::BIG);
    array[9]=this->updateOptimalTeamStrength_aux(CHOICE::MEDIUM, CHOICE::MEDIUM,CHOICE::BIG);
    int max = array[0];
    for(int i=0;i<10;i++){
        max = array[i]>max?array[i]:max;
    }
    this->optimalTeamStrength=max;
}

