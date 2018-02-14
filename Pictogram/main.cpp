#include "pictogram.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Pictogram w;
    w.show();

    return a.exec();
}
