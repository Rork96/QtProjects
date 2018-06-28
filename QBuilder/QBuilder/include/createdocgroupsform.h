#ifndef CREATEDOCGROUPSFORM_H
#define CREATEDOCGROUPSFORM_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>

#define TABLE   "document_group"
#define RECORD  "group_name"

namespace Ui {
class CreateDocGroupsForm;
}

class CreateDocGroupsForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateDocGroupsForm(QWidget *parent = 0);
    ~CreateDocGroupsForm();

    void setRowIndex(int rowIndex); // User chose to edit data from the table

private:
    Ui::CreateDocGroupsForm *ui;

    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges();

signals:
    void sygnalBack();
    void sygnalSubmit();
private slots:
    void on_docFamilyBox_currentIndexChanged(const QString &arg1);
};

#endif // CREATEDOCGROUPSFORM_H
