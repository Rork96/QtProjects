#ifndef CREATEQUESTIONFORM_H
#define CREATEQUESTIONFORM_H

#include "BaseForm.h"

namespace Ui {
class CreateQuestionForm;
}

class CreateQuestionForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateQuestionForm(QWidget *parent = 0);
    ~CreateQuestionForm();

private:
    Ui::CreateQuestionForm *ui;

    const QString Table = "security_question";
};

#endif // CREATEQUESTIONFORM_H
