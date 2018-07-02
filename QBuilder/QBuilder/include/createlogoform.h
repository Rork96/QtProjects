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

    void setRowIndex(int rowIndex, int id);     // User chose to edit data from the table

private:
    Ui::CreateLogoForm *ui;

    void submitChanges();
    void openImage();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATELOGOFORM_H
