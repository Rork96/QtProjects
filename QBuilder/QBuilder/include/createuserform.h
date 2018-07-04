#ifndef CREATEUSERFORM_H
#define CREATEUSERFORM_H

#include "BaseForm.h"
#include <QComboBox>

namespace Ui {
class CreateUserForm;
}

class CreateUserForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateUserForm(QWidget *parent = 0);
    ~CreateUserForm();

    //void setRowIndex(int rowIndex, int) override; // User chose to edit data from the table

private:
    Ui::CreateUserForm *ui;

    const  QString Table = "user";
    const  QString Record = "User name";

    void initComboBox(QList<QComboBox*> elements);  // Init comboboxes with colors
    void checkPasswordLength(const QString &arg1);

    void submitChanges() override;
    void openImage();
};

#endif // CREATEUSERFORM_H
