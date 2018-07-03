#ifndef CREATEQUESTIONFORM_H
#define CREATEQUESTIONFORM_H

#include "BaseForm.h"
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class CreateQuestionForm;
}

class CreateQuestionForm : public BaseForm
{
    Q_OBJECT

public:
    explicit CreateQuestionForm(QWidget *parent = 0);
    ~CreateQuestionForm();

    void setRowIndex(int rowIndex, int) override; // User chose to edit data from the table

private:
    Ui::CreateQuestionForm *ui;

    const QString Table = "security_question";

    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges() override;

//signals:
//    void sygnalBack() override;
//    void sygnalSubmit() override;
};

#endif // CREATEQUESTIONFORM_H
