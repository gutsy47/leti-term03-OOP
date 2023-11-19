#ifndef OOP_TSquareMatrix_H
#define OOP_TSquareMatrix_H

#include "number.h"
#include "matrix.h"
#include <vector>


/**
 * @class TSquareMatrix
 * @brief Implementation of square matrix
 * Implement an square matrix with the following functionality:
 * init, print, calculate the determinant, calculate the rank, transpose
 */
class TSquareMatrix : public TMatrix {
public:
    explicit TSquareMatrix(unsigned short);       // Creates a matrix of custom size filled with zeros

    void setSize(unsigned short);                 // Resizes the matrix (saves old values)
    [[nodiscard]] unsigned short getSize() const; // Returns the current size

    number getDeterminant();                      // Calculates & returns the determinant
};


#endif //OOP_TSQUAREMATRIX_H
