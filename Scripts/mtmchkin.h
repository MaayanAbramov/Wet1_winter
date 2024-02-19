//
// Created by maaya on 07/01/2024.
//

#ifndef WINTERAVLTREE_MTMCHKIN_H
#define WINTERAVLTREE_MTMCHKIN_H

#ifndef MTMCHKIN_H_
#define MTMCHKIN_H_

#include <string>
#include <queue>
#include "Players/Player.h"
#include "Cards/Card.h"
#include <memory>

class Mtmchkin{

    std::queue<std::shared_ptr<Player>> m_players;
    std::queue<std::shared_ptr<Card>> m_deck;
    std::deque<std::shared_ptr<Player>> m_leaderboard;
    int m_leaderboardIndexWin;
    int m_leaderboardIndexLose;
    int m_rounds;

public:

    /*
    * C'tor of Mtmchkin class
    *
    * @param filename - a file which contains the cards of the deck.
    * @return
    *      A new instance of Mtmchkin.
    */
    explicit Mtmchkin(const std::string fileName);
    /*
     * Here we deleted the copy constructor.
     *
     */

    Mtmchkin(const Mtmchkin& other) = delete;

    /*
     * Here we deleted the copy constructor.
     *
     */

    Mtmchkin& operator=(const Mtmchkin& other)=delete;

    /*
    * Play the next Round of the game - according to the instruction in the exercise document.
    *
    * @return
    *      void
    */
    void playRound();

    /*
    * Prints the leaderBoard of the game at a given stage of the game - according to the instruction in the exercise document.
    *
    * @return
    *      void
    */
    void printLeaderBoard() const;

    /*
    *  Checks if the game ended:
    *
    *  @return
    *          True if the game ended
    *          False otherwise
    */
    bool isGameOver() const;

    /*
    *  Returns the number of rounds played.
    *
    *  @return
    *          int - number of rounds played
    */
    int getNumberOfRounds() const;
};



#endif /* MTMCHKIN_H_ */
#endif //WINTERAVLTREE_MTMCHKIN_H
