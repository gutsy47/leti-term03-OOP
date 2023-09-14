#include "matrix.h"
#include <cmath>

/// Creates a 3x3 matrix filled with zeros
TMatrix::TMatrix() {
    size = 3;
    values.resize(size, std::vector<number>(size, 0));
}

/// Creates a matrix of custom size filled with zeros
TMatrix::TMatrix(unsigned short size) : size(size) {
    values.resize(size, std::vector<number>(size, 0));
}

void TMatrix::setValues(std::vector<std::vector<number>>& newValues) {
    // Wrong size error
    if (newValues.size() != size) {
        std::cout << "Wrong size. Matrix wasn't updated\n";
        return;
    }

    values = newValues;
}

/// Resizes the matrix and fills new fields with zeros or deletes existing ones if newSize < size
void TMatrix::setSize(unsigned short newSize) {
    // Wrong size error
    if (newSize <= 0) {
        std::cout << "Wrong size. Matrix wasn't updated\n";
        return;
    }

    if (newSize == size) {
        // No changes. Return
        return;
    } else if (newSize < size) {
        // newSize is lower. Resize the matrix
        values.resize(newSize, std::vector<number>(newSize));
        size = newSize;
    } else {
        // newSize is greater. Resize and copy the values
        // Filling existing rows with zeros does not work correctly,
        // So we have to recreate matrix.values manually

        std::vector<std::vector<number>> newValues(newSize, std::vector<number>(newSize, 0));

        // Use size instead of newSize due to size < newSize. New values will stay 0
        for (unsigned short i = 0; i < size; ++i)
            for (unsigned short j = 0; j < size; ++j)
                newValues[i][j] = values[i][j];

        values = newValues;
        size = newSize;
    }
}

/// Returns the current size of the matrix
unsigned short TMatrix::getSize() const {
    return size;
}

/// Replace basic << operator with updated one. Prints the matrix
std::ostream& operator<< (std::ostream& os, TMatrix& matrix) {
    unsigned short N = matrix.getSize();
    std::cout.precision(3);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            os << matrix.values[i][j] << "\t\t";
        }
        std::cout << std::endl;
    }
    return os;
}

/// Transforms matrix to the upper triangular (echelon) form via Gaussian elimination method
void TMatrix::toUpperTriangularForm() {
    // pC - pivot Column; pR - pivot Row
    int rowsUpdated = 0; // Used to check the place where the pivot row goes after swap
    for (int pC = 0; pC < size; ++pC) {

        // Find the first non-zero pivot element in the column. -1 - no non-zero el
        int pR = -1;
        for (int i = pC; i < size; ++i) {
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
        for (int i = pR + 1; i < size; ++i) {
            number factor = values[i][pC] / values[pR][pC];
            for (int j = pC; j < size; ++j) {
                values[i][j] -= values[pR][j] * factor;
                // Have to use round due to periodical fractals (e.g. 5/6 -> smh*10e-16)
                values[i][j] = std::round(values[i][j] * std::pow(10, 5)) / std::pow(10, 5);
            }
        }

        rowsUpdated++;
        if (rowsUpdated == size - 1) break;
    }
}

/// Calculates & returns the determinant of the matrix
number TMatrix::getDeterminant() {
    // Create new matrix and copy values
    TMatrix upperMatrix(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            upperMatrix.values[i][j] = values[i][j];

    // Transform it to the echelon form
    upperMatrix.toUpperTriangularForm();

    // Calculate the determinant & return
    number determinant = 1;
    for (int i = 0; i < size; ++i)
        determinant *= upperMatrix.values[i][i];
    return determinant;
}

/// Calculates and returns rank of the matrix
unsigned int TMatrix::getRank() {
    // Create new matrix and copy values
    TMatrix upperMatrix(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            upperMatrix.values[i][j] = values[i][j];

    // Transform it to the echelon form
    upperMatrix.toUpperTriangularForm();

    // Calculate the rank & return
    unsigned int rank = 0;
    for (int i = 0; i < size; ++i)
        for (int j = i; j < size; ++j)
            if (upperMatrix.values[i][j] != 0) {
                rank++;
                break;
            }
    return rank;
}

/// Transposes the matrix (rows will be cols and cols will be rows)
void TMatrix::transpose() {
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size; ++j)
            std::swap(values[i][j], values[j][i]);
}
