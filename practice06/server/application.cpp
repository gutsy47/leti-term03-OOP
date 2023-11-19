#include "application.h"
#include "../common/common.h"
#include "square_matrix.h"
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


QByteArray &operator>> (QByteArray &arr, int &num) {
    int sepInd = (int) arr.indexOf(separator.toLatin1());
    if (sepInd > 0) {
        num = arr.left(sepInd).toInt();
        arr = arr.right(arr.length() - sepInd - 1);
    }
    return arr;
}


void TApplication::receive(QByteArray msg) {
    qDebug() << "TApplication::receive(): \t" << msg;

    int matrixSize;
    msg >> matrixSize;
    std::vector<std::vector<number>> values(matrixSize, std::vector<number>(matrixSize, 0));
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            number num;
            msg >> num;
            values[i][j] = num;
        }
    }
    TSquareMatrix matrix(matrixSize);
    matrix.setValues(values);

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
