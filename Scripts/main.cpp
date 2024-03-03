#include <iostream>
#include "AvlTree.h"
#include "Team.h"
#include "Contestant.h"
#include "wet1util.h"
#include "Olympicsa1.h"

int main() {
    Olympics* paris2024 = new Olympics();
    paris2024->add_country(854, 2);
    paris2024->add_country(855, 8);
    paris2024->add_country(856, 4);
    paris2024->add_country(857, 0);
    for (int i = 1 ; i < 1000; i++) {
        paris2024->add_team(i, 854 + i%4, Sport::ACROBATICS);

    }
    for (int i = 1 ; i < 1000; i++) {
        paris2024->remove_team(i);

    }

    paris2024->remove_country(854);
    paris2024->remove_country(855);
    paris2024->remove_country(856);
    paris2024->remove_country(857);
    int ziv = 1;





    return 0;
}