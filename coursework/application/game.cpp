#include "game.h"

Game::Game(int argc, char *argv[]) : QApplication(argc, argv) {
    // TODO: Подключить коммуникатор

    interface = new Interface();
    interface->show();

    // TODO: Обработка перехода хода и т.д.
}
