#ifndef CREATEEXTFUNCFORM_H
#define CREATEEXTFUNCFORM_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>

#define TABLE   "extension_functions"

namespace Ui {
class CreateExtFuncForm;
}

class CreateExtFuncForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateExtFuncForm(QWidget *parent = 0);
    ~CreateExtFuncForm();

    void setRowIndex(int rowIndex); // User chose to edit data from the table

private:
    Ui::CreateExtFuncForm *ui;

    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATEEXTFUNCFORM_H
