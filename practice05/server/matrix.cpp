#include "matrix.h"
#include <cmath>


/// Creates a 3x3 matrix filled with zeros
TMatrix::TMatrix() {
    sizeX = 3;
    sizeY = 3;
    values.resize(sizeX, std::vector<number>(sizeY, 0));
}


/// Creates a matrix of custom size filled with zeros
TMatrix::TMatrix(unsigned short x, unsigned short y) {
    sizeX = x;
    sizeY = y;
    values.resize(sizeX, std::vector<number>(sizeY, 0));
}


void TMatrix::setValues(std::vector<std::vector<number>>& newValues) {
    // Wrong size error
    if (newValues.size() != sizeX && newValues[0].size() != sizeY)  {
        std::cout << "Wrong size. Matrix wasn't updated\n";
        return;
    }

    values = newValues;
}


/// Resizes the matrix and fills new fields with zeros or deletes existing ones if newSize < size
void TMatrix::setSize(unsigned short newX, unsigned short newY) {
    // Wrong size error
    if (newX <= 0 || newY <= 0) {
        std::cout << "Wrong size. Matrix wasn't updated\n";
        return;
    }

    if (newX == sizeX && newY == sizeY) {
        // No changes. Return
        return;
    } else if (newX < sizeX && newY < sizeY) {
        // newSize is lower. Resize the matrix
        values.resize(newX, std::vector<number>(newY));
        sizeX = newX;
        sizeY = newY;
    } else {
        // newSize is greater. Resize and copy the values
        // Filling existing rows with zeros does not work correctly,
        // So we have to recreate matrix.values manually

        std::vector<std::vector<number>> newValues(newX, std::vector<number>(newY, 0));

        // Use size instead of newSize due to size < newSize. New values will stay 0
        for (unsigned short i = 0; i < sizeX; ++i)
            for (unsigned short j = 0; j < sizeY; ++j)
                newValues[i][j] = values[i][j];

        values = newValues;
        sizeX = newX;
        sizeY = newY;
    }
}


/// Returns the current rows amount of the matrix
unsigned short TMatrix::getSizeX() const {
    return sizeX;
}


/// Returns the current rows amount of the matrix
unsigned short TMatrix::getSizeY() const {
    return sizeY;
}


/// Replace QString << operator with updated one.
QString& operator<< (QString& os, TMatrix& matrix) {
    unsigned short rows = matrix.getSizeX();
    unsigned short cols = matrix.getSizeY();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            os << matrix.values[i][j];
            os += "\t";
        }
        os += "\n";
    }
    return os;
}


/// Transforms matrix to the upper triangular (echelon) form via Gaussian elimination method
void TMatrix::toUpperTriangularForm() {
    // pC - pivot Column; pR - pivot Row
    int rowsUpdated = 0; // Used to check the place where the pivot row goes after swap
    for (int pC = 0; pC < sizeX; ++pC) {

        // Find the first non-zero pivot element in the column. -1 - no non-zero el
        int pR = -1;
        for (int i = pC; i < sizeY; ++i) {
            if (values[i][pC] != 0) {
                pR = i;
                break;
            }
        }

        if (pR == -1) continue;

        // Non-zero element found. Swap rows to make the pivot the leading one
        if (pR != rowsUpdated) {
            std::swap(values[rowsUpdated], values[pR]);
            pR = rowsUpdated;
        }

        // Main part of algorithm. Eliminate all non-zero elements below the pivot element
        // The math of it:
        // Factor is how we need to change the subtrahend number to get zero
        // factor = numberBelowThePivot / subtrahendNumber
        // currentElement -= numberBelowTheCurrent * factor
        for (int i = pR + 1; i < sizeX; ++i) {
            number factor = values[i][pC] / values[pR][pC];
            for (int j = pC; j < sizeY; ++j) {
                values[i][j] = values[i][j] - values[pR][j] * factor;
            }
        }

        rowsUpdated++;
        if (rowsUpdated == sizeY - 1) break;
    }
}


/// Calculates and returns rank of the matrix
unsigned int TMatrix::getRank() {
    // Create new matrix and copy values
    TMatrix upperMatrix(sizeX, sizeY);
    for (int i = 0; i < sizeX; ++i)
        for (int j = 0; j < sizeY; ++j)
            upperMatrix.values[i][j] = values[i][j];

    // Transform it to the echelon form
    upperMatrix.toUpperTriangularForm();

    // Calculate the rank & return
    unsigned int rank = 0;
    for (int i = 0; i < sizeX; ++i)
        for (int j = i; j < sizeY; ++j)
            if (upperMatrix.values[i][j] != 0) {
                rank++;
                break;
            }
    return rank;
}


/// Transposes the matrix (rows will be cols and cols will be rows)
void TMatrix::transpose() {
    for (int i = 0; i < sizeX; ++i)
        for (int j = i + 1; j < sizeY; ++j)
            std::swap(values[i][j], values[j][i]);
}