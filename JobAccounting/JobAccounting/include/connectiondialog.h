#ifndef connectiondialog_H
#define connectiondialog_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = 0);
    ~ConnectionDialog();

private:
    Ui::ConnectionDialog *ui;

    QSettings *set;

    void loadSettings();        // Load settings
    void setConnectParams();    // Set parameters to connection to database
};

#endif //connectiondialog_H
