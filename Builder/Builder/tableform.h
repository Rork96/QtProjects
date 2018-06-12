#ifndef TABLEFORM_H
#define TABLEFORM_H

#include <QWidget>

namespace Ui {
class TableForm;
}

class TableForm : public QWidget
{
    Q_OBJECT

public:
    explicit TableForm(QWidget *parent = 0);
    ~TableForm();

private:
    Ui::TableForm *ui;

    void searchInDB();
};

#endif // TABLEFORM_H
