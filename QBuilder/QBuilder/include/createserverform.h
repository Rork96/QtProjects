#ifndef CREATESERVERFORM_H
#define CREATESERVERFORM_H

#include <QWidget>

namespace Ui {
class CreateServerForm;
}

class CreateServerForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateServerForm(QWidget *parent = 0);
    ~CreateServerForm();

private:
    Ui::CreateServerForm *ui;

    void submitChanges();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATESERVERFORM_H