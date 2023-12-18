#include "sample-light.h"


void TLight::draw(QPainter* painter, int x, int y) {
    // Светофор
    QColor back = QColor("#303030");
    painter->setBrush(back);
    painter->setPen(QPen(back, 0));
    QRect backRect(x, y, 36, 78);
    painter->drawRoundedRect(backRect, 3, 3);
    painter->drawRect(x + 16, y + 78, 4, 12);

    // Лампы
    painter->setBrush((state == RED) ? Qt::red : Qt::darkRed);
    painter->drawEllipse(x + 8, y + 6,  20, 20);
    painter->setBrush((state == YELLOW) ? Qt::yellow : Qt::darkYellow);
    painter->drawEllipse(x + 8, y + 28, 20, 20);
    painter->setBrush((state == GREEN) ? Qt::green : Qt::darkGreen);
    painter->drawEllipse(x + 8, y + 50, 20, 20);
}