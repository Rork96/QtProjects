#ifndef CREATEDOCFAMILYFORM_H
#define CREATEDOCFAMILYFORM_H

#include <QWidget>

namespace Ui {
class CreateDocFamilyForm;
}

class CreateDocFamilyForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateDocFamilyForm(QWidget *parent = 0);
    ~CreateDocFamilyForm();

private:
    Ui::CreateDocFamilyForm *ui;

    void submitChanges();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATEDOCFAMILYFORM_H
