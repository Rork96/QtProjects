#ifndef CREATESCREEFORM_H
#define CREATESCREEFORM_H

#include "BaseForm.h"

namespace Ui {
class CreateScreeForm;
}

class CreateScreeForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateScreeForm(QWidget *parent = 0);
    ~CreateScreeForm();

private:
    Ui::CreateScreeForm *ui;

    const QString Table = "screens";
    const QString Record = "tab_text";

    void submitChanges() override;
};

#endif // CREATESCREEFORM_H
