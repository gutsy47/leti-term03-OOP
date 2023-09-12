#include "application.h"
#include "matrix.h"

#include <iostream>
#include <iomanip>

/**
 * Reads the integer input via cin
 * @param[out] variable Reference to a declared variable
 * @param[in] isSpaceSep If true, it does not check the last character of the input for newline
 * @param[in] isUnsigned If true, then negative numbers will lead to an error
 * @return True if input was correct, else false
 */
bool inputInt(int &variable, bool isSpaceSep = false, bool isUnsigned = false) {
    std::cin >> variable;
    if (std::cin.fail() || (isUnsigned && variable < 0) || (isSpaceSep && std::cin.peek() != '\n')) {
        std::cout << "Invalid input\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return false;
    }
    return true;
}

TApplication::TApplication() = default;

/**
 * Executes the program
 * @return 0 if correct exit
 */
int TApplication::execute() {

    // Init the matrix
    int matrixSize;
    std::cout << "<< Enter the size of the matrix:\n>> ";
    while (!inputInt(matrixSize, true, true))
        std::cout << "<< Another try (size must be not negative)...\n>>";
    TMatrix matrix(matrixSize);
    std::cout << "Matrix:\n" << matrix;

    char userChoice;                                // Get command from user
    while (true) {
        if (!menu(userChoice)) continue;         // Error occurred
        if (userChoice == '0') break;               // Exit command

        // All good. Executing
        switch (userChoice) {
            // Print the matrix
            case 'p':
                std::cout << matrix;
                break;

            // Set new size of the matrix
            case 's': {
                std::cout << "<< Enter the size of the matrix:\n>> ";
                while (!inputInt(matrixSize, true, true))
                    std::cout << "<< Another try (size must be not negative)...\n>>";
                matrix.setSize(matrixSize);
                std::cout << "Updated matrix:\n" << matrix;
                break;
            }

            // Set values of the matrix
            case 'i':
                matrix.setValues();
                std::cout << "Updated matrix:\n" << matrix;
                break;


            // Determinant
            case '1':
                std::cout << "Determinant = " << matrix.getDeterminant() << std::endl;
                break;

            // Transpose
            case '2':
                matrix.transpose();
                std::cout << "Matrix's been transposed. Updated matrix:\n" << matrix;
                break;

            // Rank
            case '3':
                std::cout << "Rank = " << matrix.getRank() << std::endl;
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
bool TApplication::menu(char &userChoice) {
    std::cout << "<< Action:\n"
                 "   p. Print the matrix\n"
                 "   i. Set values of the matrix\n"
                 "   s. Set new size of the matrix\n"
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