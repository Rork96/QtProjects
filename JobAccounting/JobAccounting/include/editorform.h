#ifndef EditorForm_H
#define EditorForm_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QTranslator>
#include <QSettings>
#include <QMenu>

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

protected:
    void changeEvent(QEvent * event) override;
    void translate(QString language);

private:
    Ui::EditorForm *ui;

    QMenu *languageMenu;
    QSettings *set;
    QTranslator qtLanguageTranslator;

    QSqlRelationalTableModel *mainModel;

    void clearAll();        // Clear all data
    void submitChanges();   // Save data to database
    void calckTime();       // Calculate time
    void setFilter();       // Set filter to model in table
    void loadData();        // Load data from database
};

#endif //EditorForm_H
