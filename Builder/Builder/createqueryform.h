#ifndef CREATEQUERYFORM_H
#define CREATEQUERYFORM_H

#include <QWidget>

namespace Ui {
class CreateQueryForm;
}

class CreateQueryForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateQueryForm(QWidget *parent = 0);
    ~CreateQueryForm();

private:
    Ui::CreateQueryForm *ui;

    void submitChanges();

signals:
    sygnalBack();
    sygnalSubmit();
};

#endif // CREATEQUERYFORM_H
