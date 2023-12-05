#include "sample.h"


TSample::TSample(TParser *parser) {
    graph = parser->graph;
}


void TSample::changeSource(TParser *parser) {
    graph = parser->graph;
}


bool TSample::empty() {
    return graph->empty();
}


void TSample::draw(QPainter* painter, QRect rect) {
    painter->drawText(
        rect,
        QString().setNum(graph->size()),
        QTextOption(Qt::AlignCenter)
    );
}

