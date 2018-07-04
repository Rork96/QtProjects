#ifndef CREATETENANTFORM_H
#define CREATETENANTFORM_H

#include "BaseForm.h"
#include <QComboBox>

namespace Ui {
class CreateTenantForm;
}

class CreateTenantForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateTenantForm(QWidget *parent = 0);
    ~CreateTenantForm();

    void setRowIndex(int rowIndex, int id) override;     // User chose to edit data from the table

private:
    Ui::CreateTenantForm *ui;

    const QString Table = "tenant";

    void initComboBox(QList<QComboBox*> elements); // Init comboboxes with colors

    void submitChanges() override;
};

#endif // CREATETENANTFORM_H
