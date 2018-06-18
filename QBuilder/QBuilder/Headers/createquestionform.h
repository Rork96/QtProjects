#ifndef CREATEQUESTIONFORM_H
#define CREATEQUESTIONFORM_H

#include <QWidget>

namespace Ui {
class CreateQuestionForm;
}

class CreateQuestionForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateQuestionForm(QWidget *parent = 0);
    ~CreateQuestionForm();

private:
    Ui::CreateQuestionForm *ui;
};

#endif // CREATEQUESTIONFORM_H
