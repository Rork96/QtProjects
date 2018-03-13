#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>

class AppCore : public QObject
{
    Q_OBJECT
public:
    explicit AppCore(QObject *parent = 0);

public:
    // Приём данных из qml-интерфейса - Q_INVOKABLE
    // или объявлять как public slots
    Q_INVOKABLE void calck(const QString &msg);
    Q_INVOKABLE QObject *getObjectId() {
        return numberXObj = new QObject();
    };

private:
    QObject *numberXObj;
};

#endif // APPCORE_H
