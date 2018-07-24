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

    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;

    void clearAll();        // Clear all data
    void submitChanges();   // Save data to database
    void calckTime();       // Calculate time
};

#endif //EditorForm_H
