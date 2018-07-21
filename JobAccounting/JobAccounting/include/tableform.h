#ifndef TABLEFORM_H
#define TABLEFORM_H

#include <QWidget>
#include <QSqlRelationalTableModel>

#include <QListView>

namespace Ui {
class TableForm;
}

class TableForm : public QWidget
{
    Q_OBJECT

public:
    explicit TableForm(QWidget *parent = 0);
    ~TableForm();

    void setRights(const QString user, int rights); // User rights: read or read and edit mode

private:
    Ui::TableForm *ui;

    QSqlRelationalTableModel *mainModel;    // For providing relations between tables
    QSqlQueryModel *mod;

    QListView *listView;
    QString user;

    void showSearchWidgets();               // Show widgets for providing search
    void searchInDB(const QString &arg1);   // Interactive search in database

    void loadDataFromDB();                  // Load data
    void acceptData();                      // Write data into database
    void deleteDatafromDB();                // Delete current data from database
};

#endif // TABLEFORM_H
