#ifndef CREATESCREEFORM_H
#define CREATESCREEFORM_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>

#define TABLE   "screens"

namespace Ui {
class CreateScreeForm;
}

class CreateScreeForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateScreeForm(QWidget *parent = 0);
    ~CreateScreeForm();

    void setRowIndex(int rowIndex); // User chose to edit data from the table

private:
    Ui::CreateScreeForm *ui;

    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATESCREEFORM_H
