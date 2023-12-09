#include "interface.h"


const int WINDOW_SIZE_X = 400;
const int WINDOW_SIZE_Y = 440;

TInterface::TInterface(TSampleSwitcher *sample, QWidget *parent) : QWidget(parent) {
    setWindowTitle("#8. State graph painter");
    setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);

    this->sample = sample;

    btnUpdFile = new QPushButton("Change file", this);
    btnUpdFile->setGeometry(300, 405, 80, 30);
    connect(btnUpdFile, SIGNAL(pressed()), this, SLOT(updFile()));
}


TInterface::~TInterface() {
    delete btnUpdFile;
    delete sample;
}


void TInterface::paintEvent(QPaintEvent*) {
    QPainter painter;
    painter.begin(this);
    QRect rect(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y - 40);
    sample->draw(&painter, rect);
    painter.end();
}


void TInterface::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton)  sample->updateActive(false);
    if (event->button() == Qt::RightButton)  sample->updateActive(true);
    update();
}


void TInterface::updFile() {
    TParser parser;
    sample->changeSource(&parser);
    if (sample->empty()) close();
}