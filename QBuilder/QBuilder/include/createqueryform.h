#ifndef CREATEQUERYFORM_H
#define CREATEQUERYFORM_H

#include "BaseForm.h"
#include <QSqlTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class CreateQueryForm;
}

class CreateQueryForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateQueryForm(QWidget *parent = 0);
    ~CreateQueryForm();

    void setRowIndex(int rowIndex, int) override; // User chose to edit data from the table

private:
    Ui::CreateQueryForm *ui;

    const QString Table = "query";
    const QString Record = "Query name";

    QSqlTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges() override;

//signals:
//    void sygnalBack() override;
//    void sygnalSubmit() override;
};

#endif // CREATEQUERYFORM_H
