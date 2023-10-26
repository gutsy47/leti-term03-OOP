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
    connect(btnDeterminant, SIGNAL(pressed()), this, SLOT(formRequest()));
    connect(btnRank, SIGNAL(pressed()), this, SLOT(formRequest()));
    connect(btnTranspose, SIGNAL(pressed()), this, SLOT(formRequest()));
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
    if (btn == btnRank)
        msg << QString().setNum(RANK_REQUEST);
    if (btn == btnTranspose)
        msg << QString().setNum(TRANSPOSE_REQUEST);

    qDebug() << "TInterface::formRequest(): \t" << msg;

    emit request(msg);
}


void TInterface::answer(QString msg) {
    qDebug() << "TInterface::answer(): \t" << msg;

    QString text;
    int sepInd = msg.indexOf(separator);
    int answer = msg.left(sepInd).toInt();
    if (answer >= LAST_ELEMENT) return;

    msg = msg.mid(sepInd + 1, msg.length() - sepInd - 2);
    sepInd = msg.indexOf(separator);
    text += msg.left(sepInd);
    output->setText(text);
}
