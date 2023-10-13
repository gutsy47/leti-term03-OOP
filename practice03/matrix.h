#ifndef OOP_TMatrix_H
#define OOP_TMatrix_H

#include "number.h"
#include <iostream>
#include <QString>
#include <vector>


/**
 * @class TMatrix
 * @brief Implementation of square matrix
 * Implement an square matrix with the following functionality:
 * init, print, calculate the determinant, calculate the rank, transpose
 */
class TMatrix {
public:
    TMatrix();                                                  // Creates a 3x3 matrix filled with zeros
    explicit TMatrix(unsigned short);                           // Creates a matrix of custom size filled with zeros

    void setValues(std::vector<std::vector<number>>&);          // Updates the matrix's values
    void setSize(unsigned short);                               // Resizes the matrix (saves old values)
    [[nodiscard]] unsigned short getSize() const;               // Returns the current size

    friend QString& operator<< (QString&, TMatrix&);            // Replaces the QString << operator

    number getDeterminant();                                    // Calculates & returns the determinant
    void transpose();                                           // Transposes the matrix
    unsigned int getRank();                                     // Calculates & returns the rank

protected:
    void toUpperTriangularForm();

private:
    unsigned short size;                        // Size of the matrix. Can be gotten & changed via methods
    std::vector<std::vector<number>> values;    // Values of the matrix. Can be printed & changed via methods
};


#endif //OOP_TMATRIX_H
