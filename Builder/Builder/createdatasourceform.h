#ifndef CREATEDATASOURCEFORM_H
#define CREATEDATASOURCEFORM_H

#include <QWidget>

namespace Ui {
class CreateDataSourceForm;
}

class CreateDataSourceForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateDataSourceForm(QWidget *parent = 0);
    ~CreateDataSourceForm();

private:
    Ui::CreateDataSourceForm *ui;

    void submitChanges();

signals:
    sygnalBack();
    sygnalSubmit();
};

#endif // CREATEDATASOURCEFORM_H
