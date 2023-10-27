#include "rational.h"
#include "../common/common.h"


QChar TRational::SEPARATOR = separator;


TRational::TRational() {
    numerator = 0;
    divisor = 1;
}


TRational::TRational(const int& num) {
    numerator = num;
    divisor = 1;
}


TRational::TRational(const int& num, const int& div) {
    numerator = num;
    divisor = div == 0 ? 1 : div;
}


TRational::TRational(const QByteArray &arr) {
    int sepInd = arr.indexOf(SEPARATOR.toLatin1());
    numerator = arr.left(sepInd).toDouble();
    divisor = arr.right(arr.length() - sepInd - 1).toDouble();
}


QString& operator<< (QString& os, TRational num) {
    if (num.numerator != 0 && num.divisor == 0) {
        os += "DivisionByZeroError";
        return os;
    }
    os += QString().setNum(num.numerator);
    if (num.numerator != 0 && num.divisor != 1) {
        os += "/";
        os += QString().setNum(num.divisor);
    }
    return os;
}


QByteArray &operator>>(QByteArray &arr, TRational &num) {
    int sepInd = arr.indexOf(TRational::SEPARATOR.toLatin1());
    sepInd =  arr.indexOf(TRational::SEPARATOR.toLatin1(), sepInd + 1);
    if (sepInd > 0) {
        num = TRational(arr.left(sepInd));
        arr = arr.right(arr.length() - sepInd - 1);
    }
    return arr;
}


TRational TRational::toProperFraction() {
    // Get grand common divisor (gcd)
    int gcd = numerator;
    int div = divisor;
    while (div != 0) {
        int temp = div;
        div = gcd % div;
        gcd = temp;
    }

    numerator /= gcd;
    divisor /= gcd;

    return *this;
}


TRational TRational::operator+ (TRational num) const {
    TRational temp;
    temp.numerator = numerator * num.divisor + num.numerator * divisor;
    temp.divisor = divisor * num.divisor;
    return temp.toProperFraction();
}


TRational TRational::operator- (TRational num) const {
    TRational temp;
    temp.numerator = numerator * num.divisor - num.numerator * divisor;
    temp.divisor = divisor * num.divisor;
    return temp.toProperFraction();
}


TRational TRational::operator* (TRational num) const {
    TRational temp;
    temp.numerator = numerator * num.numerator;
    temp.divisor = divisor * num.divisor;
    return temp.toProperFraction();
}


TRational TRational::operator/ (TRational num) const {
    TRational temp;
    temp.numerator = numerator * num.divisor;
    temp.divisor = divisor * num.numerator;
    return temp.toProperFraction();
}


// Floating point in bool operators may cause problems
// The reason is the imprecision of the data storage
// Actually, I'll try to fix it
const int MATH_PRECISION = 7;

bool TRational::operator== (TRational num) const {
    double left = double(numerator) / double(divisor);
    double right = double(num.numerator) / double(num.divisor);
    left = std::round(left * std::pow(10, MATH_PRECISION)) / std::pow(10, MATH_PRECISION);
    right = std::round(right * std::pow(10, MATH_PRECISION)) / std::pow(10, MATH_PRECISION);

    return left == right;
}


bool TRational::operator!= (TRational num) const {
    double left = double(numerator) / double(divisor);
    double right = double(num.numerator) / double(num.divisor);
    left = std::round(left * std::pow(10, MATH_PRECISION)) / std::pow(10, MATH_PRECISION);
    right = std::round(right * std::pow(10, MATH_PRECISION)) / std::pow(10, MATH_PRECISION);

    return left != right;
}
