#ifndef APPLICATION_H
#define APPLICATION_H


#include <QObject>
#include <QCoreApplication>

#include "direct_graph.h"

#include "../common/common.h"
#include "../common/communicator.h"

#include <fstream>
#include <vector>


class TApplication : public QCoreApplication {
private:
    Q_OBJECT
    TCommunicator *comm;
    short getValues(const std::string, std::vector<std::vector<int>>&);

public:
    TApplication(int, char **);

signals:

public slots:
    void receive(QByteArray);
};


#endif // APPLICATION_H
