#ifndef CREATELOGOFORM_H
#define CREATELOGOFORM_H

#include "BaseForm.h"
#include <QDataWidgetMapper>
#include <QSqlRelationalTableModel>

namespace Ui {
class CreateLogoForm;
}

class CreateLogoForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateLogoForm(QWidget *parent = 0);
    ~CreateLogoForm();

    void setRowIndex(int rowIndex, int id) override;     // User chose to edit data from the table

private:
    Ui::CreateLogoForm *ui;

    const QString Table = "logo";
    const QString Record = "entry_name";

    bool imageChanged = false;

    void submitChanges() override;
    void openImage();
};

#endif // CREATELOGOFORM_H
