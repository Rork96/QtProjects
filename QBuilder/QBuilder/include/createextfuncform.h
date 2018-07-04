#ifndef CREATEEXTFUNCFORM_H
#define CREATEEXTFUNCFORM_H

#include "BaseForm.h"

namespace Ui {
class CreateExtFuncForm;
}

class CreateExtFuncForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateExtFuncForm(QWidget *parent = 0);
    ~CreateExtFuncForm();

    void setRowIndex(int rowIndex, int id) override; // User chose to edit data from the table

private:
    Ui::CreateExtFuncForm *ui;

    const QString Table = "extension_functions";

    void submitChanges() override;
};

#endif // CREATEEXTFUNCFORM_H
