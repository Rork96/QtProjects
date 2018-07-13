#ifndef CREATEDOCFAMILYFORM_H
#define CREATEDOCFAMILYFORM_H

#include "BaseForm.h"

namespace Ui {
class CreateDocFamilyForm;
}

class CreateDocFamilyForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateDocFamilyForm(QWidget *parent = 0);
    ~CreateDocFamilyForm();

    void setRowIndex(int rowIndex, int id) override;     // User chose to edit data from the table

private:
    Ui::CreateDocFamilyForm *ui;

    const QString Table = "document_family";    // Base table name
    const QString Record = "family_name";
    const QString Category = "categories";      // Second table

    QSqlRelationalTableModel *categoryModel;

    void submitChanges() override;

    void addCategory();
    void delCategory();
};

#endif // CREATEDOCFAMILYFORM_H
