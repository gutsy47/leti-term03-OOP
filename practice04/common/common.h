#ifndef COMMON_H
#define COMMON_H


#include <QString>


enum messages {
    PRINT_REQUEST = 1,
    PRINT_ANSWER,
    DETERM_REQUEST,
    DETERM_ANSWER
};


extern const QChar separator;


QString &operator<< (QString &, const QString &);


#endif // COMMON_H
