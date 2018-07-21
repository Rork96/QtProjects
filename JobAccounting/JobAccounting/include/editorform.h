#ifndef EditorForm_H
#define EditorForm_H

#include <QWidget>

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
};

#endif //EditorForm_H
