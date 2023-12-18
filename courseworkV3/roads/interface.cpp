#include "interface.h"


/// Write to the QString operator
const QChar separator(';');
QString &operator>> (QString &str, const QString &other) {
    if (!str.isEmpty()) str.append(separator);
    str += other;
    return str;
}


/// Конструктор
TInterface::TInterface(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Курсовая вариант 3");
    setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
    road = new TRoad();
    for (int i = 0; i < LIGHTS_COUNT; ++i) lights[i] = new TLight();

    // DELETE ME
    lights[0]->turnOff();
    lights[1]->turnRed();
    lights[2]->turnYellow();
    lights[3]->turnGreen();
    // DELETE ME

}


/// Деструктор
TInterface::~TInterface() {
    delete road;
    for (auto &light : lights) delete light;
}


/// Вызывается при обновлении интерфейса
void TInterface::paintEvent(QPaintEvent*) {
    QPainter painter;
    painter.begin(this);
    QRect rect(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y);
    road->draw(&painter, rect);
    for (int i = 0; i < LIGHTS_COUNT; ++i) lights[i]->draw(&painter, LIGHTS_COORDS[i][0], LIGHTS_COORDS[i][1]);
    painter.end();
}


void TInterface::answer(QString msg) {

}