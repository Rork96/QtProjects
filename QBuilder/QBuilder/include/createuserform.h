#ifndef CREATEUSERFORM_H
#define CREATEUSERFORM_H

#include "BaseForm.h"
#include "basecombomodel.h"
#include "clickelineedit.h"
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

    void setRowIndex(int rowIndex, int id) override; // User chose to edit data from the table

private:
    Ui::CreateUserForm *ui;

    const  QString Table = "users";
    const  QString Record = "username";

    bool avatarChanged = false;
    bool menuImgChanged = false;
    bool bodyImgChanged = false;

    void checkPasswordLength(const QString &arg1);

    void submitChanges() override;
    void openImage();

    QList<QComboBox*> combo;            // ComboBoxes
    QList<BaseComboModel*> cbModel;     // Combobox models
    QList<ClickeLineEdit*> colorLine;   // Color lineEdits

    BaseComboModel *groupModel;
    BaseComboModel *accountModel;
    BaseComboModel *tenantModel;
    BaseComboModel *userModel;
    BaseComboModel *currencyModel;
    BaseComboModel *currencyTypeModel;
    BaseComboModel *timezoneModel;
    BaseComboModel *timeFormatModel;
    BaseComboModel *dateModel;
    BaseComboModel *docModel;
    BaseComboModel *bntModel;
    BaseComboModel *menuModel;
    BaseComboModel *borderModel;
    BaseComboModel *headerBorderModel;
};

#endif // CREATEUSERFORM_H
