#ifndef OOP_WINDOW_HELP_H
#define OOP_WINDOW_HELP_H


#include <QDialog>
#include <QLabel>


/**
 * @class HelpWindow
 * @brief Represents a help dialog window in the game
 *
 * Simply creates a window with game rules text
 */
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
            "Для начала игры необходимо два игрока.\n\n"
            "Перед вами будет некоторое количество коробок с деньгами. "
            "Открывая ящик вы узнаете количество денег в нем. "
            "Вы можете либо взять деньги и закончить свои ходы, "
            "либо передать ход другому игроку, не забирая деньги.\n"
            "Правила:\n"
            " - Первый ход делает игрок, приложение которого было запущено первым;\n"
            " - Игра заканчивается, когда оба игрока взяли деньги либо потратили все ходы;\n"
            " - Потратив все ходы, вы автоматически забираете деньги из последнего открытого ящика;\n"
            " - Побеждает тот игрок, который забрал большее число денег;\n"
            " - Коробку можно открыть только один раз."
        );
    }
};


#endif //OOP_WINDOW_HELP_H
