#ifndef CREATELISTFORM_H
#define CREATELISTFORM_H

#include "BaseForm.h"

namespace Ui {
class CreateListForm;
}

class CreateListForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateListForm(QWidget *parent = 0);
    ~CreateListForm();


private:
    Ui::CreateListForm *ui;

    const QString Table = "lists";
    const QString Record = "Entry name";

    void submitChanges() override;
};

#endif // CREATELISTFORM_H
