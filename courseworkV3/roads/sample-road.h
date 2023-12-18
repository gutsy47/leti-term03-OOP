#ifndef OOP_SAMPLE_H
#define OOP_SAMPLE_H


#include <QPainter>


/// Рисунок перекрестка
struct TRoad {
    void draw(QPainter*, QRect&); // Рисует перекресток
};


#endif //OOP_SAMPLE_H