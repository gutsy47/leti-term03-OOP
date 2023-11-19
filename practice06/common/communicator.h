#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H


#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>


struct TCommParams {
    QHostAddress rHost;
    quint16 rPort;
    QHostAddress sHost;
    quint16 sPort;
};


class TCommunicator : public QUdpSocket {
private:
    Q_OBJECT
    bool ready;
    TCommParams params;

public:
    explicit TCommunicator(TCommParams &, QObject *parent = nullptr);

signals:
    void received(QByteArray);

public slots:
    void send(const QByteArray&);

private slots:
    void receive();
};


#endif // COMMUNICATOR_H
