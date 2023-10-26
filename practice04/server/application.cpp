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

    QString answer, s;
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

    int pos = msg.indexOf(separator.toLatin1());
    int msgType = msg.left(pos).toInt();

    switch (msgType) {
        case PRINT_REQUEST:
            s << matrix;
            answer << QString().setNum(PRINT_ANSWER) << s;
            break;
        default:
            return;
    }
    comm->send(QByteArray().append(answer.toStdString()));
//    switch (t) {
//        case PRINT_REQUEST:
//            msg = msg.right(msg.length() - pos - 1);
//            msg >> x;
//            v = p.value(x);
//            s << (QString) x << (QString) v;
//            answer << QString().setNum(PRINT_ANSWER);
//            answer += s;
//            break;
//        case DETERM_REQUEST:
////            p.setPrintMode(EPrintModeClassic);
//            s << p;
//            answer << QString().setNum(PRINT_ANSWER) << s;
//            break;
//        default:
//            return;
//    }'
}
