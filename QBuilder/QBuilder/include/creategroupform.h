#ifndef CREATEGROUPFORM_H
#define CREATEGROUPFORM_H

#include <QWidget>
#include <QSqlTableModel>
#include <QDataWidgetMapper>

#define TABLE   "admin_groups"
#define RECORD  "Group name"

namespace Ui {
class CreateGroupForm;
}

class CreateGroupForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateGroupForm(QWidget *parent = 0);
    ~CreateGroupForm();

    void setRowIndex(int rowIndex); // User chose to edit data from the table

private:
    Ui::CreateGroupForm *ui;

    QSqlTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATEGROUPFORM_H
