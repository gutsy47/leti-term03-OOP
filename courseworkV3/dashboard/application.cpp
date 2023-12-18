#include "application.h"


TApplication::TApplication(int argc, char *argv[]) : QApplication(argc, argv) {
    communicator = new P2PCommunicator();
    communicator->initHandshake();

    interface = new TInterface();
    interface->show();

    connect(communicator, SIGNAL(handshakeDone(int)),   this,      SLOT(handshakeDone(int)));
    connect(interface,    SIGNAL(request(QString)),     this,      SLOT(to(QString)));
}


void TApplication::handshakeDone(int order) {

}


void TApplication::to(const QString &msg) {
    communicator->send(QByteArray().append(msg.toStdString()));
}