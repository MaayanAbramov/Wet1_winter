#include <iostream>
#include "AvlTree.h"
#include "Team.h"
#include "Contestant.h"
#include "wet1util.h"

int main() {

    Team team = Team(1, Sport::ACROBATICS, 0, 123); // Example values for teamId, sport, numParticipants, and countryId
    team.updateStateOfBalance();

    Contestant num1 = Contestant(2, 0, 1, Sport::ACROBATICS, false);
    team.get_treeByIdSmallVal()->insertAux(2, num1);
    num1.set_is_by_strength_sorted(true);
    team.get_treeByStrengthSmallVal()->insertAux(1, num1);
    // Update the state of balance
    team.updateTreeByStrengthSmallVal();

    Contestant num2 = Contestant(5, 0, 7, Sport::ACROBATICS, false);
    team.get_treeByIdMedVal()->insertAux(5, num2);
    num2.set_is_by_strength_sorted(true);
    team.get_treeByStrengthMedVal()->insertAux(7, num2);
    // Update the state of balance
    team.updateTreeByStrengthMedVal();


    for (int i = 0 ; i < 3 ; i++) {
        cout << "#updateStateOfBalance " << team.getStateOfBalance(i) <<endl;
    }
    cout << "------------------------------------" << endl;
    team.makePlaceInTreeByIdSmallVal();
    for (int i = 0 ; i < 3 ; i++) {
        cout << "#updateStateOfBalance " << team.getStateOfBalance(i) <<endl;
    }
    cout << "------------------------------------" << endl;
    return 0;
}