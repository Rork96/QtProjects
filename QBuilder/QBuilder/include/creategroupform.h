#ifndef CREATEGROUPFORM_H
#define CREATEGROUPFORM_H

#include "BaseForm.h"

namespace Ui {
class CreateGroupForm;
}

class CreateGroupForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateGroupForm(QWidget *parent = 0);
    ~CreateGroupForm();

    //void setRowIndex(int rowIndex, int) override; // User chose to edit data from the table

private:
    Ui::CreateGroupForm *ui;

    const QString Table = "groups";
    const QString Record = "Group name";

    void submitChanges() override;
};

#endif // CREATEGROUPFORM_H
