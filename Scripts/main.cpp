#include <iostream>
#include "AvlTree.h"
#include "Team.h"
#include "Contestant.h"
#include "wet1util.h"
#include "Olympicsa1.h"
using namespace std;
int main() {
    Olympics* paris2024 = new Olympics();
    paris2024->add_country(5, 2);
//    paris2024->add_team(2,5,Sport::SPINNING);
//    paris2024->add_team(3,5,Sport::SPINNING);
//    paris2024->add_team(4,5,Sport::SPINNING);
   // paris2024->add_contestant(301, 5, Sport::SPINNING, 301);
    //paris2024->add_contestant_to_team(4, 301);
    int k = 40;
    for (int i = 1; i < k; ++i) {
        paris2024->add_team(i,5,Sport::SPINNING);
        paris2024->add_contestant(i,5,Sport::SPINNING,i);
    }
    for(int i = 1; i<k;i++){
        paris2024->add_contestant_to_team(i,i);

    }
    for (int i = k-1 ; i >-1; i--) {
        if(i>1)
        {
            paris2024->unite_teams(i-1,i);
        }
    }
    for(int i = 1; i<k;i++){
        paris2024->remove_contestant_from_team(1,i);

    }
    for(int i = 1; i<k;i++){
        paris2024->remove_contestant(i);

    }
    for(int i = 1; i<k;i++){
        StatusType a = paris2024->remove_team(i);
        std::cout<<"remove team"<< i<<":";
        if (a == StatusType::SUCCESS){
            std::cout<<"success"<<std::endl;
        }
        if (a == StatusType::FAILURE){
            std::cout<<"failure"<<std::endl;
        }
    }
    paris2024->remove_country(5);
    //std::cout << paris2024->get_team_strength(2).ans() << endl;
    //std::cout << paris2024->austerity_measures(2).ans() << endl;
    /*for(int i = 1; i<k;i++){
        std::cout<<(int)paris2024->update_contestant_strength(i,7);
    }
    for (int i = 2; i < 5; ++i) {
        std::cout<<"strength of team  "<<i<<" "<<paris2024->get_team_strength(i).ans()<<std::endl;;
    }
    for (int i = 1; i < k; ++i) {
        if(i>1){
            assert(paris2024->get_strength(i).ans()==paris2024->get_strength(i-1).ans());
        }
    }

    for (int i = 1; i < k; ++i) {
        paris2024->get_strength(i);
    }
    std::cout<<"after removinggg team strength ~~~~ woowww **************************************"<<std::endl;

*/
//    for(int i = 1; i<k;i++){
//        paris2024->remove_contestant_from_team(2,i);
//        //std::cout<<"after removinggg team strength ~~~~ woowww **************************************"<<std::endl;
//        //assert(paris2024->get_team_strength(2).ans() == paris2024->get_team_strength(3).ans());
//        //assert(paris2024->get_team_strength(2).ans() == paris2024->get_team_strength(4).ans());
//    }
//    paris2024->remove_contestant_from_team(2, 301);
//    /*std::cout<<"after removinggg team strength ~~~~ woowww **************************************"<<std::endl;
//    for (int i = 2; i < 5; ++i) {
//        std::cout<<"expecting 0 , strength of team  "<<i<<" "<<paris2024->get_team_strength(i).ans()<<std::endl;;
//    }*/
//    for (int i = 1; i < k; ++i) {
//        paris2024->remove_contestant(i);
//    }
//    paris2024->remove_contestant(301);
//    paris2024->remove_team(2);
//    paris2024->remove_team(3);
//    paris2024->remove_team(4);
//    paris2024->remove_country(5);
    int ziv = 1;
    delete paris2024;
    return 0;
}