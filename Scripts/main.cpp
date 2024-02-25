#include <iostream>
#include "AvlTree.h"
#include "Team.h"
#include "Contestant.h"
#include "wet1util.h"

int main() {

    Team team = Team(1, Sport::ACROBATICS, 0, 123); // Example values for teamId, sport, numParticipants, and countryId
    team.updateStateOfBalance();




    for (int i = 0 ; i < 3 ; i++) {
        cout << "#updateStateOfBalance " << team.getStateOfBalance(i) <<endl;
    }
    cout << "------------------------------------" << endl;
    team.addContestantToATeam(10, 0, 2, Sport::ACROBATICS);

    for (int i = 0 ; i < 3 ; i++) {
        cout << "#updateStateOfBalance " << team.getStateOfBalance(i) <<endl;
    }
    cout << "------------------------------------" << endl;


    return 0;
}