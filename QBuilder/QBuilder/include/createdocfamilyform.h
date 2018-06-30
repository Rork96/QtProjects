#ifndef CREATEDOCFAMILYFORM_H
#define CREATEDOCFAMILYFORM_H

#include <QWidget>
//#include <QLineEdit>
//#include <QToolButton>
#include <QDataWidgetMapper>
#include <QSqlRelationalTableModel>

#define TABLE       "document_family"
#define CATEGORY    "categories"

namespace Ui {
class CreateDocFamilyForm;
}

class CreateDocFamilyForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateDocFamilyForm(QWidget *parent = 0);
    ~CreateDocFamilyForm();

    void setRowIndex(int rowIndex, int id);     // User chose to edit data from the table

private:
    Ui::CreateDocFamilyForm *ui;

    QSqlTableModel *model;
    QDataWidgetMapper *mapper;
    QSqlRelationalTableModel *categoryModel;

    int currentId = -1;
    bool isEdit = false;

    void submitChanges();

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

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATEDOCFAMILYFORM_H
