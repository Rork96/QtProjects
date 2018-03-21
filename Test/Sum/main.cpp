#include "sum_widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sum_widget w;
    w.show();

    return a.exec();
}
