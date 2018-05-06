#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // Open archive when program starts
    if (argc > 1)
        w.OpenArchive(argv[1]);
    w.show();
    w.show();

    return a.exec();
}
