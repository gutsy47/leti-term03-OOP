#include "interface.h"
#include "../common/common.h"
#include <QInputDialog>
#include <QMessageBox>


const int WINDOW_SIZE_X = 360;
const int WINDOW_SIZE_Y = 350;


TInterface::TInterface(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Работа 7");
    setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);

    filename = new QLineEdit("input.txt", this);
    filename->setGeometry(10, 10, 250, 30);

    btnDraw = new QPushButton("Draw", this);
    btnDraw->setGeometry(260, 10, 50, 30);

    connect(btnDraw, SIGNAL(pressed()), this, SLOT(formRequest()));

    output = new QLabel("", this);
    output->setGeometry(80, 210, 270, 100);
    output->setStyleSheet("QLabel { background-color : black; color : white; }");
}


TInterface::~TInterface() {
    delete filename;
    delete btnDraw;
    delete output;
}


void TInterface::formRequest() {
    QString msg;
    msg << filename->text();

    qDebug() << "TInterface::formRequest(): \t" << msg;
    emit request(msg);
}


void TInterface::answer(QString msg) {
    qDebug() << "TInterface::answer(): \t" << msg;

    QString text;
    int sepInd = (int) msg.indexOf(separator);
    int answer = msg.left(sepInd).toInt();
    switch (answer) {
        case 0: break;
        case -1:
            text += "Error: File not found";
            break;
        case -2:
            text += "Error: Invalid syntax";
            break;
        case -3:
            text += "Error: Invalid size";
            break;
        case -4:
            text += "Error: Non-zero diagonal element";
            break;
        default: text += "Error: Unexpected behaviour";
    }

//    msg = msg.mid(sepInd + 1, msg.length() - sepInd - 2);
//    sepInd = (int) msg.indexOf(separator);
//    text += msg.left(sepInd);
    output->setText(text);
}
