#include "database.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

DataBase::DataBase(QObject *parent) : QObject(parent)
{
    // Program settings (ini in current program directorry)
    set = new QSettings("settings.ini", QSettings::IniFormat, this);
}

DataBase::~DataBase()
{

}

// Connect to database
bool DataBase::connectToDataBase(QString userName, QString password, int &rights)
{
    /* Before connecting to the database, verify its existence.
     */
    if (!userName.isEmpty()) {
        this->userName = userName;
        this->password = password;
        return this->openDataBase(rights);
    }
    else {
        return false;
    }
}

// Open database
bool DataBase::openDataBase(int &rights)
{
    /* Open database
     */

    // load settings
    loadConnectionSettings();

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(this->host);
    db.setDatabaseName(DATABASE_NAME);
    db.setPort(this->port);
    db.setUserName(userName);
    db.setPassword(password);

    rights = 0;

    bool result = db.open();
    if (result) {
        QSqlQuery query;
        if (query.exec( "SELECT privilege_type FROM information_schema.role_table_grants WHERE grantee = '" + userName + "' AND table_name = 'main_table'" )) {
            while (query.next()) {
                // Write rights
                if (query.value(0).toString() == "SELECT") {
                    this->rights += 1;
                }
                else if (query.value(0).toString() == "INSERT") {
                    this->rights += 3;
                }
                else if (query.value(0).toString() == "UPDATE") {
                    this->rights += 6;
                }
                else if (query.value(0).toString() == "DELETE") {
                    this->rights += 8;
                }
            }
        }
    }
    else {
        //QMessageBox::warning(nullptr, trUtf8("Error"), db.lastError().text()); // Error
        return result;
    }
    rights = this->rights;
    return result;
}

// Close database
void DataBase::closeDataBase()
{
    db.close();
}

void DataBase::loadConnectionSettings()
{
    // Load settings
    this->host = set->value("JobAccounting/host", "localhost").toString();
    this->port = set->value("JobAccounting/port", 5432).toInt();
}
