#include "generatesignal.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    generateSignal w;
    w.show();
    return a.exec();
}
