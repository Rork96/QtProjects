#include "appcore.h"

#include <QDebug>

AppCore::AppCore(QObject *parent) :
        BaseClass(parent)
{
}

void AppCore::calck(QObject *numXObj, QObject *numYObj, QObject *resLblObj)
{
    /* * * Приём данных из qml-интерфейса * * */

    // Информация со строк ввода через свойство text
    double x = (numXObj->property("text")).toDouble();
    double y = (numYObj->property("text")).toDouble();

    // Вывод в поле вывода
    resLblObj->setProperty("text", "Результат: " + QString::number(x + y));
}
