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
    explicit TableForm(QWidget *parent = 0, QString tableName = "main_table");
    ~TableForm();

    void setRights(int &rights);                // User rights: read or read and edit mode
    void reloadView();                          // Reload table when language changed

private:
    Ui::TableForm *ui;

    QString currentTable;

    QSqlRelationalTableModel *mainModel;        // For providing relations between tables
    QListView *listView;

    void showSearchWidgets();                   // Show widgets for providing search
    void searchInDB(const QString &arg1);       // Interactive search in database
    void loadDataFromDB(const QString &table);  // Load data
    void acceptData();                          // Write data into database
    void deleteDatafromDB();                    // Delete current data from database
    void searchForComboBox();                   // Search data
    void adjustSearchForComboBox();
};

#endif // TABLEFORM_H
