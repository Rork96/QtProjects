#ifndef CREATEDOCFAMILYFORM_H
#define CREATEDOCFAMILYFORM_H

#include "BaseForm.h"
//#include <QLineEdit>
//#include <QToolButton>
#include <QDataWidgetMapper>
#include <QSqlRelationalTableModel>

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
    const QString Category = "categories";      // Second table

    QSqlTableModel *model;
    QDataWidgetMapper *mapper;
    QSqlRelationalTableModel *categoryModel;

    int currentId = -1;
    bool isEdit = false;

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

//signals:
//    void sygnalBack() override;
//    void sygnalSubmit() override;
};

#endif // CREATEDOCFAMILYFORM_H
