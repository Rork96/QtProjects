#ifndef CREATETENANTFORM_H
#define CREATETENANTFORM_H

#include "BaseForm.h"
#include <QComboBox>
#include <QDataWidgetMapper>
#include <QSqlRelationalTableModel>

namespace Ui {
class CreateTenantForm;
}

class CreateTenantForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateTenantForm(QWidget *parent = 0);
    ~CreateTenantForm();

    void setRowIndex(int rowIndex, int) override;     // User chose to edit data from the table

private:
    Ui::CreateTenantForm *ui;

    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;

    const QString Table = "tenant";

    void initComboBox(QList<QComboBox*> elements); // Init comboboxes with colors

    void submitChanges() override;

//signals:
//    void sygnalBack() override;
//    void sygnalSubmit() override;
};

#endif // CREATETENANTFORM_H
