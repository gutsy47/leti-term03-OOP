#include "sample-switcher.h"


/// Constructor
TSampleSwitcher::TSampleSwitcher(TParser* parser) : TSample(parser) {
    if (empty()) return;
    activeIndex = 0;
}


/// Change the source of the sample
void TSampleSwitcher::changeSource(TParser* parser) {
    TSample::changeSource(parser);
    activeIndex = 0;
}


/// Switch the active vertex to the nearest "right" one if true
void TSampleSwitcher::updateActive(bool isForward) {
    activeIndex = isForward ? ++activeIndex : --activeIndex + graph->size();
    activeIndex %= graph->size();
}


/// Draw the sample with active node
void TSampleSwitcher::draw(QPainter* painter, QRect& rect) {
    if (empty()) return;

    TSample::draw(painter, rect); // Draw the sample

    // Highlight the active vertex with a red circle
    int radius = 150;
    int vertR = 15;
    int angle = activeIndex * 360 / graph->size();
    double rad = qDegreesToRadians(static_cast<double>(angle));
    int dx = static_cast<int>(radius * qCos(rad));
    int dy = static_cast<int>(radius * qSin(rad));
    QPoint circlePoint = rect.center() + QPoint(dx, dy);
    painter->setBrush(Qt::red);
    painter->drawEllipse(circlePoint, vertR, vertR);

    // Rewrite the name of the active vertex
    std::vector<Vertex*> vertices = graph->getVertices();
    painter->setPen(Qt::white);
    painter->setFont(QFont("Arial", 10, QFont::Bold));
    QRect textRect(circlePoint.x() - vertR, circlePoint.y() - vertR, 2*vertR, 2*vertR);
    painter->drawText(textRect, QChar(vertices[activeIndex]->getName()), QTextOption(Qt::AlignCenter));
}