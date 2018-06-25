#ifndef CREATEMENUFORM_H
#define CREATEMENUFORM_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>

#define TABLE   "menus"

namespace Ui {
class CreateMenuForm;
}

class CreateMenuForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateMenuForm(QWidget *parent = 0);
    ~CreateMenuForm();

    void setRowIndex(int rowIndex); // User chose to edit data from the table

private:
    Ui::CreateMenuForm *ui;

    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATEMENUFORM_H
