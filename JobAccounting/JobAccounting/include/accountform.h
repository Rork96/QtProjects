#ifndef accountform_H
#define accountform_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QListView>

namespace Ui {
class AccountForm;
}

class AccountForm : public QWidget
{
    Q_OBJECT

public:
    explicit AccountForm(QWidget *parent = 0);
    ~AccountForm();

    void reloadView();                          // Reload table when language changed

private:
    Ui::AccountForm *ui;

    QSqlRelationalTableModel *mainModel;        // For providing relations between tables

    void showSearchWidgets();                   // Show widgets for providing search
    void searchInDB();                          // Interactive search in database
    void loadDataFromDB();  // Load data
    void acceptData();                          // Write data into database
    // Calculete time
    void calculateData(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
    // Sorting in tableView
    void sortByColumn(int index);
};

#endif //accountform_H
