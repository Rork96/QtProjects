#include <QtWidgets/QMessageBox>
#include <QtSql/QSqlRecord>
#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

// Connect to database
bool DataBase::connectToDataBase(QString userName, QString password)
{
    /* Before connecting to the database, verify its existence.
     */
    if (!userName.isEmpty()) {
        this->userName = userName;
        this->password = password;
        return this->openDataBase();
    }
    else {
        return false;
    }
}

// Open database
bool DataBase::openDataBase()
{
    /* Open database as superuser
     */
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DATABASE_NAME);
    db.setPort(PORT);
    db.setUserName(USER_NAME);
    db.setPassword(PASSWORD);

    // Check username and password
    if(db.open()) {
        QSqlQuery query;
        if (query.exec( "SELECT password FROM users WHERE username = '" + this->userName + "'" )) {
            while (query.next()) {
                QString result = query.value(0).toString();
                qDebug() << result;
                return !(result != this->password);
                /*if (result != this->password) {
                    return false;
                }
                else return true;*/
            }
        }
    }
    else {
        QMessageBox::warning(nullptr, "Error", db.lastError().text()); // Error
        return false;
    }
    return false;
}

// Close database
void DataBase::closeDataBase()
{
    db.close();
}
