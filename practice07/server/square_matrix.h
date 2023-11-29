#ifndef OOP_TSquareMatrix_H
#define OOP_TSquareMatrix_H

#include "matrix.h"
#include <vector>


/**
 * @class TSquareMatrix
 * @brief Implementation of square matrix
 * Implement an square matrix with the following functionality:
 * init, print, calculate the determinant, calculate the rank, transpose
 */
template <class number>
class TSquareMatrix : public TMatrix<number> {
public:
    explicit TSquareMatrix(unsigned short size) : TMatrix<number>(size, size) {}       // Creates a matrix of custom size filled with zeros

    void setSize(unsigned short);                 // Resizes the matrix (saves old values)
    [[nodiscard]] unsigned short getSize() const; // Returns the current size

    number getDeterminant();                      // Calculates & returns the determinant
};


/// Resizes the matrix and fills new fields with zeros or deletes existing ones if newSize < size
template <class number>
void TSquareMatrix<number>::setSize(unsigned short newSize) {
    TMatrix<number>::setSize(newSize, newSize);
}

/// Returns the current size of the matrix
template <class number>
unsigned short TSquareMatrix<number>::getSize() const {
    return TMatrix<number>::getSizeX();
}


/// Calculates & returns the determinant of the matrix
template <class number>
number TSquareMatrix<number>::getDeterminant() {
    // Create new matrix and copy values
    TSquareMatrix upperMatrix(this->sizeX);
    for (int i = 0; i < this->sizeX; ++i)
        for (int j = 0; j < this->sizeX; ++j)
            upperMatrix.values[i][j] = this->values[i][j];

    // Transform it to the echelon form
    upperMatrix.toUpperTriangularForm();

    // Calculate the determinant & return
    number determinant(1);
    for (int i = 0; i < this->sizeX; ++i)
        determinant = determinant * upperMatrix.values[i][i];
    return determinant;
}


#endif //OOP_TSQUAREMATRIX_H
