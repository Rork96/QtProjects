#ifndef CREATELISTFORM_H
#define CREATELISTFORM_H

#include "BaseForm.h"
#include <QSqlTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class CreateListForm;
}

class CreateListForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateListForm(QWidget *parent = 0);
    ~CreateListForm();

    void setRowIndex(int rowIndex, int) override; // User chose to edit data from the table

private:
    Ui::CreateListForm *ui;

    const QString Table = "lists";
    const QString Record = "Entry name";

    QSqlTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges() override;

//signals:
//    void sygnalBack() override;
//    void sygnalSubmit() override;
};

#endif // CREATELISTFORM_H
