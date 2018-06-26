#ifndef CREATEDATASOURCEFORM_H
#define CREATEDATASOURCEFORM_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>

#define TABLE   "data_sources"

namespace Ui {
class CreateDataSourceForm;
}

class CreateDataSourceForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateDataSourceForm(QWidget *parent = 0);
    ~CreateDataSourceForm();

    void setRowIndex(int rowIndex); // User chose to edit data from the table

private:
    Ui::CreateDataSourceForm *ui;

    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATEDATASOURCEFORM_H
