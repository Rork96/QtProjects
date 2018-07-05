#ifndef CREATETENANTFORM_H
#define CREATETENANTFORM_H

#include "BaseForm.h"
#include <QComboBox>
#include "basecombomodel.h"

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

    QList<QComboBox*> combo;            // ComboBoxes
    QList<BaseComboModel*> cbModel;     // Combobox models

    /* Combobox models */
    BaseComboModel *countryCModel;
    BaseComboModel *cityCModel;
    BaseComboModel *stateCModel;
    BaseComboModel *langCModel;
    BaseComboModel *currencyModel;
    BaseComboModel *currencyTypeModel;
    BaseComboModel *timezoneModel;
    BaseComboModel *timeFormatModel;
    BaseComboModel *dateModel;
    BaseComboModel *bntModel;
    BaseComboModel *menuModel;
};

#endif // CREATETENANTFORM_H
