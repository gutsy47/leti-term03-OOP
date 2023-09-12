#include "matrix.h"

/// Creates a 3x3 matrix filled with zeros
TMatrix::TMatrix() {
    size = 3;
    values.resize(size, std::vector<number>(size, 0));
}

/// Creates a matrix of custom size filled with zeros
TMatrix::TMatrix(unsigned short size) : size(size) {
    values.resize(size, std::vector<number>(size, 0));
}

void TMatrix::setValues() {

}

/// Resizes the matrix and fills new fields with zeros or deletes existing ones if newSize < size
void TMatrix::setSize(unsigned short newSize) {
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
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            os << matrix.values[i][j] << ' ';
        std::cout << std::endl;
    }
    return os;
}

/// Calculates and returns determinant of the matrix
int TMatrix::getDeterminant() {
    return 0;
}

/// Transposes the matrix (rows will be cols and cols will be rows)
void TMatrix::transpose() {

}

/// Calculates and returns rank of the matrix
unsigned int TMatrix::getRank() {
    return 0;
}
