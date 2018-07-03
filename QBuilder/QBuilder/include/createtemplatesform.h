#ifndef CREATETEMPLATESFORM_H
#define CREATETEMPLATESFORM_H

#include "BaseForm.h"
#include <QSqlTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class CreateTemplatesForm;
}

class CreateTemplatesForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateTemplatesForm(QWidget *parent = 0);
    ~CreateTemplatesForm();

    void setRowIndex(int rowIndex, int) override; // User chose to edit data from the table

private:
    Ui::CreateTemplatesForm *ui;

    const QString Table = "templates";

    QSqlTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges() override;

//signals:
//    void sygnalBack() override;
//    void sygnalSubmit() override;
};

#endif // CREATETEMPLATESFORM_H
