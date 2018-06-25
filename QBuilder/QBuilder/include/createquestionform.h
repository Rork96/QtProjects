#ifndef CREATEQUESTIONFORM_H
#define CREATEQUESTIONFORM_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>

#define TABLE   "security_question"

namespace Ui {
class CreateQuestionForm;
}

class CreateQuestionForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateQuestionForm(QWidget *parent = 0);
    ~CreateQuestionForm();

    void setRowIndex(int rowIndex); // User chose to edit data from the table

private:
    Ui::CreateQuestionForm *ui;

    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATEQUESTIONFORM_H
