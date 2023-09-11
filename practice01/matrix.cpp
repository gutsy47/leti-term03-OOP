#include "matrix.h"

Matrix::Matrix() {
    unsigned short N = Matrix::get_size();
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            values[i][j] = i + j + 1;
}

void Matrix::set_values() {

}

number * Matrix::get_values() {

}

unsigned short Matrix::get_size() {
    return size;
}

std::ostream& operator<< (std::ostream& os, Matrix& matrix) {
    unsigned short N = Matrix::get_size();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            os << matrix.values[i][j] << ' ';
        std::cout << std::endl;
    }
    return os;
}

int Matrix::get_determinant() {
    return 0;
}

void Matrix::transpose() {

}

unsigned int Matrix::get_rank() {
    return 0;
}
