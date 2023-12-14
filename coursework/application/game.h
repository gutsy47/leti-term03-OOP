#ifndef OOP_GAME_H
#define OOP_GAME_H


#include "box.h"
#include "player.h"
#include "interface.h"
#include "../communicator.h"

#include <QObject>
#include <QApplication>


class Game : public QApplication {
private:
    Q_OBJECT

public:
    Game(int, char **);
};


#endif //OOP_GAME_H
