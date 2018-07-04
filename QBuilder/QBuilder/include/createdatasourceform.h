#ifndef CREATEDATASOURCEFORM_H
#define CREATEDATASOURCEFORM_H

#include "BaseForm.h"
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class CreateDataSourceForm;
}

class CreateDataSourceForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateDataSourceForm(QWidget *parent = 0);
    ~CreateDataSourceForm();

    void setRowIndex(int rowIndex, int id) override;     // User chose to edit data from the table

private:
    Ui::CreateDataSourceForm *ui;

    const QString Table = "data_sources";   // Base table name

    void submitChanges() override;
};

#endif // CREATEDATASOURCEFORM_H
