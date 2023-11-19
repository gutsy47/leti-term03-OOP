#ifndef OOP_TMatrix_H
#define OOP_TMatrix_H

#include "number.h"
#include <iostream>
#include <QString>
#include <vector>


/**
 * @class TMatrix
 * @brief Implementation of matrix
 * Implement an matrix with the following functionality:
 * init, print, calculate the determinant, calculate the rank, transpose
 */
class TMatrix {
public:
    TMatrix();                                         // Creates a 3x3 matrix filled with zeros
    explicit TMatrix(unsigned short, unsigned short);  // Creates a matrix of custom size filled with zeros

    void setValues(std::vector<std::vector<number>>&); // Updates the matrix's values
    void setSize(unsigned short, unsigned short);      // Resizes the matrix (saves old values)
    [[nodiscard]] unsigned short getSizeX() const;     // Returns the current rows size
    [[nodiscard]] unsigned short getSizeY() const;     // Returns the current cols size

    friend QString& operator<< (QString&, TMatrix&);   // Replaces the QString << operator

    void transpose();                                  // Transposes the matrix
    unsigned int getRank();                            // Calculates & returns the rank

protected:
    void toUpperTriangularForm();
    unsigned short sizeX;                    // Row amount
    unsigned short sizeY;                    // Columns amount
    std::vector<std::vector<number>> values; // Values of the matrix. Can be printed & changed via methods
};


#endif //OOP_TMATRIX_H
