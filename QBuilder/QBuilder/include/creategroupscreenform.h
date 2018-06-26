#ifndef CREATEGROUPSCREENFORM_H
#define CREATEGROUPSCREENFORM_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>

#define TABLE   "group_screen"

namespace Ui {
class CreateGroupScreenForm;
}

class CreateGroupScreenForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateGroupScreenForm(QWidget *parent = 0);
    ~CreateGroupScreenForm();

    void setRowIndex(int rowIndex); // User chose to edit data from the table

private:
    Ui::CreateGroupScreenForm *ui;

    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATEGROUPSCREENFORM_H
