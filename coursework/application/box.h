#ifndef OOP_BOX_H
#define OOP_BOX_H


#include "game-settings.h"

#include <QPushButton>


/**
 * @class Box
 * @brief Represents a box in the game
 * A descendant of QPushButton, but instead of
 * a normal button "box.png" is displayed
 */
class Box : public QPushButton {
private:
    Q_OBJECT

    bool opened; // Is the box opened
    int  value;  // Amount of the money

public:
    explicit Box(QWidget *parent = nullptr);

    void setRandomValue(); // Random value setter
    void setValue(int);    // Value setter
    void setOpen(bool);    // Opened setter
    int getValue();        // Value getter
    bool isOpen();         // Opened getter

    void draw(int, int);
};


#endif //OOP_BOX_H
