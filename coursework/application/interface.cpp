#include "interface.h"


Interface::Interface(QWidget *parent) : QWidget(parent) {
    const int N = GameSettings::boxAmount;
    int windowWidth = 90 * (N / 3 + N % 3);

    setWindowTitle("Курсовая Работа. Вариант #13");
    setFixedSize(windowWidth, 400);

    // TODO: Ожидание игрока

    // Text window
    output = new QLabel(this);
    output->setGeometry(windowWidth / 2 - 100, 285, 210, 60);
    output->setStyleSheet("QLabel { background-color : black; color : white; font-size : 20 px}");
    output->setAlignment(Qt::AlignCenter);

    // Create action buttons and hide them
    btnTake = new QPushButton("Взять", this);
    btnPass = new QPushButton("Дальше", this);
    btnTake->setStyleSheet("QPushButton { background-color : #00AA00; color : white; font-size: 20px}");
    btnPass->setStyleSheet("QPushButton { background-color : #FF0000; color : white; font-size: 20px}");
    btnTake->setGeometry(windowWidth / 2 - 100, 350, 100, 30);
    btnPass->setGeometry(windowWidth / 2 + 10, 350, 100, 30);
    btnTake->hide();
    btnPass->hide();

    // Create help button
    btnHelp = new QPushButton("Rules", this);
    btnHelp->setGeometry(windowWidth - 65, 365, 60, 30);
    connect(btnHelp, SIGNAL(pressed()), this, SLOT(showHelp()));

    // Create 2 rows of boxes
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
    }
    isBoxChosen = false;

    // TODO: Переход хода
}


Interface::~Interface() {
    for (auto *box : boxes) delete box;
    delete btnTake;
    delete btnPass;
    delete btnHelp;
    delete output;
}


/// Return the correct declination of the number of coins in the box
QString Interface::getBoxClickedMessage(int value) {
    int lastDigit = value % 10;
    int preLastDigit = (value / 10) % 10;

    if (preLastDigit == 1) return QString("%1 монет").arg(value);
    else if (lastDigit == 1) return QString("%1 монета").arg(value);
    else if (lastDigit >= 2 && lastDigit <= 4) return QString("%1 монеты").arg(value);
    else return QString("%1 монет").arg(value);
}


/// Handle box click
void Interface::onBoxClicked(Box *box) {
    // The choice was already made.
    if (isBoxChosen) {
        output->setText(output->text() + QString("\nВы уже выбрали коробку."));
        return;
    }

    // The box was already open. Reset
    if (box->isOpen()) {
        output->setText("Коробка уже была открыта.\nВыберите другую");
        return;
    }

    // The box was not opened. Update
    box->setOpen(true);
    isBoxChosen = true;
    QString arg = getBoxClickedMessage(box->getValue());
    output->setText(QString("В коробке %1\nВзять или продолжить?").arg(arg));
    btnTake->show();
    btnPass->show();
}


/// Open a window with game rules
void Interface::showHelp() {
    HelpWindow *help = new HelpWindow();
    help->exec();
}