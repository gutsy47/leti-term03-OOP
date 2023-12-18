#ifndef OOP_SAMPLE_LIGHT_H
#define OOP_SAMPLE_LIGHT_H


#include <QPainter>


class TLight {
private:
    enum { MANUAL = 0, AUTOMATIC = 1, AUTONOMOUS = 2} mode = AUTOMATIC;
    enum { OFF = -1, RED = 0, YELLOW = 1, GREEN = 2 } state = OFF;

public:
    // Переключение режимов
    void setAutonomousMode() { mode = AUTONOMOUS; };
    void setAutomaticMode()  { mode = AUTOMATIC; };
    void setManualMode()     { mode = MANUAL; };

    // Получить текущий режим
    int getMode() { return mode; };

    // Переключение состояний
    void turnOff()    { state = OFF; };
    void turnRed()    { state = RED; };
    void turnYellow() { state = YELLOW; };
    void turnGreen()  { state = GREEN; };

    // Отрисовка
    void draw(QPainter*, int, int);
};


#endif //OOP_SAMPLE_LIGHT_H
