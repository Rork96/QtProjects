#ifndef CREATESECURITYFILTERFORM_H
#define CREATESECURITYFILTERFORM_H

#include "BaseForm.h"
#include "basecombomodel.h"

namespace Ui {
class CreateSecurityFilterForm;
}

class CreateSecurityFilterForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateSecurityFilterForm(QWidget *parent = 0);
    ~CreateSecurityFilterForm();

    void setRowIndex(int rowIndex, int id) override;     // User chose to edit data from the table

private:
    Ui::CreateSecurityFilterForm *ui;

    const QString Table = "security_filters";

    void submitChanges() override;

    QList<QComboBox*> combo;            // ComboBoxes
    QList<BaseComboModel*> cbModel;     // Combobox models

    /* Combobox models */
    BaseComboModel *tenantCModel;
    BaseComboModel *acTypeCModel;
};

#endif // CREATESECURITYFILTERFORM_H
