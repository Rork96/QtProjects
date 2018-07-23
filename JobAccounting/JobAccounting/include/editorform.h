#ifndef EditorForm_H
#define EditorForm_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>
#include <QSqlRelationalDelegate>

namespace Ui
{
class EditorForm;
}

class EditorForm: public QWidget
{
    Q_OBJECT

public:
    explicit EditorForm(QWidget *parent = 0);
    ~EditorForm();

private:
    Ui::EditorForm *ui;

    const QString Main_Table = "main_table";
    const QString Worker_Table = "worker_table";
    const QString Equipment_Table = "equipment_table";

    const QString Worker = "worker";
    const QString Equipment = "equipment";

    const QString Worker_Name = "worker_name";
    const QString Equipment_Name = "equipment_name";

    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;

    void clearAll();        // Clear all data
    void submitChanges();   // Save data to database
    void calckTime();       // Calculate time
};

#endif //EditorForm_H
