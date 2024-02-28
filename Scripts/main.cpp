#include <iostream>
#include "AvlTree.h"
#include "Team.h"
#include "Contestant.h"
#include "wet1util.h"

int main() {

    Team* team = new Team(1, Sport::ACROBATICS, 0, 123); // Example values for teamId, sport, numParticipants, and
    // countryId
//    team->updateStateOfBalanceForAdd();
//
//
// team->addContestantToATeam(i, 123, i, Sport::ACROBATICS);
    //team->addContestantToATeam(1, 123, 1, Sport::ACROBATICS);
    for (int i = 0; i <= 5000 ; ++i) {
//        team->addContestantToATeam(i, 123, i, Sport::ACROBATICS);
//        team->addContestantToATeam(200+i, 123, 200+i, Sport::ACROBATICS);
        team->addContestantToATeam(i, 123, i, Sport::SPINNING);

    }
//    team->addContestantToATeam(10, 123, 3, Sport::ACROBATICS);
//    team->addContestantToATeam(13, 123, 6, Sport::ACROBATICS);
//    team->addContestantToATeam(15, 123, 9, Sport::ACROBATICS);
//    team->addContestantToATeam(8, 123, 4, Sport::ACROBATICS);
//    team->addContestantToATeam(12, 123, 5, Sport::ACROBATICS);
//    team->addContestantToATeam(14, 123, 0, Sport::ACROBATICS);
//    team->addContestantToATeam(7, 0, 2, Sport::ACROBATICS);
//    team->addContestantToATeam(6, 0, 6, Sport::ACROBATICS);
//    team->addContestantToATeam(9, 0, 7, Sport::ACROBATICS);
//    team->addContestantToATeam(11, 0, 7, Sport::ACROBATICS);
//    team->addContestantToATeam(16, 0, 14, Sport::ACROBATICS);
//    team->addContestantToATeam(18, 0, 4, Sport::ACROBATICS);
    /*-----------------------------------------------------------------------------------------*/
//    team->addContestantToATeam(3, 0, 2, Sport::ACROBATICS);
//    team->addContestantToATeam(1, 0, 2, Sport::ACROBATICS);
//    team->addContestantToATeam(0, 0, 2, Sport::ACROBATICS);
    /*team->addContestantToATeam(10, 0, 3, Sport::ACROBATICS);
    team->addContestantToATeam(9, 0, 7, Sport::ACROBATICS);
    team->addContestantToATeam(11, 0, 7, Sport::ACROBATICS);
    team->addContestantToATeam(16, 0, 14, Sport::ACROBATICS);
    team->addContestantToATeam(18, 0, 4, Sport::ACROBATICS);*/

    for (int i = 0 ; i < 3 ; i++) {
        cout << "#updateStateOfBalance " << team->getStateOfBalanceForAdd(i) <<endl;
    }
    cout << "hello" << endl;
    return 0;
}