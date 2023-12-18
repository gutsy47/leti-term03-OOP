#ifndef OOP_INTERFACE_H
#define OOP_INTERFACE_H


#include "application.h"
#include "traffic-light.h"

#include <QWidget>


class TInterface : public QWidget {
private:
    Q_OBJECT

public:
    explicit TInterface(QWidget* = nullptr);
    ~TInterface() override;
};


#endif //OOP_INTERFACE_H
