#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // Открытие файла при старте программы
    if (argc > 1)
        w.Open(argv[1]);
    w.show();

    return a.exec();
}
