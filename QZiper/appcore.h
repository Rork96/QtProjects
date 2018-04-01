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
    // Receive data from qml - Q_INVOKABLE
    // or public slots
    Q_INVOKABLE void compress(QString File, QString Dir); // Compress dir
};

#endif // APPCORE_H
