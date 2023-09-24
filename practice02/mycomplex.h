#ifndef OOP_MYCOMPLEX_H
#define OOP_MYCOMPLEX_H

#include <iostream>

class Complex {
public:
    double real, image;

    Complex();
    Complex(const double&);
    Complex(const double&, const double&);

    friend std::istream& operator>> (std::istream&, Complex&);
    friend std::ostream& operator<< (std::ostream&, Complex);

    Complex operator+ (Complex) const;
    Complex operator- (Complex) const;
    Complex operator* (Complex) const;
    Complex operator/ (Complex) const;

    bool operator== (Complex num) const;
    bool operator!= (Complex num) const;
};


#endif //OOP_MYCOMPLEX_H
