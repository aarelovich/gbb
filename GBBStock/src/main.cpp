#include "gbbmain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GBBMain w;
    w.show();

    return a.exec();
}
