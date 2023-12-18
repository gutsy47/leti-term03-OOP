#ifndef OOP_APPLICATION_H
#define OOP_APPLICATION_H


#include "interface.h"
#include "../communicator/communicator.h"

#include <QApplication>


class TApplication : public QApplication {
private:
    Q_OBJECT

public:
    TApplication(int, char**);
};


#endif //OOP_APPLICATION_H
