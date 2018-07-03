#ifndef CREATESCREEFORM_H
#define CREATESCREEFORM_H

#include "BaseForm.h"
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class CreateScreeForm;
}

class CreateScreeForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateScreeForm(QWidget *parent = 0);
    ~CreateScreeForm();

    void setRowIndex(int rowIndex, int) override; // User chose to edit data from the table

private:
    Ui::CreateScreeForm *ui;

    const QString Table = "screens";

    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;
    bool isEdit = false;

    void submitChanges() override;

//signals:
//    void sygnalBack() override;
//    void sygnalSubmit() override;
};

#endif // CREATESCREEFORM_H
