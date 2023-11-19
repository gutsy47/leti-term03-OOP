#ifndef APPLICATION_H
#define APPLICATION_H


#include <QObject>
#include <QCoreApplication>

#include "square_matrix.h"
#include "rational.h"
#include "mycomplex.h"
#include "mydouble.h"

#include "../common/common.h"
#include "../common/communicator.h"

#include <vector>


class TApplication : public QCoreApplication {
private:
    Q_OBJECT
    TCommunicator *comm;

    template <class number>
    void send(QByteArray&, TSquareMatrix<number>&);

public:
    TApplication(int, char **);

signals:

public slots:
    void receive(QByteArray);
};


template <class number>
void TApplication::send(QByteArray &msg, TSquareMatrix<number> &matrix) {
    QString answer, answerText;
    int sepInd = (int) msg.indexOf(separator.toLatin1());
    int request = msg.left(sepInd).toInt();

    switch (request) {
        case PRINT_REQUEST:
            answerText << matrix;
            answer << QString().setNum(PRINT_ANSWER) << answerText;
            break;
        case DETERM_REQUEST:
            answerText << matrix.getDeterminant();
            answer << QString().setNum(DETERM_ANSWER) << answerText;
            break;
        case RANK_REQUEST:
            answerText += std::to_string(matrix.getRank());
            answer << QString().setNum(RANK_ANSWER) << answerText;
            break;
        case TRANSPOSE_REQUEST:
            matrix.transpose();
            answerText << matrix;
            answer << QString().setNum(TRANSPOSE_ANSWER) << answerText;
            break;
        default:
            return;
    }
    comm->send(QByteArray().append(answer.toStdString()));
}


#endif // APPLICATION_H
