#ifndef OOP_SAMPLE_H
#define OOP_SAMPLE_H


#include "parser.h"

#include <QPainter>
#include <map>


class TSample {
protected:
    Graph *graph;

public:
    // Constructor and updater
    TSample(TParser*);
    virtual void changeSource(TParser*);

    bool empty();
    virtual void draw(QPainter*, QRect&);
};


#endif //OOP_SAMPLE_H
