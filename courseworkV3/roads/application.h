#ifndef OOP_APPLICATION_H
#define OOP_APPLICATION_H


#include "interface.h"
#include "../communicator/communicator.h"

#include <QApplication>


/**
 * Приложение "Перекресток"
 * Отображает сам перекресток и светофоры на нём
 * Наследуется от QApplication
 * Состоит из коммуникатора и интерфейса
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
    void from(const QByteArray&);
    void to(const QString&);
};


#endif //OOP_APPLICATION_H
