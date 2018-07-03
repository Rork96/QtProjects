#ifndef CREATESERVERFORM_H
#define CREATESERVERFORM_H

#include "BaseForm.h"
#include <QSqlTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class CreateServerForm;
}

class CreateServerForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateServerForm(QWidget *parent = 0);
    ~CreateServerForm();

    void setRowIndex(int rowIndex, int) override; // User chose to edit data from the table

private:
    Ui::CreateServerForm *ui;

    const QString Table = "servers";

    QSqlTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges() override;

//signals:
//    void sygnalBack() override;
//    void sygnalSubmit() override;
};

#endif // CREATESERVERFORM_H
