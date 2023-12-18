#include "sample-road.h"


void TRoad::draw(QPainter* painter, QRect &rect) {
    QColor border = QColor("#8D8D8D"); // Цвет бордюров
    QColor green  = QColor("#5BAB5E"); // Цвет травы
    QColor bg     = QColor("#505050"); // Цвет фона
    QColor line   = QColor("#FFFFFF"); // Цвет разметки
    int w = rect.width();
    int h = rect.height();

    // Заливаем дорогу
    painter->fillRect(rect, bg);
    painter->setRenderHint(QPainter::Antialiasing);

    // Отрисовка прямоугольников по краям
    painter->setBrush(green);
    painter->setPen(QPen(border, 15));
    painter->drawRect(-15,      -15,      w/2 - 45, h/2 - 45); // Левый верхний
    painter->drawRect(w/2 + 60, -15,      w/2 - 45, h/2 - 45); // Правый верхний
    painter->drawRect(-15,      h/2 + 60, w/2 - 45, h/2 - 45); // Левый нижний
    painter->drawRect(w/2 + 60, h/2 + 60, w/2 - 45, h/2 - 45); // Правый нижний
    painter->setPen(QPen(line, 3));

    // Отрисовка горизонтальной разметки
    int N = (w / 2 - 50) / 50;
    for (int i = 0; i < N; ++i) painter->drawLine(50*i,            h/2, 50*i + 25,       h/2);
    for (int i = N; i > 0; --i) painter->drawLine(w/2 + 50*i + 25, h/2, w/2 + 50*i + 50, h/2);

    // Отрисовка вертикальной разметки
    N = (h / 2 - 50) / 50;
    for (int i = 0; i < N; ++i) painter->drawLine(w/2, 50*i,            w/2, 50*i + 25);
    for (int i = N; i > 0; --i) painter->drawLine(w/2, h/2 + 50*i + 25, w/2, h/2 + 50*i + 50);
}