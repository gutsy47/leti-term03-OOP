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


void TSample::draw(QPainter* painter, QRect &rect) {
    if (empty()) return;

    // Draw vertices
    int radius = 150; // Radius of the whole circle
    int vertR = 15;   // Circle radius of each vertex
    std::vector<Vertex*> vertices = graph->getVertices();
    std::map<Vertex*, QPoint> verticesPos;
    int step = 360 / graph->size();
    for (int i = 0, angle = 0; i < graph->size(); ++i, angle += step) {
        // Get coords
        double rad = qDegreesToRadians(static_cast<double>(angle));
        int dx = static_cast<int>(radius * qCos(rad));
        int dy = static_cast<int>(radius * qSin(rad));

        // Draw vertex stroke
        QPoint circlePoint = rect.center() + QPoint(dx, dy);
        verticesPos[vertices[i]] = circlePoint;
        painter->setBrush(Qt::black);
        painter->drawEllipse(circlePoint, vertR, vertR);

        // Draw vertex name
        painter->setPen(Qt::white);
        painter->setFont(QFont("Arial", 10, QFont::Bold));
        QRect textRect(circlePoint.x() - vertR, circlePoint.y() - vertR, 2*vertR, 2*vertR);
        painter->drawText(textRect, QChar(vertices[i]->getName()), QTextOption(Qt::AlignCenter));
    }

    // Draw edges
    painter->setPen(QPen(Qt::black, 3));
    for (int i = 0; i < graph->size(); ++i) {
        std::vector<Vertex*> neighbors = vertices[i]->getNeighbors();
        for (int j = 0; j < neighbors.size(); ++j) {
            // Draw edge
            // Using the Pythagorean formula, obtain the vector
            // offset (length = vertR) of the direction of the edge
            QPointF p1 = verticesPos[vertices[i]];
            QPointF p2 = verticesPos[neighbors[j]];
            QPointF v = p2 - p1;
            double length = sqrt(v.x() * v.x() + v.y() * v.y());
            QPointF offset = QPoint(v.x() / length * vertR, v.y() / length * vertR);
            painter->drawLine(p1 + offset, p2 - offset);

            // Draw arrow
            double size = 5;
            QPointF arrowTop = p2 - offset;
            QPointF arrowDir = (v / length) * size;
            QPointF arrowL = arrowTop - arrowDir + QPointF(arrowDir.y(), -arrowDir.x());
            QPointF arrowR = arrowTop - arrowDir + QPointF(-arrowDir.y(), arrowDir.x());
            painter->drawPolygon(QPolygonF() << arrowTop << arrowL << arrowR);
        }
    }
}