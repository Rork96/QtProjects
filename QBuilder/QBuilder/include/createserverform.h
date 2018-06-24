#ifndef CREATESERVERFORM_H
#define CREATESERVERFORM_H

#include <QWidget>
#include <QSqlTableModel>
#include <QDataWidgetMapper>

#define TABLE   "servers"


namespace Ui {
class CreateServerForm;
}

class CreateServerForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateServerForm(QWidget *parent = 0);
    ~CreateServerForm();

    void setRowIndex(int rowIndex); // User chose to edit data from the table

private:
    Ui::CreateServerForm *ui;

    QSqlTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATESERVERFORM_H
