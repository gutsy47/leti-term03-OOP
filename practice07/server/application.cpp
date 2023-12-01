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


/// Update <values> by data from <path>
short TApplication::getValues(const std::string path, std::vector<std::vector<int>> &values) {
    /**
     * Return values
     *  0 Success
     * -1 File Not Found
     * -2 Invalid Input
     * -3 Invalid Size
     * -4 Non-Zero Diagonals
     */

    // Open file. Return -1 if not found
    std::ifstream iFile(path);
    if (!iFile.is_open()) return -1;

    // Get values
    std::string line;
    int sizeX = 0, sizeY = 0;
    while (std::getline(iFile, line)) {
        std::vector<int> row;
        sizeY = 0;
        for (int i = 0; i < line.length(); ++i) {
            if (line[i] == '0' || line[i] == '1') {
                if (i != line.length() - 1 && line[i+1] != ' ') return -2; // Not '0' or '1' value error
                row.push_back(line[i] - '0');
                sizeY++;
            } else if (line[i] != ' ') return -2; // Invalid char error
        }
        if (sizeX > 0 && sizeY != values[sizeX-1].size()) return -3; // Invalid row size
        values.push_back(row);
        sizeX++;
    }
    if (sizeX != sizeY) return -3; // Invalid matrix size
    for (int i = 0; i < sizeX; ++i) if (values[i][i] != 0) return -4; // Invalid diagonals

    iFile.close();
    return 0;
}


void TApplication::receive(QByteArray msg) {
    qDebug() << "TApplication::receive(): \t" << msg;

    // Get values from the file
    std::vector<std::vector<int>> values;
    short response = getValues(
            msg.left(msg.indexOf(separator.toLatin1())).toStdString(),
            values
    );

    QString answer, answerText;
    answer << QString().setNum(response);

    // Bad response. Send error code and return
    if (response != 0) {
        comm->send(QByteArray().append(answer.toStdString()));
        return;
    }

    // Good response.
    // Here we need to do something of those:
    // 1. Send values (no need in DrGraph obj ig)
    // 2. Create drawer or drawing and send it instead

    comm->send(QByteArray().append(answer.toStdString()));
}
