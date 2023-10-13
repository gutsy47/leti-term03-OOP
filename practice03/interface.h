#ifndef TINTERFACE_H
#define TINTERFACE_H


#include "number.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <vector>


class TInterface : public QWidget {
private:
    Q_OBJECT;

    std::vector<QLabel*> delimeters;
    std::vector<std::vector<std::vector<QLineEdit*>>> numbers;

    QPushButton *print_btn;
    QPushButton *determinant_btn;
    QPushButton *rank_btn;
    QPushButton *transpose_btn;

    QLabel *output;

    std::vector<std::vector<number>> getValues();
    int matrixSize;

public:
    TInterface(QWidget *parent = nullptr, int size = 1);
    ~TInterface();

public slots:
    void print();
    void determinant();
    void rank();
    void transpose();
};


#endif // TINTERFACE_H
