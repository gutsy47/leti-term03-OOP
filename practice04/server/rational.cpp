#include "rational.h"
#include "../common/common.h"


QChar TRational::SEPARATOR = separator;


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
