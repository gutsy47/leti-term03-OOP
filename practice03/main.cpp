#include "interface.h"
#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Input matrix size
    bool isGood;
    QString userInput = QInputDialog::getText(nullptr, "Matrix size", "Enter size: ", QLineEdit::Normal, "", &isGood);

    if (isGood && !userInput.isEmpty()) {
        int size = userInput.toInt(&isGood);

        // The matrix size is now limited to 5.
        // We can easily remove this limitation by adding the ability to expand the window,
        // but for educational purposes this does not matter
        if (size > 5) {
            QMessageBox::critical(nullptr, "Error #1", "Size is too big");
            return -1;
        }

        // Size is not negative
        if (size < 0) {
            QMessageBox::critical(nullptr, "Error #2", "Size is negative");
            return -2;
        }

        // Some weird stuff in input
        if (!isGood) {
            QMessageBox::critical(nullptr, "Error #3", "Wrong input");
            return -3;
        }

        // Create and show interface, execute app
        TInterface w(nullptr, size);
        w.show();
        return a.exec(); // NOLINT(*-static-accessed-through-instance)
    }

    return 0; // User closed the input window
}
