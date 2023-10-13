#include "rational.h"
#include <QString>

TRational::TRational() {
    numerator = 0;
    divisor = 1;
}


TRational::TRational(const double& num) {
    numerator = num;
    divisor = 1;
}


TRational::TRational(const double& num, const double& div) {
    numerator = num;
    divisor = div == 0 ? 1 : div;
}


QString& operator<< (QString& os, TRational num) {
    os += QString().setNum(num.numerator);
    os += "/";
    os += QString().setNum(num.divisor);
    return os;
}


TRational TRational::operator+ (TRational num) const {
    TRational temp;
    temp.numerator = numerator * num.divisor + num.numerator * divisor;
    temp.divisor = divisor * num.divisor;
    return temp;
}


TRational TRational::operator- (TRational num) const {
    TRational temp;
    temp.numerator = numerator * num.divisor - num.numerator * divisor;
    temp.divisor = divisor * num.divisor;
    return temp;
}


TRational TRational::operator* (TRational num) const {
    TRational temp;
    temp.numerator = numerator * num.numerator;
    temp.divisor = divisor * num.divisor;
    return temp;
}


TRational TRational::operator/ (TRational num) const {
    TRational temp;
    temp.numerator = numerator * num.divisor;
    temp.divisor = divisor * num.numerator;
    return temp;
}


bool TRational::operator== (TRational num) const {
    return (numerator / divisor) == (num.numerator / num.divisor);
}


bool TRational::operator!= (TRational num) const {
    return (numerator / divisor) != (num.numerator / num.divisor);
}
