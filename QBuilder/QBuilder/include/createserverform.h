#ifndef CREATESERVERFORM_H
#define CREATESERVERFORM_H

#include "BaseForm.h"

namespace Ui {
class CreateServerForm;
}

class CreateServerForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateServerForm(QWidget *parent = 0);
    ~CreateServerForm();

private:
    Ui::CreateServerForm *ui;

    const QString Table = "servers";
};

#endif // CREATESERVERFORM_H
