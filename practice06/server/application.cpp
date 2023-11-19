#include "application.h"


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

    int matrixSize, numType;
    msg >> matrixSize;
    msg >> numType;

    if (numType == D_MODE) {
        std::vector<std::vector<double>> values(matrixSize, std::vector<double>(matrixSize, 0));
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                double num;
                msg >> num;
                values[i][j] = num;
            }
        }
        TSquareMatrix<double> matrix(matrixSize);
        matrix.setValues(values);
        send(msg, matrix);
    } else if (numType == C_MODE) {
        std::vector<std::vector<Complex>> values(matrixSize, std::vector<Complex>(matrixSize, 0));
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                Complex num;
                msg >> num;
                values[i][j] = num;
            }
        }
        TSquareMatrix<Complex> matrix(matrixSize);
        matrix.setValues(values);
        send(msg, matrix);
    } else {
        std::vector<std::vector<TRational>> values(matrixSize, std::vector<TRational>(matrixSize, 0));
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                TRational num;
                msg >> num;
                values[i][j] = num;
            }
        }
        TSquareMatrix<TRational> matrix(matrixSize);
        matrix.setValues(values);
        send(msg, matrix);
    }
}
