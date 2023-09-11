#ifndef OOP_MATRIX_H
#define OOP_MATRIX_H

#include "number.h"

/**
 * @class Tree
 * @brief Implementation of AVL-Tree
 * Implement an AVL-Tree with the following functionality:
 * insert, search, delete node/tree, output to ostream
 * @example main.cpp
 */
class Matrix {
public:
    void set_values();
    int get_determinant();
    void transpose();
    unsigned int get_rank();
    number * get_values();

private:
    static const unsigned short size = 1;
    number values[size][size];
};


#endif //OOP_MATRIX_H
