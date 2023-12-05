#ifndef INTERFACE_H
#define INTERFACE_H


#include "parser.h"
#include "sample.h"

#include <QWidget>
#include <QPushButton>


class TInterface : public QWidget {
private:
    Q_OBJECT

    QPushButton *btnUpdFile;
    TSample *sample;

public:
    explicit TInterface(TSample*, QWidget *parent = nullptr);
    ~TInterface() override;

protected:
    void paintEvent(QPaintEvent*) override;

public slots:
    void updFile();
};


#endif // INTERFACE_H
