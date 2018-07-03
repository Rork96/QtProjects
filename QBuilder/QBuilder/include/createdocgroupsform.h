#ifndef CREATEDOCGROUPSFORM_H
#define CREATEDOCGROUPSFORM_H

#include "BaseForm.h"
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class CreateDocGroupsForm;
}

class CreateDocGroupsForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateDocGroupsForm(QWidget *parent = 0);
    ~CreateDocGroupsForm();

    void setRowIndex(int rowIndex, int) override;     // User chose to edit data from the table

private:
    Ui::CreateDocGroupsForm *ui;

    const QString Table = "document_group";     // Base table name
    const QString Record = "group_name";        // Unique record

    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges() override;

//signals:
//    void sygnalBack();
//    void sygnalSubmit();

private slots:
    void on_docFamilyBox_currentIndexChanged(const QString &arg1);
};

#endif // CREATEDOCGROUPSFORM_H
