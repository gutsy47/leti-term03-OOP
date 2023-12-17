#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H


#include "game-settings.h"


/**
 * @class Player
 * @brief Represents a player of the game
 *
 * Holds the current state of a player,
 * including their money and how many moves they have left.
 */
class Player {
private:
    int money;     // How much money player could take
    int movesLeft; // How many moves left

public:
    Player();

    void setMoney(int);     // Set custom amount of money
    void setMovesLeft(int); // Set custom amount of moves
    void move();            // Decrease number of moves
    int getMoney();         // Return amount of money
    int getMovesLeft();     // Return amount of moves left
};


#endif //OOP_PLAYER_H
