#ifndef CREATETEMPLATESFORM_H
#define CREATETEMPLATESFORM_H

#include <QWidget>

namespace Ui {
class CreateTemplatesForm;
}

class CreateTemplatesForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateTemplatesForm(QWidget *parent = 0);
    ~CreateTemplatesForm();

private:
    Ui::CreateTemplatesForm *ui;
};

#endif // CREATETEMPLATESFORM_H
