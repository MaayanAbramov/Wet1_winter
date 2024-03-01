#include <iostream>
#include "AvlTree.h"
#include "Team.h"
#include "Contestant.h"
#include "wet1util.h"

int main() {

    Team* team = new Team(1, Sport::ACROBATICS, 0, 123); // Example values for teamId, sport, numParticipants, and
    /*for (int i = 0; i <= 10 ; ++i) {
        team->addContestantToATeam(i, 123, i, Sport::ACROBATICS);
    }
    for(int i = 0 ; i <= 5; i++){
        team->removeContestantFromTeam(Contestant_Key(i,i,false));
    }*/
    for (int i = 0; i <900 ; ++i) {
        team->addContestantToATeam(i,123,i,Sport::ACROBATICS, false);
    }
    for(int i = 0; i< 900 ; i++){
        team->removeContestantFromTeam(Contestant_Key(i,i,false),false);
        cout << "the optimal strength is "<<team->get_optimalTeamStrength() << endl;

    }
//    team->addContestantToATeam(2, 123, 2, Sport::ACROBATICS,false);
//    team->addContestantToATeam(10, 123, 3, Sport::ACROBATICS,false);
//    team->addContestantToATeam(13, 123, 6, Sport::ACROBATICS,false);
//    team->addContestantToATeam(15, 123, 9, Sport::ACROBATICS,false);
//    team->addContestantToATeam(8, 123, 4, Sport::ACROBATICS,false);
//    team->addContestantToATeam(12, 123, 5, Sport::ACROBATICS,false);
//    team->addContestantToATeam(14, 123, 0, Sport::ACROBATICS);
//    team->addContestantToATeam(7, 0, 2, Sport::ACROBATICS);
//    team->addContestantToATeam(6, 0, 6, Sport::ACROBATICS);
//    team->addContestantToATeam(9, 0, 7, Sport::ACROBATICS);
//    team->addContestantToATeam(11, 0, 7, Sport::ACROBATICS);
//    team->addContestantToATeam(16, 0, 14, Sport::ACROBATICS);
//    team->addContestantToATeam(18, 0, 4, Sport::ACROBATICS);
    /*-----------------------------------------------------------------------------------------*/
//    team->addContestantToATeam(18, 0, 4, Sport::ACROBATICS);
//    team->addContestantToATeam(13, 0, 6, Sport::ACROBATICS);
//    team->addContestantToATeam(9, 0, 7, Sport::ACROBATICS);
//    team->addContestantToATeam(16, 0, 14, Sport::ACROBATICS);
//    team->addContestantToATeam(12, 0, 5, Sport::ACROBATICS);
//    team->addContestantToATeam(8, 0, 4, Sport::ACROBATICS);
//    team->addContestantToATeam(15, 0, 9, Sport::ACROBATICS);
//    team->addContestantToATeam(11, 0, 7, Sport::ACROBATICS);
//    team->addContestantToATeam(7, 0, 2, Sport::ACROBATICS);
//    team->addContestantToATeam(14, 0, 0, Sport::ACROBATICS);
//    team->addContestantToATeam(10, 0, 3, Sport::ACROBATICS);
//    team->addContestantToATeam(6, 0, 6, Sport::ACROBATICS);
//    team->removeContestantFromTeam(Contestant_Key(18, 4, false));
//    team->removeContestantFromTeam(Contestant_Key(16, 14, false));
//    team->removeContestantFromTeam(Contestant_Key(9, 7, false));
//    team->removeContestantFromTeam(Contestant_Key(11, 7, false));
//    team->removeContestantFromTeam(Contestant_Key(12, 5, false));

    /*for (int i = 0 ; i < 3 ; i++) {
        cout << "#updateStateOfBalance " << team->getStateOfBalanceForAdd(i) <<endl;
    }
    cout << "#remove status array" << endl;
    for (int i = 0 ; i < 3 ; i++) {
        cout << "#updateStateOfBalance " << team->getStateOfBalanceForRemove(i) <<endl;
    }
    team->removeContestantFromTeam(Contestant_Key(2,2,false));
    cout << "--------------------------after removing---------------------------" << endl;
    for (int i = 0 ; i < 3 ; i++) {
        cout << "#updateStateOfBalance " << team->getStateOfBalanceForAdd(i) <<endl;
    }
    cout << "#remove status array" << endl;
    for (int i = 0 ; i < 3 ; i++) {
        cout << "#updateStateOfBalance " << team->getStateOfBalanceForRemove(i) <<endl;
    }*/
    cout << "the optimal strength is "<<team->get_optimalTeamStrength() << endl;
    delete team;
    return 0;
}