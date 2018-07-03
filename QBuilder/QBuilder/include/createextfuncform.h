#ifndef CREATEEXTFUNCFORM_H
#define CREATEEXTFUNCFORM_H

#include "BaseForm.h"
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class CreateExtFuncForm;
}

class CreateExtFuncForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateExtFuncForm(QWidget *parent = 0);
    ~CreateExtFuncForm();

    void setRowIndex(int rowIndex, int) override; // User chose to edit data from the table

private:
    Ui::CreateExtFuncForm *ui;

    const QString Table = "extension_functions";

    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges() override;

//signals:
//    void sygnalBack() override;
//    void sygnalSubmit() override;
};

#endif // CREATEEXTFUNCFORM_H
