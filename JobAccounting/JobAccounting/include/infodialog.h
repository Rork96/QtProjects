#ifndef InfoDialog_H
#define InfoDialog_H

#include <QDialog>

namespace Ui
{
class InfoDialog;
}

class InfoDialog: public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(QWidget *parent = 0, int id = 0);
    ~InfoDialog();

private:
    Ui::InfoDialog *ui;
};

#endif //InfoDialog_H
