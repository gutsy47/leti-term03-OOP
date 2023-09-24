#include "mycomplex.h"

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


