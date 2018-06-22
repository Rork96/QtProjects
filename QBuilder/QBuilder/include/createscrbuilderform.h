#ifndef CREATESCRBUILDERFORM_H
#define CREATESCRBUILDERFORM_H

#include <QWidget>

namespace Ui {
class CreateScrBuilderForm;
}

class CreateScrBuilderForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateScrBuilderForm(QWidget *parent = 0);
    ~CreateScrBuilderForm();

private:
    Ui::CreateScrBuilderForm *ui;

signals:
    void sygnalBack();
};

#endif // CREATESCRBUILDERFORM_H
