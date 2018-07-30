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

    void reloadView();                          // Reload table when language changed

private:
    Ui::TableForm *ui;

    QString currentTable;

    QSqlRelationalTableModel *mainModel;        // For providing relations between tables

    void showSearchWidgets();                   // Show widgets for providing search
    void searchInDB();                          // Interactive search in database
    void loadDataFromDB(const QString &table);  // Load data
    void acceptData();                          // Write data into database
    void deleteDatafromDB();                    // Delete current data from database
    // Calculete time
    void calculateTime(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
    // Context menu for table
    void customMenuRequested(const QPoint &point);
    // Sorting in tableView
    void sortByColumn(int index);
    void setFilterForOrder();                   // Filter for order number for part table
};

#endif // TABLEFORM_H
