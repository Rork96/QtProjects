#ifndef CREATEUSERFORM_H
#define CREATEUSERFORM_H

#include <QWidget>
#include <QComboBox>

namespace Ui {
class CreateUserForm;
}

class CreateUserForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateUserForm(QWidget *parent = 0);
    ~CreateUserForm();

private:
    Ui::CreateUserForm *ui;

    void initComboBox(QList<QComboBox*> elements); // Init comboboxes with colors

    void submitChanges();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATEUSERFORM_H
