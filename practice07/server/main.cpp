#include "application.h"

int main(int argc, char *argv[]) {
    TApplication a(argc, argv);
    a.send();
    return a.exec();
}
