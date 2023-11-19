#include "mycomplex.h"
#include "../common/common.h"


QChar Complex::SEPARATOR = separator;


Complex::Complex() {
    real = 0;
    image = 0;
}

Complex::Complex(const double& re) {
    real = re;
    image = 0;
}

Complex::Complex(const double& re, const double& im) {
    real = re;
    image = im;
}


Complex::Complex(const QByteArray &arr) {
    int sepInd = (int) arr.indexOf(SEPARATOR.toLatin1());
    real = (int) arr.left(sepInd).toDouble();
    image = (int) arr.right(arr.length() - sepInd - 1).toDouble();
}


/// Overload >> operator
std::istream& operator>> (std::istream& is, Complex& num) {
    is >> num.real >> num.image;
    return is;
}

/// Overload << operator
std::ostream& operator<< (std::ostream& os, Complex num) {
    os << num.real << " + " << num.image << "i";
    return os;
}


QString& operator<< (QString& os, Complex num) {
    os += QString::number(num.real, 'f', 2) + " + " + QString::number(num.image, 'f', 2) + "i";
    return os;
}


QByteArray &operator>> (QByteArray &arr, Complex &num) {
    int sepInd = (int) arr.indexOf(Complex::SEPARATOR.toLatin1());
    sepInd = (int) arr.indexOf(Complex::SEPARATOR.toLatin1(), sepInd + 1);
    num = Complex(arr.left(sepInd));
    arr = arr.right(arr.length() - sepInd - 1);
    return arr;
}


/// Overload + operator
Complex Complex::operator+ (Complex num) const {
    Complex temp;
    temp.real = real + num.real;
    temp.image = image + num.image;
    return temp;
}

/// Overload - operator
Complex Complex::operator- (Complex num) const {
    Complex temp;
    temp.real = real - num.real;
    temp.image = image - num.image;
    return temp;
}

/// Overload * operator
Complex Complex::operator* (Complex num) const {
    Complex temp;
    temp.real = (real * num.real) - (image * num.image);
    temp.image = (real * num.image) + (image * num.real);
    return temp;
}

/// Overload / operator
Complex Complex::operator/ (Complex num) const {
    Complex temp;
    temp.real = (real * num.real + image * num.image) / (num.real * num.real + num.image * num.image);
    temp.image = (image * num.real - real * num.image) / (num.real * num.real + num.image * num.image);
    return temp;
}

/// Overload == operator
bool Complex::operator== (Complex num) const {
    return (real == num.real) && (image == num.image);
}

/// Overload != operator
bool Complex::operator!= (Complex num) const {
    return (real != num.real) || (image != num.image);
}