#ifndef CREATECUSTQBUILDFORM_H
#define CREATECUSTQBUILDFORM_H

#include <QWidget>

namespace Ui {
class CreateCustQBuildForm;
}

class CreateCustQBuildForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateCustQBuildForm(QWidget *parent = 0);
    ~CreateCustQBuildForm();

private:
    Ui::CreateCustQBuildForm *ui;

    void submitChanges();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATECUSTQBUILDFORM_H
