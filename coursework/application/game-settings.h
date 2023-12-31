#ifndef OOP_GAME_SETTINGS_H
#define OOP_GAME_SETTINGS_H


/// Be careful changing settings
/// It may break the game, no invalid settings handlers
struct GameSettings {
    static const int boxAmount = 15;
    static const int boxMin    = 0;
    static const int boxMax    = 10;
    static const int moveLimit = 5;
};


#endif //OOP_GAME_SETTINGS_H
