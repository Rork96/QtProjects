#ifndef CREATELOGOFORM_H
#define CREATELOGOFORM_H

#include "BaseForm.h"
#include <QDataWidgetMapper>
#include <QSqlRelationalTableModel>

namespace Ui {
class CreateLogoForm;
}

class CreateLogoForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateLogoForm(QWidget *parent = 0);
    ~CreateLogoForm();

    void setRowIndex(int rowIndex, int) override;     // User chose to edit data from the table

private:
    Ui::CreateLogoForm *ui;

    QSqlTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges() override;
    void openImage();

//signals:
//    void sygnalBack() override;
//    void sygnalSubmit() override;
};

#endif // CREATELOGOFORM_H
