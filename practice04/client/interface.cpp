#include "interface.h"
#include "../common/common.h"


const int WINDOW_SIZE_X = 360;
const int WINDOW_SIZE_Y = 370;
const int MATRIX_SIZE = 3;


TInterface::TInterface(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Работа 4");
    setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);

    matrixSize = MATRIX_SIZE;

    nums.resize(matrixSize);
    delims.resize(matrixSize*matrixSize);

    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            nums[i].resize(matrixSize);
            nums[i][j].resize(2);

            nums[i][j][0] = new QLineEdit("0", this);
            nums[i][j][0]->setGeometry(70*j + 10, 40*i + 10, 25, 25);

            delims[i+j] = new QLabel(" /", this);
            delims[i+j]->setGeometry(70*j + 35, 40*i + 10, 10, 25);

            nums[i][j][1] = new QLineEdit("0", this);
            nums[i][j][1]->setGeometry(70*j + 45, 40*i + 10, 25, 25);
        }
    }

    btnPrint = new QPushButton("Print", this);
    btnPrint->setGeometry(10, 210, 60, 30);
    btnDeterminant = new QPushButton("Determ.", this);
    btnDeterminant->setGeometry(10, 250, 60, 30);
    btnRank = new QPushButton("Rank", this);
    btnRank->setGeometry(10, 290, 60, 30);
    btnTranspose = new QPushButton("Transpose", this);
    btnTranspose->setGeometry(10, 330, 60, 30);

    output = new QLabel("", this);
    output->setGeometry(80, 210, 270, 150);
    output->setStyleSheet("QLabel { background-color : black; color : white; }");

    connect(btnPrint, SIGNAL(pressed()), this, SLOT(formRequest()));
//    connect(btnDeterminant, SIGNAL(pressed()), this, SLOT(determinant()));
//    connect(btnRank, SIGNAL(pressed()), this, SLOT(rank()));
//    connect(btnTranspose, SIGNAL(pressed()), this, SLOT(transpose()));
}


TInterface::~TInterface() {
    for (auto &delim : delims)
        delete delim;
    for (auto &row : nums)
        for (auto &col : row)
            for (auto &el : col)
                delete el;

    delete btnPrint;
    delete btnDeterminant;
    delete btnRank;
    delete btnTranspose;

    delete output;
}


void TInterface::formRequest() {
    QString msg;
    for (auto &row : nums)
        for (auto &col : row)
            for (auto &el : col)
                msg << el->text();
    QPushButton *btn = (QPushButton*) sender();

    if (btn == btnPrint)
        msg << QString().setNum(PRINT_REQUEST);
    if (btn == btnDeterminant)
        msg << QString().setNum(DETERM_REQUEST);

    emit request(msg);
}


void TInterface::answer(QString msg) {
    qDebug() << "TInterface::answer(): \t" << msg;

    QString text;
    int p = msg.indexOf(separator);
    int t = msg.left(p).toInt();
    msg = msg.mid(p + 1, msg.length() - p - 2);
    switch (t) {
        case PRINT_ANSWER:
            p = msg.indexOf(separator);
            text += msg.left(p);
//            text += msg.right(msg.length() - p - 1);
            output->setText(text);
            break;
//        case DETERM_ANSWER:
//            text = "p(x) = ";
//            text += msg;
//            output->setText(text);
//            break;
        default:
            break;
    }
}
