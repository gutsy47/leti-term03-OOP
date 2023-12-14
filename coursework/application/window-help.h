#ifndef OOP_WINDOW_HELP_H
#define OOP_WINDOW_HELP_H


#include <QDialog>
#include <QLabel>


class HelpWindow : public QDialog {
private:
Q_OBJECT

    QLabel *output;

public:
    HelpWindow(QDialog *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Справка");
        setFixedSize(350, 300);

        output = new QLabel(this);
        output->setGeometry(10, 10, 340, 290);
        output->setStyleSheet("QLabel { font-size : 20 px}");
        output->setAlignment(Qt::AlignTop);
        output->setWordWrap(true);
        output->setText(
            "Изначально перед каждым из них находится общий набор из N (15)"
            " закрытых ящиков с деньгами.\n Сумма денег в каждом ящике - случайная"
            " равномерно распределенная на интервале [S1,S2] (0-10) величина.\n"
            "Игроки поочередно открывают по одному выбранному ящику, узнавая сумму "
            "в нем хранящуюся. Повторно ящики не используются.\nПри этом игрок до"
            " хода другого может взять деньги и закончить свои ходы или продолжить,\n"
            "передав ход сопернику, который видит открытый ящик, но не знает о"
            " взятой сумме.\n Всего может быть сделано по K (5) ходов каждым"
            " игроком. Выиграл тот, у которого денег оказалось больше.\n"
            "- первым ход делает игрок, приложение которого запущено первым,\n"
        );
    }
};


#endif //OOP_WINDOW_HELP_H
