#ifndef CREATELISTFORM_H
#define CREATELISTFORM_H

#include <QWidget>
#include <QSqlTableModel>
#include <QDataWidgetMapper>

#define TABLE   "lists"
#define RECORD  "Entry name"

namespace Ui {
class CreateListForm;
}

class CreateListForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateListForm(QWidget *parent = 0);
    ~CreateListForm();

    void setRowIndex(int rowIndex); // User chose to edit data from the table

private:
    Ui::CreateListForm *ui;

    QSqlTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATELISTFORM_H
