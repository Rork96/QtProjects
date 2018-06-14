#ifndef CREATESCREEFORM_H
#define CREATESCREEFORM_H

#include <QWidget>

namespace Ui {
class CreateScreeForm;
}

class CreateScreeForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateScreeForm(QWidget *parent = 0);
    ~CreateScreeForm();

private:
    Ui::CreateScreeForm *ui;
};

#endif // CREATESCREEFORM_H
