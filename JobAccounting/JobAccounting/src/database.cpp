#include "database.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

// Connect to database
int DataBase::connectToDataBase(QString userName, QString password)
{
    /* Before connecting to the database, verify its existence.
     */
    if (!userName.isEmpty()) {
        this->userName = userName;
        this->password = password;
        return this->openDataBase();
    }
    else {
        return 0;
    }
}

// Open database
int DataBase::openDataBase()
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
        if (query.exec( "SELECT password, rights FROM users WHERE username = '" + this->userName + "'" )) {
            while (query.next()) {
                // Check password
                if (query.value(0).toString() == this->password) {
                    return query.value(1).toInt();  // return rights
                }
                else return 0;  // username or password incorrect
            }
        }
    }
    else {
        QMessageBox::warning(nullptr, trUtf8("Error"), db.lastError().text()); // Error
        return false;
    }
    return false;
}

// Close database
void DataBase::closeDataBase()
{
    db.close();
}
