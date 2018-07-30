#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlRelationalDelegate>
#include <QSettings>

/* Connection parameters */
#define DATABASE_NAME       "JobAccounting"

// Tables and columns
#define MAIN_TABLE          "main_table"
#define ORDER               "order_number"
#define WORKER              "worker"
#define EQUIPMENT           "equipment"
#define DATE                "date"

#define ORDER_TABLE         "order_table"
#define ORDER_NAME          "order_name"

#define PART_TABLE          "part_table"
#define ORDER_ID            "order_id"
#define PART_NAME           "part_name"

#define WORKER_TABLE        "worker_table"
#define WORKER_NAME         "worker_name"

#define EQUIPMENT_TABLE     "equipment_table"
#define EQUIPMENT_NAME      "equipment_name"

#define ACCOUNT_TABLE       "account_table"

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
