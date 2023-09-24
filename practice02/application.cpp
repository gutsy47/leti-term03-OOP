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
    TMatrix matrix;
    char userChoice;
    while (true) {
        // Get command from the keyboard
        if (!menu(userChoice)) continue; // Error occurred
        if (userChoice == '0') break;       // Exit command

        // Execute
        switch (userChoice) {
            // Print the matrix
            case 'p': {
                std::cout << matrix;
                break;
            }

            // Set new size of the matrix
            case 's': {
                std::cout << "<< Enter the size of the matrix:\n>> ";
                int matrixSize;
                while (!inputInt(matrixSize, true, true)  && matrixSize != 0)
                    std::cout << "<< Another try (size must be not negative)...\n>> ";
                matrix.setSize(matrixSize);
                std::cout << "Updated matrix:\n" << matrix;
                break;
            }

            // Set values of the matrix
            case 'i': {
                unsigned int size = matrix.getSize();
                std::vector<std::vector<number>> newValues(size, std::vector<number>(size, 0));

                std::cout << "<< Enter the values\n";
                bool isGood = true; // Flag of input's correctness
                for (int i = 0; i < size; ++i) {
                    for (unsigned int j = 0; j < size; ++j) {
                        number value;
                        if (!(std::cin >> value).fail()) newValues[i][j] = value;
                        else {
                            std::cout << "Invalid input\n";
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                            isGood = false;
                            break;
                        }
                    }
                    if (!isGood) break;
                }

                if (isGood) matrix.setValues(newValues);
                break;
            }


            // Determinant
            case '1': {
                number answer = matrix.getDeterminant();
                std::cout << "Determinant = " << answer << std::endl;
                break;
            }

            // Transpose
            case '2': {
                matrix.transpose();
                std::cout << "Matrix's been transposed. Updated matrix:\n" << matrix;
                break;
            }

            // Rank
            case '3': {
                std::cout << "Rank = " << matrix.getRank() << std::endl;
                break;
            }

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