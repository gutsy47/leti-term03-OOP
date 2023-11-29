#ifndef APPLICATION_H
#define APPLICATION_H


#include <QObject>
#include <QCoreApplication>

#include "direct_graph.h"

#include "../common/common.h"
#include "../common/communicator.h"

#include <vector>


class TApplication : public QCoreApplication {
private:
    Q_OBJECT
    TCommunicator *comm;

public:
    TApplication(int, char **);

signals:

public slots:
    void receive(QByteArray);
};


#endif // APPLICATION_H
