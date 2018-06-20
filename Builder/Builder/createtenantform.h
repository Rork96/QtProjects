#ifndef CREATETENANTFORM_H
#define CREATETENANTFORM_H

#include <QWidget>

#include <QComboBox>

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

    void initComboBox(QList<QComboBox*> elements); // Init comboboxes with colors

    void submitChanges();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATETENANTFORM_H
