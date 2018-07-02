#ifndef CREATESECURITYFILTERFORM_H
#define CREATESECURITYFILTERFORM_H

#include <QWidget>

namespace Ui {
class CreateSecurityFilterForm;
}

class CreateSecurityFilterForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateSecurityFilterForm(QWidget *parent = 0);
    ~CreateSecurityFilterForm();

    void setRowIndex(int rowIndex, int id);     // User chose to edit data from the table

private:
    Ui::CreateSecurityFilterForm *ui;

    void submitChanges();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATESECURITYFILTERFORM_H
