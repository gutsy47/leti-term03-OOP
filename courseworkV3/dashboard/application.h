#ifndef OOP_APPLICATION_H
#define OOP_APPLICATION_H


#include "interface.h"
#include "../communicator/communicator.h"

#include <QApplication>


/**
 * Приложение "Панель управления"
 * Отвечает за управление светофорами
 */
class TApplication : public QApplication {
private:
    Q_OBJECT
    P2PCommunicator *communicator;
    TInterface      *interface;

public:
    TApplication(int, char**);

public slots:
    void handshakeDone(int);
    void to(const QString&);
};


#endif //OOP_APPLICATION_H
