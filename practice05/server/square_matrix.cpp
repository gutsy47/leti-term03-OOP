#include "square_matrix.h"


/// Creates a matrix of custom size filled with zeros
TSquareMatrix::TSquareMatrix(unsigned short size) {
     sizeX = size;
     sizeY = size;
     values.resize(sizeX, std::vector<number>(sizeY, 0));
}


/// Resizes the matrix and fills new fields with zeros or deletes existing ones if newSize < size
void TSquareMatrix::setSize(unsigned short newSize) {
    // Wrong size error
    if (newSize <= 0) {
        std::cout << "Wrong size. Matrix wasn't updated\n";
        return;
    }

    if (newSize == sizeX) {
        // No changes. Return
        return;
    } else if (newSize < sizeX) {
        // newSize is lower. Resize the matrix
        values.resize(newSize, std::vector<number>(newSize));
        sizeX = newSize;
        sizeY = newSize;
    } else {
        // newSize is greater. Resize and copy the values
        // Filling existing rows with zeros does not work correctly,
        // So we have to recreate matrix.values manually

        std::vector<std::vector<number>> newValues(newSize, std::vector<number>(newSize, 0));

        // Use size instead of newSize due to size < newSize. New values will stay 0
        for (unsigned short i = 0; i < sizeX; ++i)
            for (unsigned short j = 0; j < sizeX; ++j)
                newValues[i][j] = values[i][j];

        values = newValues;
        sizeX = newSize;
        sizeY = newSize;
    }
}

/// Returns the current size of the matrix
unsigned short TSquareMatrix::getSize() const {
    return sizeX;
}


/// Calculates & returns the determinant of the matrix
number TSquareMatrix::getDeterminant() {
    // Create new matrix and copy values
    TSquareMatrix upperMatrix(sizeX);
    for (int i = 0; i < sizeX; ++i)
        for (int j = 0; j < sizeX; ++j)
            upperMatrix.values[i][j] = values[i][j];

    // Transform it to the echelon form
    upperMatrix.toUpperTriangularForm();

    // Calculate the determinant & return
    number determinant(1);
    for (int i = 0; i < sizeX; ++i)
        determinant = determinant * upperMatrix.values[i][i];
    return determinant;
}
