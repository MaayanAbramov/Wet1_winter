#include <iostream>
#include "AvlTree.h"
#include "Team.h"
#include "Contestant.h"
#include "wet1util.h"

int main() {

    Team team = Team(1, Sport::ACROBATICS, 0, 123); // Example values for teamId, sport, numParticipants, and countryId
    team.updateStateOfBalance();


    Contestant num2 = Contestant(7, 0, 4, Sport::ACROBATICS, false);
    team.get_treeByIdMedVal()->insertAux(num2.get_contestantId(), num2);
    num2.set_is_by_strength_sorted(true);
    team.get_treeByStrengthMedVal()->insertAux(num2.get_strength(), num2);
    // Update the state of balance
    team.updateTreeByStrengthMedVal();

    Contestant num3 = Contestant(11, 0, 7, Sport::ACROBATICS, false);
    team.get_treeByIdBigVal()->insertAux(num3.get_contestantId(), num3);
    num3.set_is_by_strength_sorted(true);
    team.get_treeByStrengthBigVal()->insertAux(num3.get_strength(), num3);
    // Update the state of balance
    team.updateTreeByStrengthBigVal();

    for (int i = 0 ; i < 3 ; i++) {
        cout << "#updateStateOfBalance " << team.getStateOfBalance(i) <<endl;
    }
    cout << "------------------------------------" << endl;
    team.makePlaceInTreeByIdBigVal();
    for (int i = 0 ; i < 3 ; i++) {
        cout << "#updateStateOfBalance " << team.getStateOfBalance(i) <<endl;
    }
    cout << "------------------------------------" << endl;



    return 0;
}