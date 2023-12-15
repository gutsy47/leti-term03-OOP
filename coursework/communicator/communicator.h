#ifndef OOP_COMMUNICATOR_H
#define OOP_COMMUNICATOR_H


#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>


class P2PCommunicator : public QUdpSocket {
private:
    Q_OBJECT

    static int  hostMsgSize;
    static char hostRequest[];
    static char hostResponse[];

    struct CommParams {
        QHostAddress localHost;
        quint16      localReadPort;
        QHostAddress remoteHost;
        quint16      remoteWritePort;
    }   params;

    short handshakeStatus;
    bool  isReady;

public:
    P2PCommunicator(QHostAddress = QHostAddress::LocalHost, quint16 = 10000, QObject* = nullptr);
    void initHandshake();

private:
    void swapPorts();
    void verifyOrder(const char*, const int);

public slots:
    void send(QByteArray);

private slots:
    void receive();

signals:
    void received(QByteArray);
    void handshakeDone(int);
};


#endif //OOP_COMMUNICATOR_H
