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

    void submitChanges();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATETENANTFORM_H
