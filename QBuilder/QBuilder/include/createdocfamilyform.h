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

//    QVector<QLineEdit*> catL;
//    QVector<QLineEdit*> descrL;
//    QVector<QLineEdit*> kp_1_L;
//    QVector<QLineEdit*> kp_2_L;
//    QVector<QLineEdit*> kp_3_L;
//    QVector<QLineEdit*> kp_4_L;
//    QVector<QLineEdit*> kp_5_L;
//    QVector<QLineEdit*> searchL;
//    QVector<QToolButton*> delBtn;
};

#endif // CREATEDOCFAMILYFORM_H
