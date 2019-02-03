#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlRelationalDelegate>

/* Connection parameters */
#define DATABASE_HOSTNAME   "localhost"
#define DATABASE_NAME       "BuilderBase"
#define PORT                5433
#define USER_NAME           "postgres"
#define PASSWORD            "123"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();

    /* Connect to database */
    bool connectToDataBase(QString userName, QString password);

private:
    QSqlDatabase db;

    QString userName;
    QString password;

    bool openDataBase();
    void closeDataBase();
};

#endif // DATABASE_H
