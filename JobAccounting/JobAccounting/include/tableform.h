#ifndef TABLEFORM_H
#define TABLEFORM_H

#include <QWidget>
#include <QSqlRelationalTableModel>

#include <QListView>
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

private:
    Ui::TableForm *ui;

    QSqlRelationalTableModel *mainModel;    // For providing relations between tables

    QListView *listView;

    void showSearchWidgets();               // Show widgets for providing search
    void searchInDB(const QString &arg1);   // Interactive search in database
    void setRights(const int rights);       // User rights: read or read and edit mode

    void loadDataFromDB();                  // Load data
    void deleteDatafromDB();                // Delete current data from database
};

#endif // TABLEFORM_H
