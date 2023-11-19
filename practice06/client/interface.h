#ifndef INTERFACE_H
#define INTERFACE_H


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>

#include <vector>


class TInterface : public QWidget {
private:
    Q_OBJECT

    std::vector<std::vector<std::vector<QLineEdit*>>> nums;

    QPushButton *btnPrint;
    QPushButton *btnDeterminant;
    QPushButton *btnRank;
    QPushButton *btnTranspose;

    QRadioButton *doubleMode;
    QRadioButton *complexMode;
    QRadioButton *rationalMode;

    QLabel *output;

    int matrixSize;

public:
    explicit TInterface(QWidget *parent = nullptr);
    ~TInterface() override;

public slots:
    void answer(QString);

private slots:
    void formRequest();

signals:
    void request(QString);
};


#endif // INTERFACE_H
