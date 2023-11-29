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

    // msg in:
    // filename
    // msg out:
    // isGood, data

    QString answer, answerText;

    // Get filename and open it

    // Get data from file
    // Check data
    bool isGood = true;

    answer << QString().setNum(isGood ? 1 : -1) << answerText;

    // If bad, send answer 0
    if (!isGood) {
        answer << QString().setNum(0);
        comm->send(QByteArray().append(answer.toStdString()));
        return;
    }

    // If good, create DrGraph and send 1;graph;
    // ...
    answer << QString().setNum(1) << answerText;


    comm->send(QByteArray().append(answer.toStdString()));
}
