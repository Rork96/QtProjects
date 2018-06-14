#ifndef CREATEMENUFORM_H
#define CREATEMENUFORM_H

#include <QWidget>

namespace Ui {
class CreateMenuForm;
}

class CreateMenuForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateMenuForm(QWidget *parent = 0);
    ~CreateMenuForm();

private:
    Ui::CreateMenuForm *ui;
};

#endif // CREATEMENUFORM_H
