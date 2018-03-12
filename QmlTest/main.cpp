#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "appcore.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qputenv("QT_LABS_CONTROLS_STYLE", QVariant("Material").toByteArray());

    //engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    // Для взаимодействия C++ класса AppCore и QML-интерфейса
    AppCore appCore;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("appCore", &appCore);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
