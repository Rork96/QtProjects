#include "appcore.h"

#include <QDebug>

AppCore::AppCore(QObject *parent) : QObject(parent)
{
}

void AppCore::calck(const QString &msg)
{
    /* * * Приём данных из qml-интерфейса * * */

    qDebug() << "Сообщение: " << msg;

    // Строки ввода
    QObject* numberX = this->findChild<QObject*>("numberX");
    QObject* numberY = this->findChild<QObject*>("numberY");

    // Поле вывода
    QObject* resultLabel = this->findChild<QObject*>("resultLabel");

    qDebug() << numberX;
    qDebug() << "... Инициализация переменных ...";

    // Информацию со строк ввода через свойство text
    QString str1 = (numberX->property("text")).toString();
    qDebug() << "Строка 1: " << str1;
    QString str2 = (numberY->property("text")).toString();
    qDebug() << "Строка 2: " << str2;

    int c = str1.toInt() + str2.toInt();

    qDebug() << "Результат: " << QString::number(c);

    // Вывод в поле вывода
    resultLabel->setProperty("text", str1 + " + " + str2 + " = " + QString::number(c));
}
