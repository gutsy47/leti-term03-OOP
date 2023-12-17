#ifndef OOP_COMMUNICATOR_H
#define OOP_COMMUNICATOR_H


#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>


/**
 * @class P2PCommunicator
 * @brief Peer-to-peer communication via UDP socket
 *
 * Provides methods and signals for initiating and handling
 * peer-to-peer communication, including handshakes and messages
 */
class P2PCommunicator : public QUdpSocket {
private:
    Q_OBJECT

    static int  hostMsgSize;    // Size of the message
    static char hostRequest[];  // "Need a host" message
    static char hostResponse[]; // "I'll be the host" message

    struct CommParams {
        QHostAddress localHost;
        quint16      localReadPort;
        QHostAddress remoteHost;
        quint16      remoteWritePort;
    }   params; // Host addresses and ports

    short handshakeStatus; // -1 if not ready, 0 in progress, 1 if done
    bool  isReady;         // True if socket is ready to communicate

public:
    P2PCommunicator(QHostAddress = QHostAddress::LocalHost, quint16 = 10000, QObject* = nullptr);
    void initHandshake();

private:
    void swapPorts();                         // Swap the local and remote ports in this.params
    void verifyOrder(const char*, const int); // Set the order (host or client) based on message

public slots:
    void send(QByteArray); // Send message to the remote

private slots:
    void receive();        // Receive message from the remote

signals:
    void received(QByteArray); // Message received signal
    void handshakeDone(int);   // Host and client knows each other signal
};


#endif //OOP_COMMUNICATOR_H
