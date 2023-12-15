#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H


#include "game-settings.h"


class Player {
private:
    int money;
    int movesLeft;

public:
    Player();

    void setMoney(int);
    void setMovesLeft(int);
    void move();
    int getMoney();
    int getMovesLeft();
};


#endif //OOP_PLAYER_H
