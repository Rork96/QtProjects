#ifndef CREATEGROUPSCREENFORM_H
#define CREATEGROUPSCREENFORM_H

#include "BaseForm.h"
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class CreateGroupScreenForm;
}

class CreateGroupScreenForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateGroupScreenForm(QWidget *parent = 0);
    ~CreateGroupScreenForm();

    void setRowIndex(int rowIndex, int) override; // User chose to edit data from the table

private:
    Ui::CreateGroupScreenForm *ui;

    const QString Table = "group_screen";

    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges() override;

//signals:
//    void sygnalBack() override;
//    void sygnalSubmit() override;
};

#endif // CREATEGROUPSCREENFORM_H
