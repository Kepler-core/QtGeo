#include "QGeometry.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGeometry w;
    w.show();
    return a.exec();
}
