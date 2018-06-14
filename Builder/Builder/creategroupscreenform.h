#ifndef CREATEGROUPSCREENFORM_H
#define CREATEGROUPSCREENFORM_H

#include <QWidget>

namespace Ui {
class CreateGroupScreenForm;
}

class CreateGroupScreenForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateGroupScreenForm(QWidget *parent = 0);
    ~CreateGroupScreenForm();

private:
    Ui::CreateGroupScreenForm *ui;
};

#endif // CREATEGROUPSCREENFORM_H
