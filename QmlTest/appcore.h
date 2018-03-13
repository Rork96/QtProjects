#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>

class AppCore : public QObject
{
    Q_OBJECT
    using BaseClass = QObject;
public:
    explicit AppCore(QObject *parent = nullptr);

public:
    // Приём данных из qml-интерфейса - Q_INVOKABLE
    // или объявлять как public slots
    Q_INVOKABLE void calck(QObject *numXObj, QObject *numYObj, QObject *resLblObj);
};

#endif // APPCORE_H
