#include <iostream>
#include "AvlTree.h"
#include "Team.h"
#include "Contestant.h"
#include "wet1util.h"
#include "Olympicsa1.h"

int main() {
    Olympics* paris2024 = new Olympics();
    paris2024->add_country(2, 2);
    paris2024->add_team(2,2,Sport::SPINNING);
    paris2024->add_team(3,2,Sport::SPINNING);
    paris2024->add_team(4,2,Sport::SPINNING);

    for (int i = 1; i < 2; ++i) {
        paris2024->add_contestant(i,2,Sport::SPINNING,2);
    }
    for(int i = 1; i<2;i++){
        paris2024->add_contestant_to_team(2,i);
        paris2024->add_contestant_to_team(3,i);
        paris2024->add_contestant_to_team(4,i);
    }
//    for(int i = 1; i<2000;i++){
//        paris2024->update_contestant_strength(i,2);
//    }
    for(int i = 1; i<2;i++){
        paris2024->remove_contestant_from_team(2,i);
        paris2024->remove_contestant_from_team(3,i);
        paris2024->remove_contestant_from_team(4,i);
    }
//    for (int i = 1; i < 2000; ++i) {
//        paris2024->remove_contestant(i);
//    }
    paris2024->remove_team(2);
    paris2024->remove_team(3);
    paris2024->remove_team(4);
    paris2024->remove_country(2);
    int ziv = 1;
    delete paris2024;
    return 0;
}