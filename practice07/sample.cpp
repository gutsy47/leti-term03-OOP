#include "sample.h"


TSample::TSample(TParser *parser) {
    values = parser->getValues();
}


void TSample::changeSource(TParser *parser) {
    values = parser->getValues();
}


bool TSample::isEmpty() {
    return values.size() == 0;
}


void TSample::draw(QPainter* painter, QRect rect) {
    painter->drawText(
        rect,
        QString().setNum(values.size()),
        QTextOption(Qt::AlignCenter)
    );
}

