#ifndef CREATETEMPLATESFORM_H
#define CREATETEMPLATESFORM_H

#include "BaseForm.h"

namespace Ui {
class CreateTemplatesForm;
}

class CreateTemplatesForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateTemplatesForm(QWidget *parent = 0);
    ~CreateTemplatesForm();

private:
    Ui::CreateTemplatesForm *ui;

    const QString Table = "templates";
};

#endif // CREATETEMPLATESFORM_H
