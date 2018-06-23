#ifndef CREATETEMPLATESFORM_H
#define CREATETEMPLATESFORM_H

#include <QWidget>
#include <QSqlTableModel>
#include <QDataWidgetMapper>

#define TABLE   "templates"

namespace Ui {
class CreateTemplatesForm;
}

class CreateTemplatesForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateTemplatesForm(QWidget *parent = 0);
    ~CreateTemplatesForm();

    void setRowIndex(int rowIndex); // User chose to edit data from the table

private:
    Ui::CreateTemplatesForm *ui;

    QSqlTableModel *model;
    QDataWidgetMapper *mapper;

    void submitChanges();

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATETEMPLATESFORM_H
