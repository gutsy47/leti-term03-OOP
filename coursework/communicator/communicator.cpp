#include "communicator.h"
#include <QHostInfo>


int  P2PCommunicator::hostMsgSize    = 4;
char P2PCommunicator::hostRequest[]  = {0x05, 0x00, 0x01, 0x08};
char P2PCommunicator::hostResponse[] = {0x05, 0x01, 0x00, 0x08};


P2PCommunicator::P2PCommunicator(QHostAddress remoteHost, quint16 basePort, QObject *parent) : QUdpSocket(parent) {
    handshakeStatus = -1;

    if (remoteHost == QHostAddress::LocalHost) params.localHost = QHostAddress::LocalHost;
    else {
        QHostInfo info;
        QList<QHostAddress> addresses = info.addresses();
        params.localHost = (addresses.isEmpty() ? QHostAddress::LocalHost : addresses.first());
    }

    params.localReadPort   = basePort;
    params.remoteHost      = remoteHost;
    params.remoteWritePort = basePort + 1;

    isReady = bind(params.localHost, params.localReadPort);
    if (!isReady) {
        swapPorts();
        isReady = bind(params.localHost, params.localReadPort);
    }
    if (isReady) connect(this, SIGNAL(readyRead()), this, SLOT(receive()));
}


void P2PCommunicator::initHandshake() {
    if (handshakeStatus < 0) {
        handshakeStatus = 0;
        send(QByteArray(hostRequest, hostMsgSize));
    }
}


void P2PCommunicator::verifyOrder(const char *msg, const int size) {
    if (size == hostMsgSize) {
        if (memcmp(msg, hostRequest, size) == 0) {
            send(QByteArray(hostResponse, hostMsgSize));
            emit handshakeDone(1);
            handshakeStatus = 1;
        }
        if (memcmp(msg, hostResponse, size) == 0) {
            emit handshakeDone(2);
            handshakeStatus = 1;
        }
    }
}


void P2PCommunicator::swapPorts() {
    quint16 tmp            = params.localReadPort;
    params.localReadPort   = params.remoteWritePort;
    params.remoteWritePort = tmp;
}


void P2PCommunicator::send(QByteArray msg) {
    if (!isReady) return;

    writeDatagram(msg, params.remoteHost, params.remoteWritePort);
    qDebug() << "Communicator\tsent\t" << msg;
}


void P2PCommunicator::receive() {
    if (!hasPendingDatagrams()) return;

    quint64 size = pendingDatagramSize();
    QByteArray msg(size, '\0');
    readDatagram(msg.data(), size);
    qDebug() << "Communicator\treceived" << msg;
    if (handshakeStatus == 0) verifyOrder(msg.data(), size);
    else                      emit received(msg);
}