#include "box.h"
#include <QDir>
#include <QCoreApplication>


const int SIZE = 80; // Button size in pixels


Box::Box(QWidget *parent) : QPushButton(parent) {
    opened = false;
    value = 0;
}


/// Set amount of money in the box
void Box::setRandomValue() {
    value = GameSettings::boxMin + rand() % (GameSettings::boxMax - GameSettings::boxMin);
}


/// Return the amount of money in the box
int Box::getValue() {
    return value;
}


/// Update status of the box (also updates the icon)
void Box::setOpen(bool status) {
    opened = status;

    QIcon icon (opened ? std::getenv("BOX_OPENED_PATH") : std::getenv("BOX_CLOSED_PATH"));
    if (!opened) this->setEnabled(false);

    this->setIcon(icon);
    this->setIconSize(QSize(SIZE, SIZE));
}


/// Return true if the box is opened
bool Box::isOpen() {
    return opened;
}


/// Draw the box in the given position
void Box::draw(int x, int y) {
    QIcon icon(std::getenv("BOX_CLOSED_PATH"));
    this->setIcon(icon);
    this->setIconSize(QSize(SIZE, SIZE));
    this->setGeometry(x, y, SIZE, SIZE);

    this->move(x, y);
    this->show();
}