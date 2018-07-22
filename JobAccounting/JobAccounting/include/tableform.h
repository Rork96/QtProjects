#ifndef TABLEFORM_H
#define TABLEFORM_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QListView>
#include "basecombomodel.h"

namespace Ui {
class TableForm;
}

class TableForm : public QWidget
{
    Q_OBJECT

public:
    explicit TableForm(QWidget *parent = 0, QString tableName = "main_table");
    ~TableForm();

    void setRights(QString user, int rights); // User rights: read or read and edit mode

private:
    Ui::TableForm *ui;

    const QString Main_Table = "main_table";
    const QString Worker_Table = "worker_table";
    const QString Equipment_Table = "equipment_table";

    const QString Order_Column = "order_number";
    const QString Worker_Column = "worker";
    const QString Worker_Name = "worker_name";
    const QString Equipment_Name = "equipment_name";

    QSqlRelationalTableModel *mainModel;        // For providing relations between tables

    BaseComboModel * cmodel;
    QListView *listView;
    QString user;

    void showSearchWidgets();                   // Show widgets for providing search
    void searchInDB(const QString &arg1);       // Interactive search in database
    void loadDataFromDB(const QString &table);  // Load data
    void acceptData();                          // Write data into database
    void deleteDatafromDB();                    // Delete current data from database
    void searchForComboBox();                   // Search data
    void adjustSearchForComboBox();
};

#endif // TABLEFORM_H
