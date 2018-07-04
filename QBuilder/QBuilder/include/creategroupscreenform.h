#ifndef CREATEGROUPSCREENFORM_H
#define CREATEGROUPSCREENFORM_H

#include "BaseForm.h"

namespace Ui {
class CreateGroupScreenForm;
}

class CreateGroupScreenForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateGroupScreenForm(QWidget *parent = 0);
    ~CreateGroupScreenForm();

    void setRowIndex(int rowIndex, int id) override; // User chose to edit data from the table

private:
    Ui::CreateGroupScreenForm *ui;

    const QString Table = "group_screen";

    void submitChanges() override;
};

#endif // CREATEGROUPSCREENFORM_H
