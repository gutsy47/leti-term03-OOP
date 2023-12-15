#include "interface.h"


const QChar separator(';');
QString &operator>> (QString &str, const QString &other) {
    if (!str.isEmpty()) str.append(separator);
    str += other;
    return str;
}

/// Generate an interface with disabled and hidden buttons. Waiting for second player
Interface::Interface(QWidget *parent) : QWidget(parent) {
    int windowWidth = 90 * (N / 3 + N % 3);

    setWindowTitle("Курсовая Работа. Вариант #13");
    setFixedSize(windowWidth, 400);

    // Text window
    output = new QLabel(this);
    output->setGeometry(windowWidth / 2 - 100, 285, 210, 60);
    output->setStyleSheet("QLabel { background-color : black; color : white; font-size : 20 px}");
    output->setAlignment(Qt::AlignCenter);
    output->setText("Ждём второго игрока...");

    // Create action buttons and hide them
    btnTake = new QPushButton("Взять", this);
    btnPass = new QPushButton("Дальше", this);
    btnTake->setStyleSheet("QPushButton { background-color : #00AA00; color : white; font-size: 20px}");
    btnPass->setStyleSheet("QPushButton { background-color : #FF0000; color : white; font-size: 20px}");
    btnTake->setGeometry(windowWidth / 2 - 100, 350, 100, 30);
    btnPass->setGeometry(windowWidth / 2 + 10, 350, 100, 30);
    btnTake->hide();
    btnPass->hide();
    connect(btnTake, SIGNAL(pressed()), this, SLOT(onTakeOrPassPressed()));
    connect(btnPass, SIGNAL(pressed()), this, SLOT(onTakeOrPassPressed()));

    // Create help button
    btnHelp = new QPushButton("Rules", this);
    btnHelp->setGeometry(windowWidth - 65, 365, 60, 30);
    connect(btnHelp, SIGNAL(pressed()), this, SLOT(onHelpPressed()));

    // Create 3 rows of boxes and hide them
    for (int i = 0; i < N; ++i) {
        // Create new Box and set value
        boxes[i] = new Box(this);
        boxes[i]->setRandomValue();

        // Draw boxes in three rows
        if (i < N / 3) boxes[i]->draw(i * 90 + 5, 20);
        else if (i < 2 * N / 3) boxes[i]->draw((i - N / 3) * 90 + 5, 110);
        else boxes[i]->draw((i - 2 * N / 3) * 90 + 5, 200);

        // Each box is button. Connect box's signal with slot
        connect(
            boxes[i], &Box::clicked,
            this, [this, i]() { this->onBoxClicked(boxes[i]); }
        );

        boxes[i]->setEnabled(false);
    }

    // Create players
    player1 = Player();
    player2 = Player();
}


/// Destructor
Interface::~Interface() {
    for (auto *box : boxes) delete box;
    delete btnTake;
    delete btnPass;
    delete btnHelp;
    delete output;
}


/// Show updated boxes
void Interface::enableBoxes() {
    for (auto *box : boxes) if (!box->isOpen()) box->setEnabled(true);
}


/// Hide boxes
void Interface::disableBoxes() {
    for (auto *box : boxes) box->setEnabled(false);
}


/// Return the correct declination of the number of coins in the box
QString Interface::getMoneyMsg(int value) {
    int lastDigit = value % 10;
    int preLastDigit = (value / 10) % 10;

    if (preLastDigit == 1) return QString("%1 монет").arg(value);
    else if (lastDigit == 1) return QString("%1 монета").arg(value);
    else if (lastDigit >= 2 && lastDigit <= 4) return QString("%1 монеты").arg(value);
    else return QString("%1 монет").arg(value);
}


/// Player 2 joined. Start the game
void Interface::startGame() {
    output->setText(QString("Игра начата!\nВыберите коробку (ходов: %1)").arg(player1.getMovesLeft()));
    enableBoxes();
}


/// Wait for player to choose
void Interface::waitForTurn() {
    output->setText("Ход противника\nОжидайте...");
    disableBoxes();
}


/// Answer the request
void Interface::answer(QString data) {
    qDebug() << "Interface\treceived" << data;

    // Parse the message
    QStringList dataList = data.split(separator);
    int messageType = dataList[0].toInt();
    int player2Info = dataList[1].toInt();
    for (int i = 0; i < N; ++i) {
        boxes[i]->setOpen(dataList[2 + i*2].toInt());
        boxes[i]->setValue(dataList[2 + i*2 + 1].toInt());
    }

    // Update the Players
    if (messageType == PLAYER_TAKE) {
        player2.setMoney(player2Info);
        player2.setMovesLeft(0);
    }
    if (messageType == PLAYER_PASS)
        player2.setMovesLeft(player2Info);

    // Update the GUI
    QString message;
    if (messageType == PLAYER_TAKE) message = "Противник взял деньги\n";
    if (messageType == PLAYER_PASS) message = "Противник не взял деньги\n";

    // New round if some moves left else wait 'till the Pl2 ends
    if (player1.getMovesLeft() > 0) {
        enableBoxes();
        message += QString("Выберите коробку (ходов: %1)").arg(player1.getMovesLeft());
    } else {
        disableBoxes();
        if (player2.getMovesLeft() > 0) {
            message += "Ход противника";
        } else {
            int m1 = player1.getMoney(), m2 = player2.getMoney();
            message = m1 > m2 ? "Вы выиграли!" : "Вы проиграли!";
            message += QString("\nСчёт - %1:%2").arg(m1).arg(m2);
        }
    }

    output->setText(message);
}


/// Open a window with game rules
void Interface::onHelpPressed() {
    HelpWindow *help = new HelpWindow();
    help->exec();
}


/// Handle box click
void Interface::onBoxClicked(Box *box) {
    // Update data
    player1.setMoney(box->getValue());
    player1.move();
    box->setOpen(true);
    disableBoxes();

    // Update GUI
    QString message = QString("В коробке %1\n").arg(getMoneyMsg(box->getValue()));
    if (player1.getMovesLeft() > 0) {
        message += "Взять или продолжить?";
        btnTake->show();
        btnPass->show();
    } else {
        message += "Ходы закончились!\n";
        if (player2.getMovesLeft() > 0) {
            message += "Ход противника";
        } else {
            int m1 = player1.getMoney(), m2 = player2.getMoney();
            message += m1 > m2 ? "Вы выиграли!" : "Вы проиграли!";
            message += QString("\nСчёт - %1:%2").arg(m1).arg(m2);
        }
        QString data;
        data >> QString().setNum(PLAYER_TAKE);
        data >> QString().setNum(player1.getMoney());
        for (auto *el : boxes) data >> QString().setNum(el->isOpen()) >> QString().setNum(el->getValue());
        emit (request(data));
    }
    output->setText(message);
}


/// Send the request
void Interface::onTakeOrPassPressed() {
    QString data;
    auto *btn = (QPushButton*) sender();

    // Hide GUI while waiting.
    btnTake->hide();
    btnPass->hide();
    disableBoxes();

    // Set the data, create output
    QString message;
    if (btn == btnTake) {
        player1.setMovesLeft(0);
        data >> QString().setNum(PLAYER_TAKE);
        data >> QString().setNum(player1.getMoney());

        message = "Вы взяли деньги\n";
        if (player2.getMovesLeft() > 0) {
            message += "Ход противника";
        } else {
            int m1 = player1.getMoney(), m2 = player2.getMoney();
            message += m1 > m2 ? "Вы выиграли!" : "Вы проиграли!";
            message += QString("\nСчёт - %1:%2").arg(m1).arg(m2);
        }
    }
    if (btn == btnPass) {
        data >> QString().setNum(PLAYER_PASS);
        data >> QString().setNum(player1.getMovesLeft());

        message = "Вы не взяли деньги\n" + QString(player2.getMovesLeft() > 0 ? "Ход противника" : "");
    }
    for (auto *box : boxes) data >> QString().setNum(box->isOpen()) >> QString().setNum(box->getValue());
    output->setText(message);

    // Send the message
    if (player2.getMovesLeft() > 0) {
        emit request(data);
    } else {
        if (player1.getMovesLeft() == 0) emit (request(data));
        else                             enableBoxes();
    }
}