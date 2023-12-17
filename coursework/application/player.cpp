#include "player.h"


/// Constructor
Player::Player() {
    money = 0;
    movesLeft = GameSettings::moveLimit;
}


/// Set custom amount of money
void Player::setMoney(int amount) {
    money = amount;
}


/// Set custom amount of player's moves left
void Player::setMovesLeft(int amount) {
    movesLeft = amount;
}


/// Make a move. Decrease player's moves left by 1
void Player::move() {
    movesLeft -= 1;
}


/// Return how much money player could have earned now
int Player::getMoney() {
    return money;
}


/// Return remaining amount of moves
int Player::getMovesLeft() {
    return movesLeft;
}
