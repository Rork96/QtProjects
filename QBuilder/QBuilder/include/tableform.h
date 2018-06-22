#ifndef TABLEFORM_H
#define TABLEFORM_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class TableForm;
}

class TableForm : public QWidget
{
    Q_OBJECT

public:
    explicit TableForm(QWidget *parent = 0);
    ~TableForm();

    // View type
    enum Type {
        none = 0,
        groups,
        users,
        tenant,
        logo,
        security_filters,
        menu,
        group_screens,
        screens,
        document_family,
        document_groups,
        lists,
        templates,
        custom_data_sources,
        extension_functions,
        servers,
        security_questions,
        custom_query
    };
    void setViewType(Type type);

private:
    Ui::TableForm *ui;

    QSqlTableModel *mainModel;

    void searchInDB();
    Type viewType;

    void loadDataFromDB();      // Load data
    void deleteDatafromDB();    // Delete current data from database

signals:
    void createData(Type type);
    void createDataWithBuilder(Type type);
};

#endif // TABLEFORM_H
