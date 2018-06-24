#ifndef CREATEQUERYFORM_H
#define CREATEQUERYFORM_H

#include <QWidget>
#include <QSqlTableModel>
#include <QDataWidgetMapper>

#define TABLE   "query"
#define RECORD  "Query name"

namespace Ui {
class CreateQueryForm;
}

class CreateQueryForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateQueryForm(QWidget *parent = 0);
    ~CreateQueryForm();

    void setRowIndex(int rowIndex); // User chose to edit data from the table

private:
    Ui::CreateQueryForm *ui;

    QSqlTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATEQUERYFORM_H
