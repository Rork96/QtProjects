#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "loginform.h"
#include "tableform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    LoginForm *loginForm;
    TableForm *mainForm;

    void initUI();              // Hide main menu and view login screen
    void Login(bool value);     // Login
};

#endif // MAINWINDOW_H
