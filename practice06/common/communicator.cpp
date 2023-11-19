#include "communicator.h"


TCommunicator::TCommunicator(TCommParams &pars, QObject *parent) : QUdpSocket(parent) {
    params = pars;
    ready = bind(
        params.rHost,
        params.rPort,
        QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint
    );
    if (ready) connect(this, SIGNAL(readyRead()), this, SLOT(receive()));
}


void TCommunicator::send(const QByteArray& msg) {
    if (ready) writeDatagram(msg, params.sHost, params.sPort);
    qDebug() << "TCommunicator::send(): \t" << msg;
}


void TCommunicator::receive() {
    if (hasPendingDatagrams()) {
        quint64 size = pendingDatagramSize();
        QByteArray msg((int)size, '\0');
        readDatagram(msg.data(), (int)size);
        qDebug() << "TCommunicator::receive(): \t" << msg;
        emit received(msg);
    }
}
