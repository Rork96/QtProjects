#ifndef CREATESECURITYFILTERFORM_H
#define CREATESECURITYFILTERFORM_H

#include "BaseForm.h"
#include <QDataWidgetMapper>
#include <QSqlRelationalTableModel>

namespace Ui {
class CreateSecurityFilterForm;
}

class CreateSecurityFilterForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateSecurityFilterForm(QWidget *parent = 0);
    ~CreateSecurityFilterForm();

    void setRowIndex(int rowIndex, int) override;     // User chose to edit data from the table

private:
    Ui::CreateSecurityFilterForm *ui;

    QSqlTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges() override;

//signals:
//    void sygnalBack() override;
//    void sygnalSubmit() override;
};

#endif // CREATESECURITYFILTERFORM_H
