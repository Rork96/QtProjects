#ifndef CREATEDOCGROUPSFORM_H
#define CREATEDOCGROUPSFORM_H

#include <QWidget>

namespace Ui {
class CreateDocGroupsForm;
}

class CreateDocGroupsForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateDocGroupsForm(QWidget *parent = 0);
    ~CreateDocGroupsForm();

private:
    Ui::CreateDocGroupsForm *ui;

    void submitChanges();

signals:
    sygnalBack();
    sygnalSubmit();
};

#endif // CREATEDOCGROUPSFORM_H
