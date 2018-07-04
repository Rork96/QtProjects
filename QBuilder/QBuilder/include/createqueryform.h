#ifndef CREATEQUERYFORM_H
#define CREATEQUERYFORM_H

#include "BaseForm.h"

namespace Ui {
class CreateQueryForm;
}

class CreateQueryForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateQueryForm(QWidget *parent = 0);
    ~CreateQueryForm();

private:
    Ui::CreateQueryForm *ui;

    const QString Table = "query";
    const QString Record = "Query name";

    void submitChanges() override;
};

#endif // CREATEQUERYFORM_H
