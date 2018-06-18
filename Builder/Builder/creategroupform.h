#ifndef CREATEGROUPFORM_H
#define CREATEGROUPFORM_H

#include <QWidget>

namespace Ui {
class CreateGroupForm;
}

class CreateGroupForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateGroupForm(QWidget *parent = 0);
    ~CreateGroupForm();

private:
    Ui::CreateGroupForm *ui;

    void submitChanges();

signals:
    sygnalBack();
    sygnalSubmit();
};

#endif // CREATEGROUPFORM_H
