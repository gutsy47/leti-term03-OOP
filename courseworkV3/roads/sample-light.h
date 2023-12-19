#ifndef OOP_SAMPLE_LIGHT_H
#define OOP_SAMPLE_LIGHT_H


#include <QPainter>


enum { OFF = -1, RED = 0, YELLOW = 1, GREEN = 2 };


class TLight {
private:
    short state = OFF;

public:
    // Переключение состояний
    void turnOff()    { state = OFF; };
    void turnRed()    { state = RED; };
    void turnYellow() { state = YELLOW; };
    void turnGreen()  { state = GREEN; };

    // Отрисовка
    void draw(QPainter*, int, int);
};


#endif //OOP_SAMPLE_LIGHT_H
