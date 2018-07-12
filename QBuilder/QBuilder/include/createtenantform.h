#ifndef CREATETENANTFORM_H
#define CREATETENANTFORM_H

#include "BaseForm.h"
#include "basecombomodel.h"
#include "clickelineedit.h"

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
    const QString Record1 = "tenant_code";
    const QString Record2 = "name";

    void submitChanges() override;

    QList<QComboBox*> combo;            // ComboBoxes
    QList<BaseComboModel*> cbModel;     // Combobox models
    QList<ClickeLineEdit*> colorLine;   // Color lineEdits

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
    BaseComboModel *borderModel;
    BaseComboModel *headerLogoModel;
    BaseComboModel *mainLogoModel;
    BaseComboModel *headerBorderModel;
};

#endif // CREATETENANTFORM_H
