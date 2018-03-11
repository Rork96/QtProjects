#include "appcore.h"

#include <QDebug>

AppCore::AppCore(QObject *parent) : QObject(parent)
{
}

void AppCore::calck(const QString &msg)
{
    /* * * Приём данных из qml-интерфейса * * */

    qDebug() << msg;

    // Строки ввода
    QObject* numberX = viewer->findChild<QObject*>("numberX");
    QObject* numberY = viewer->findChild<QObject*>("numberY");

    // Поле вывода
    QObject* resultLabel = viewer->findChild<QObject*>("resultLabel");

    // Информацию со строк ввода через свойство text
    QString str1 = (numberX->property("text")).toString();
    QString str2 = (numberY->property("text")).toString();

    qDebug() << str1;
    qDebug() << str2;

    int c = str1.toInt() + str2.toInt();

    qDebug() << QString::number(c);

    // Вывод в поле вывода
    resultLabel->setProperty("text", str1 + " + " + str2 + " = " + QString::number(c));
}
