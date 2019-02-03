#[[#include]]# "${WINDOW_NAME}.h"
#[[#include]]# <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ${WINDOW_NAME} w;
    w.show();

    return a.exec();
}
