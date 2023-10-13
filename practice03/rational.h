#ifndef RATIONAL_H
#define RATIONAL_H

#include <QString>

class TRational {
public:
    double numerator, divisor;

    TRational();
    TRational(const double&);
    TRational(const double&, const double&);

    friend QString& operator<< (QString&, TRational);

    TRational operator+ (TRational) const;
    TRational operator- (TRational) const;
    TRational operator* (TRational) const;
    TRational operator/ (TRational) const;

    bool operator== (TRational num) const;
    bool operator!= (TRational num) const;
};

#endif // RATIONAL_H
