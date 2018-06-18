#ifndef CREATETENANTFORM_H
#define CREATETENANTFORM_H

#include <QWidget>

namespace Ui {
class CreateTenantForm;
}

class CreateTenantForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateTenantForm(QWidget *parent = 0);
    ~CreateTenantForm();

private:
    Ui::CreateTenantForm *ui;
};

#endif // CREATETENANTFORM_H
