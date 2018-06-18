#ifndef CREATELISTFORM_H
#define CREATELISTFORM_H

#include <QWidget>

namespace Ui {
class CreateListForm;
}

class CreateListForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateListForm(QWidget *parent = 0);
    ~CreateListForm();

private:
    Ui::CreateListForm *ui;

    void submitChanges();

signals:
    sygnalBack();
    sygnalSubmit();
};

#endif // CREATELISTFORM_H
