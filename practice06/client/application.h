#ifndef APPLICATION_H
#define APPLICATION_H


#include <QObject>
#include <QApplication>


#include "interface.h"
#include "../common/communicator.h"


class TApplication : public QApplication {
private:
    Q_OBJECT
    TCommunicator *comm;
    TInterface *interface;

public:
    TApplication(int, char **);

public slots:
    void fromCommunicator(const QByteArray&);
    void toCommunicator(const QString&);
};

#endif // APPLICATION_H
