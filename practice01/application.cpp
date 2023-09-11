#include "application.h"
#include "number.h"
#include "matrix.h"

#include <iostream>
#include <iomanip>

Application::Application() = default;

/**
 * Executes the program
 * @return 0 if correct exit
 */
int Application::execute() {
    Matrix matrix;
    char userChoice;                                // Get command from user
    while (true) {
        if (!menu(userChoice)) continue;         // Error occurred
        if (userChoice == '0') break;               // Exit command

        // All good. Executing
        switch (userChoice) {
            // Set values of the matrix
            case 'i':
                matrix.set_values();
                std::cout << "Updated matrix:\n" << matrix;
                break;

            // Print the matrix
            case 'p':
                std::cout << matrix;
                break;

            // Determinant
            case '1':
                std::cout << "Determinant = " << matrix.get_determinant() << std::endl;
                break;

            // Transpose
            case '2':
                matrix.transpose();
                std::cout << "Matrix's been transposed. Updated matrix:\n" << matrix;
                break;

            // Rank
            case '3':
                std::cout << "Rank = " << matrix.get_rank() << std::endl;
                break;

            // Runtime error. Unknown command
            default: std::cout << "RuntimeError. Unknown command\n";
        }
        system("pause");
    }
    return 0;
}

/**
 * Prints the menu of commands and reads the user action input via cin
 * @param[out] userChoice Reference to a declared user's choice variable
 * @return True if input was correct, else false (error)
 */
bool Application::menu(char &userChoice) {
    std::cout << "<< Action:\n"
                 "   i. Set values of the matrix\n"
                 "   p. Print the matrix\n"
                 "   1. Calculate determinant\n"
                 "   2. Transpose matrix\n"
                 "   3. Calculate rank\n"
              << std::setw(28) << std::setfill('-') << '\n'
              << std::setfill(' ') <<
              "   0. Exit\n"
              ">> ";
    std::cin >> userChoice;

    // Error handler (i.e. more than one symbol input)
    if (std::cin.fail() || std::cin.get() != '\n') {
        std::cout << "RuntimeError. Unknown command\n";
        std::cin.clear();
        std::cin.ignore(100000, '\n');
        return false;
    }
    return true;
}