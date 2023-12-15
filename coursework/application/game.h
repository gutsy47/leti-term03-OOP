#ifndef OOP_GAME_H
#define OOP_GAME_H


#include "interface.h"
#include "../communicator/communicator.h"

#include <QObject>
#include <QApplication>


class Game : public QApplication {
private:
    Q_OBJECT
    P2PCommunicator *communicator;
    Interface       *interface;

public:
    Game(int, char **);

public slots:
    void handshakeDone(int);
    void from(const QByteArray&);
    void to(const QString&);

signals:
    void gameStarted();
    void startWaiting();
};


#endif //OOP_GAME_H
