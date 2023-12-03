#ifndef OOP_SAMPLE_H
#define OOP_SAMPLE_H


#include "parser.h"

#include <QPainter>


class TSample {
private:
    std::vector<std::vector<int>> values;

public:
    TSample(TParser*);
    void changeSource(TParser*);
    bool isEmpty();
    void draw(QPainter*, QRect);
};


#endif //OOP_SAMPLE_H
