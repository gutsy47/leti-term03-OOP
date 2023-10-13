#include "interface.h"
#include "matrix.h"
#include <vector>


const int WINDOW_SIZE_X = 360;
const int WINDOW_SIZE_Y = 370;


TInterface::TInterface(QWidget *parent, int size) : QWidget(parent) {
    setWindowTitle("Пр. работа #3");
    setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);

    matrixSize = size;

    numbers.resize(size);
    delimeters.resize(size*size);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            numbers[i].resize(size);
            numbers[i][j].resize(2);

            numbers[i][j][0] = new QLineEdit("0", this);
            numbers[i][j][0]->setGeometry(70*j + 10, 40*i + 10, 25, 25);

            delimeters[i+j] = new QLabel(" /", this);
            delimeters[i+j]->setGeometry(70*j + 35, 40*i + 10, 10, 25);

            numbers[i][j][1] = new QLineEdit("0", this);
            numbers[i][j][1]->setGeometry(70*j + 45, 40*i + 10, 25, 25);
        }
    }

    print_btn = new QPushButton("Print", this);
    print_btn->setGeometry(10, 210, 60, 30);
    determinant_btn = new QPushButton("Determ.", this);
    determinant_btn->setGeometry(10, 250, 60, 30);
    rank_btn = new QPushButton("Rank", this);
    rank_btn->setGeometry(10, 290, 60, 30);
    transpose_btn = new QPushButton("Transpose", this);
    transpose_btn->setGeometry(10, 330, 60, 30);

    output = new QLabel("", this);
    output->setGeometry(80, 210, 270, 150);
    output->setStyleSheet("QLabel { background-color : black; color : white; }");

    connect(print_btn, SIGNAL(pressed()), this, SLOT(print()));
    connect(determinant_btn, SIGNAL(pressed()), this, SLOT(determinant()));
    connect(rank_btn, SIGNAL(pressed()), this, SLOT(rank()));
    connect(transpose_btn, SIGNAL(pressed()), this, SLOT(transpose()));
}


TInterface::~TInterface() {
    for (auto &delim : delimeters)
        delete delim;
    for (auto &row : numbers)
        for (auto &col : row)
            for (auto &el : col)
                delete el;

    delete print_btn;
    delete determinant_btn;
    delete rank_btn;
    delete transpose_btn;

    delete output;
}


std::vector<std::vector<number>> TInterface::getValues() {
    std::vector<std::vector<number>> values(matrixSize, std::vector<number>(matrixSize, 0));

    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            number value(numbers[i][j][0]->text().toDouble(), numbers[i][j][1]->text().toDouble());
            values[i][j] = value;
        }
    }

    return values;
}


void TInterface::print() {
    std::vector<std::vector<number>> values = getValues();
    TMatrix matrix(matrixSize);
    matrix.setValues(values);
    QString output_text("");
    output_text << matrix;
    output->setText(output_text);
}


void TInterface::determinant() {
    std::vector<std::vector<number>> values = getValues();
    TMatrix matrix(matrixSize);
    matrix.setValues(values);
    QString output_text("");
    output_text << matrix.getDeterminant();
    output->setText(output_text);
}


void TInterface::rank() {
    std::vector<std::vector<number>> values = getValues();
    TMatrix matrix(matrixSize);
    matrix.setValues(values);
    QString output_text("");
    output_text += std::to_string(matrix.getRank());
    output->setText(output_text);
}


void TInterface::transpose() {
    std::vector<std::vector<number>> values = getValues();
    TMatrix matrix(matrixSize);
    matrix.setValues(values);
    matrix.transpose();
    QString output_text("");
    output_text << matrix;
    output->setText(output_text);
}
