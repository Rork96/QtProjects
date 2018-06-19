#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

#include <QDir>

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_HOSTNAME   "localhost"
#define DATABASE_NAME       "postgres"
#define PORT                5432
#define USER_NAME           "postgres"
#define PASSWORD            "123"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();

    /* Подключение к базе данных и вставка записей в таблицу
     * */
    bool connectToDataBase(QString userName, QString password);

private:
    QSqlDatabase db;

    QString userName;
    QString password;

    /* Методы для работы с базой данных
     * */
    bool openDataBase();
    void closeDataBase();
};

#endif // DATABASE_H
