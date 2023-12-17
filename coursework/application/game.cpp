#include "game.h"


/// Constructor. Inits P2P and GUI
Game::Game(int argc, char *argv[]) : QApplication(argc, argv) {
    communicator = new P2PCommunicator();
    communicator->initHandshake();

    interface = new Interface();
    interface->show();

    connect(communicator, SIGNAL(handshakeDone(int)),   this,      SLOT(handshakeDone(int)));
    connect(communicator, SIGNAL(received(QByteArray)), this,      SLOT(from(QByteArray)));
    connect(interface,    SIGNAL(request(QString)),     this,      SLOT(to(QString)));
    connect(this,         SIGNAL(gameStarted()),        interface, SLOT(startGame()));
    connect(this,         SIGNAL(startWaiting()),       interface, SLOT(waitForTurn()));
}


/// Catches handshake completion signal and starts the game
void Game::handshakeDone(int order) {
    qDebug() << "GameServer\tqueued\t" << order;

    if (order == 1) emit gameStarted();
    else            emit startWaiting();
}


/// Receive a message
void Game::from(const QByteArray &data) {
    interface->answer(QString(data));
}


/// Send a message
void Game::to(const QString &data) {
    communicator->send(QByteArray().append(data.toStdString()));
}
