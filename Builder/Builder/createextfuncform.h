#ifndef CREATEEXTFUNCFORM_H
#define CREATEEXTFUNCFORM_H

#include <QWidget>

namespace Ui {
class CreateExtFuncForm;
}

class CreateExtFuncForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateExtFuncForm(QWidget *parent = 0);
    ~CreateExtFuncForm();

private:
    Ui::CreateExtFuncForm *ui;
};

#endif // CREATEEXTFUNCFORM_H
