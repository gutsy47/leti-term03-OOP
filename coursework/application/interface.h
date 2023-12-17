#ifndef OOP_INTERFACE_H
#define OOP_INTERFACE_H


#include "box.h"
#include "player.h"
#include "game-settings.h"
#include "window-help.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>


/// Messages for players to communicate with
enum messages {
    PLAYER_TAKE = 1,
    PLAYER_PASS
};


/**
 * @class Interface
 * @brief Represents the player's main GUI
 *
 * Manages the game interface, including boxes, players, and buttons.
 * Handles P2P signals of the game
 */
class Interface : public QWidget {
private:
    Q_OBJECT

    // Boxes
    static const int N = GameSettings::boxAmount;
    Box *boxes[N];

    // Players
    Player player1;
    Player player2;

    // Buttons
    QPushButton *btnTake;
    QPushButton *btnPass;
    QPushButton *btnHelp;

    // Labels
    QLabel *output;

public:
    // Constructor and destructor
    explicit Interface(QWidget *parent = nullptr);
    ~Interface() override;

private:
    void enableBoxes();          // Set the boxes clickable
    void disableBoxes();         // Disable the boxes
    QString getMoneyMsg(int);    // Get the correct declination of the number of coins

public slots:
    void startGame();            // P1 makes the first move
    void waitForTurn();          // P2 waits for the P1's first move
    void answer(QString);        // Make next move

private slots:
    void onHelpPressed();        // Show the help window
    void onBoxClicked(Box* box); // Handle box click, go to Take/Pass part
    void onTakeOrPassPressed();  // Handle Take/Pass click

signals:
    void request(QString);       // Send the message to the P2
};


#endif //OOP_INTERFACE_H
