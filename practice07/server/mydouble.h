#ifndef OOP_MYDOUBLE_H
#define OOP_MYDOUBLE_H


#include <QString>
#include "../common/common.h"


inline QString& operator<< (QString& os, double num) {
    os += QString().setNum(num);
    return os;
}


inline QByteArray &operator>> (QByteArray &arr, double &num) {
    int sepInd = (int) arr.indexOf(separator.toLatin1());
    num = arr.left(sepInd).toDouble();
    arr = arr.right(arr.length() - sepInd - 1);
    return arr;
}


#endif //OOP_MYDOUBLE_H
