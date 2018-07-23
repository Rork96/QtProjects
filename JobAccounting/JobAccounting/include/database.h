#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlRelationalDelegate>
#include <QSettings>

/* Connection parameters */
#define DATABASE_NAME       "JobAccounting"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();

    /* Connect to database */
    bool connectToDataBase(QString userName, QString password, int &rights);

private:
    QSqlDatabase db;
    QSettings *set;

    QString host;
    int port;

    QString userName;
    QString password;
    int rights = 0; // "rwud" - 1368; read only - 1; write only - 3, full access - 18

    bool openDataBase(int &rights);
    void closeDataBase();
    void loadConnectionSettings();  // Load settings
};

#endif // DATABASE_H
