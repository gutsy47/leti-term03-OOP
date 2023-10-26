#include "application.h"
#include "../common/common.h"
#include "matrix.h"
#include "number.h"
#include <vector>


TApplication::TApplication(int argc, char *argv[]) : QCoreApplication(argc, argv) {
    TCommParams pars = {
        QHostAddress("127.0.0.1"), 10000,
        QHostAddress("127.0.0.1"), 10001
    };
    comm = new TCommunicator(pars, this);

    connect(comm, SIGNAL(received(QByteArray)), this, SLOT(receive(QByteArray)));
}


void TApplication::receive(QByteArray msg) {
    qDebug() << "TApplication::receive(): \t" << msg;

    QString answer, answerText;
    std::vector<std::vector<number>> values(3, std::vector<number>(3, 0));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            number num;
            msg >> num;
            values[i][j] = num;
        }
    }
    TMatrix matrix(3);
    matrix.setValues(values);

    int sepInd = msg.indexOf(separator.toLatin1());
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
            answer << QString().setNum(DETERM_ANSWER) << answerText;
            break;
        default:
            return;
    }
    comm->send(QByteArray().append(answer.toStdString()));
}
