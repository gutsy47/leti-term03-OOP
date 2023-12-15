#include "player.h"


Player::Player() {
    money = 0;
    movesLeft = GameSettings::moveLimit;
}


void Player::setMoney(int amount) {
    money = amount;
}


void Player::setMovesLeft(int amount) {
    movesLeft = amount;
}


void Player::move() {
    movesLeft -= 1;
}


int Player::getMoney() {
    return money;
}


int Player::getMovesLeft() {
    return movesLeft;
}
