#ifndef OOP_MATRIX_H
#define OOP_MATRIX_H

#include "number.h"
#include <iostream>

/**
 * @class Matrix
 * @brief Implementation of square matrix
 * Implement an square matrix with the following functionality:
 * init, print, calculate the determinant, calculate the rank, transpose
 */
class Matrix {
public:
    Matrix();
    void set_values();
    number * get_values();
    static unsigned short get_size();
    friend std::ostream& operator<< (std::ostream&, Matrix&);
    int get_determinant();
    void transpose();
    unsigned int get_rank();

private:
    static const unsigned short size = 3;
    number values[size][size]{};
};


#endif //OOP_MATRIX_H
