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
    //db.setUserName(USER_NAME);
    //db.setPassword(PASSWORD);
    db.setUserName(userName);
    db.setPassword(password);

    return db.open();
    /*
    SELECT privilege_type
    FROM information_schema.role_table_grants
    WHERE grantee = 'editor' AND table_name = 'main_table'
*/

    // Check username and password
//    if(db.open()) {
//        QSqlQuery query;
//        if (query.exec( "SELECT password, rights FROM users WHERE username = '" + this->userName + "'" )) {
//            while (query.next()) {
//                // Check password
//                if (query.value(0).toString() == this->password) {
//                    return query.value(1).toInt();  // return rights
//                }
//                else return 0;  // username or password incorrect
//            }
//        }
//    }
//    else {
//        QMessageBox::warning(nullptr, trUtf8("Error"), db.lastError().text()); // Error
//        return false;
//    }
//    return false;

//    QString result;
//
//    if (db.open()) {
//        QSqlQuery query;
//        if (query.exec( "SELECT privilege_type FROM information_schema.role_table_grants WHERE grantee = '" +
//            userName + "' AND table_name = 'main_table'" )) {
//            while (query.next()) {
//                // Check privileges
//                if (query.value(0).toString() == "SELECT") {
//                    result += "1";
//                }
//                else if (query.value(0).toString() == "UPDATE") {
//
//                }
//                else if (query.value(0).toString() == "INSERT") {
//
//                }
//                else if (query.value(0).toString() == "DELETE") {
//
//                }
//            }
//        }
//    }
//    else {
//        QMessageBox::warning(nullptr, trUtf8("Error"), db.lastError().text()); // Error
//        return false;
//    }
//    return result;
}

// Close database
void DataBase::closeDataBase()
{
    db.close();
}
