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
    explicit Interface(QWidget *parent = nullptr);
    ~Interface() override;

private:
    void enableBoxes();
    void disableBoxes();
    QString getMoneyMsg(int);

public slots:
    void startGame();
    void waitForTurn();
    void answer(QString);

private slots:
    void onHelpPressed();
    void onBoxClicked(Box* box);
    void onTakeOrPassPressed();

signals:
    void request(QString);
};


#endif //OOP_INTERFACE_H
