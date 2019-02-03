#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(QWidget *parent = 0);
    ~InfoDialog();

private:
    Ui::InfoDialog *ui;

signals:
    // Открыть изображение
    void openImg();
    // Во весь экран
    void fullScreen();
    // О программе
    void aboutProgram();
    // О Qt
    void aboutQt();
};

#endif // INFODIALOG_H
