#ifndef OOP_GAME_H
#define OOP_GAME_H


#include "interface.h"
#include "../communicator/communicator.h"

#include <QObject>
#include <QApplication>


/**
 * @class Game
 * @brief Represents the game application
 *
 * Manages the main actions of the game.
 * Includes Peer2Peer communication between two games
 */
class Game : public QApplication {
private:
    Q_OBJECT
    P2PCommunicator *communicator; // Handle players communication
    Interface       *interface;    // Player interface

public:
    Game(int, char **); // Constructor

public slots:
    void handshakeDone(int);      // Start the game
    void from(const QByteArray&); // Receive a message
    void to(const QString&);      // Send a message

signals:
    void gameStarted();  // Player 1 starts the game
    void startWaiting(); // Player 2 starts waiting
};


#endif //OOP_GAME_H
