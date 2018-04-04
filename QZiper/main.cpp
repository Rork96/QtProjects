#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QApplication>

#include "appcore.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Для взаимодействия C++ класса AppCore и QML-интерфейса
    // QScopedPointer автоматичеки удаляет объект класса AppCore из памяти
    // при закрытии программы
    QScopedPointer<AppCore> appCore (new AppCore);
    engine.rootContext()->setContextProperty("appCore", appCore.data());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
