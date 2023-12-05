#ifndef OOP_SAMPLE_H
#define OOP_SAMPLE_H


#include "parser.h"

#include <QPainter>


class TSample {
private:
    Graph *graph;

public:
    TSample(TParser*);
    void changeSource(TParser*);
    bool empty();
    void draw(QPainter*, QRect);
};


#endif //OOP_SAMPLE_H
