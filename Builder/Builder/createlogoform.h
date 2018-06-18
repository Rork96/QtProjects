#ifndef CREATELOGOFORM_H
#define CREATELOGOFORM_H

#include <QWidget>

namespace Ui {
class CreateLogoForm;
}

class CreateLogoForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateLogoForm(QWidget *parent = 0);
    ~CreateLogoForm();

private:
    Ui::CreateLogoForm *ui;
};

#endif // CREATELOGOFORM_H
