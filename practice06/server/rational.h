#ifndef RATIONAL_H
#define RATIONAL_H

#include <QString>

class TRational {
private:
    static QChar SEPARATOR;
    int numerator, divisor;

public:
    TRational();
    TRational(const int&);
    TRational(const int&, const int&);
    explicit TRational(const QByteArray&);

    friend QString& operator<< (QString&, TRational);
    friend QByteArray& operator>> (QByteArray&, TRational&);

    TRational toProperFraction();

    TRational operator+ (TRational) const;
    TRational operator- (TRational) const;
    TRational operator* (TRational) const;
    TRational operator/ (TRational) const;

    bool operator== (TRational num) const;
    bool operator!= (TRational num) const;
};

#endif // RATIONAL_H
