#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QQuickWidget>
#include <QSystemTrayIcon>
#include <QQmlContext>

// Custom type for QML
Q_DECLARE_METATYPE(QSystemTrayIcon::ActivationReason)

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/pict/SystemCare.png"));

    QQmlApplicationEngine engine;

    // Register QSystemTrayIcon in Qml
    qmlRegisterType<QSystemTrayIcon>("QSystemTrayIcon", 1, 0, "QSystemTrayIcon");
    // Register a data type in QML (for click on the tray icon)
    qRegisterMetaType<QSystemTrayIcon::ActivationReason>("ActivationReason");
    // Set an icon
    engine.rootContext()->setContextProperty("iconTray", QIcon(":/pict/SystemCare.png"));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
