#ifndef RATIONAL_H
#define RATIONAL_H

#include <QString>

class TRational {
private:
    static QChar SEPARATOR;
    double numerator, divisor;

public:
    TRational();
    TRational(const double&);
    TRational(const double&, const double&);
    TRational(const QByteArray&);

    friend QString& operator<< (QString&, TRational);
    friend QByteArray& operator>> (QByteArray&, TRational&);

    TRational operator+ (TRational) const;
    TRational operator- (TRational) const;
    TRational operator* (TRational) const;
    TRational operator/ (TRational) const;

    bool operator== (TRational num) const;
    bool operator!= (TRational num) const;
};

#endif // RATIONAL_H
