#ifndef CREATEMENUFORM_H
#define CREATEMENUFORM_H

#include "BaseForm.h"
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class CreateMenuForm;
}

class CreateMenuForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateMenuForm(QWidget *parent = 0);
    ~CreateMenuForm();

    void setRowIndex(int rowIndex, int) override; // User chose to edit data from the table

private:
    Ui::CreateMenuForm *ui;

    const  QString Table = "menus";

    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges() override;

//signals:
//    void sygnalBack() override;
//    void sygnalSubmit() override;
};

#endif // CREATEMENUFORM_H
