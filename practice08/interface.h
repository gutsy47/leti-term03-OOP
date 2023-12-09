#ifndef INTERFACE_H
#define INTERFACE_H


#include "parser.h"
#include "sample-switcher.h"

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>


class TInterface : public QWidget {
private:
    Q_OBJECT

    QPushButton *btnUpdFile;
    TSampleSwitcher *sample;

public:
    explicit TInterface(TSampleSwitcher*, QWidget *parent = nullptr);
    ~TInterface() override;

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;

public slots:
    void updFile();
};


#endif // INTERFACE_H
