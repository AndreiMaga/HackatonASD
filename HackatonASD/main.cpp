#include "ui/HackatonASD.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HackatonASD w;
    w.show();
    return a.exec();
}
