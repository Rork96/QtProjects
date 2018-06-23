#ifndef CREATEUSERFORM_H
#define CREATEUSERFORM_H

#include <QWidget>
#include <QComboBox>
#include <QSqlTableModel>
#include <QDataWidgetMapper>

#define TABLE   "user"
#define RECORD  "User name"

namespace Ui {
class CreateUserForm;
}

class CreateUserForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateUserForm(QWidget *parent = 0);
    ~CreateUserForm();

    void setRowIndex(int rowIndex); // User chose to edit data from the table

private:
    Ui::CreateUserForm *ui;

    QSqlTableModel *model;
    QDataWidgetMapper *mapper;

    void initComboBox(QList<QComboBox*> elements);  // Init comboboxes with colors
    void checkPasswordLength(const QString &arg1);

    void submitChanges();
    void openImage();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATEUSERFORM_H
