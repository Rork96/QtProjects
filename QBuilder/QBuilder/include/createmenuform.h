#ifndef CREATEMENUFORM_H
#define CREATEMENUFORM_H

#include "BaseForm.h"

namespace Ui {
class CreateMenuForm;
}

class CreateMenuForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateMenuForm(QWidget *parent = 0);
    ~CreateMenuForm();

private:
    Ui::CreateMenuForm *ui;

    const  QString Table = "menus";
};

#endif // CREATEMENUFORM_H
