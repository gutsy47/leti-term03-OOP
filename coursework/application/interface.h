#ifndef OOP_INTERFACE_H
#define OOP_INTERFACE_H


#include "box.h"
#include "game-settings.h"
#include "window-help.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>


class Interface : public QWidget {
private:
    Q_OBJECT

    // Boxes
    Box *boxes[GameSettings::boxAmount];

    // Buttons
    QPushButton *btnTake;
    QPushButton *btnPass;
    QPushButton *btnHelp;

    // Labels
    QLabel *output;

    // States
    bool isBoxChosen;

public:
    explicit Interface(QWidget *parent = nullptr);
    ~Interface() override;

private:
    QString getBoxClickedMessage(int);

public slots:
    void onBoxClicked(Box* box);
    void showHelp();
};


#endif //OOP_INTERFACE_H
