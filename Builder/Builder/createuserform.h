#ifndef CREATEUSERFORM_H
#define CREATEUSERFORM_H

#include <QWidget>

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
};

#endif // CREATEUSERFORM_H
