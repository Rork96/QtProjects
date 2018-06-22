#ifndef CREATEGROUPFORM_H
#define CREATEGROUPFORM_H

#include <QWidget>
#include <QSqlTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class CreateGroupForm;
}

class CreateGroupForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateGroupForm(QWidget *parent = 0);
    ~CreateGroupForm();

private:
    Ui::CreateGroupForm *ui;

    void submitChanges();

    QSqlTableModel *model;
    QDataWidgetMapper *mapper;

signals:
    void sygnalBack();
    void sygnalSubmit();
};

#endif // CREATEGROUPFORM_H
