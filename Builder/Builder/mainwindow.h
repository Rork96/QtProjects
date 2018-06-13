#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "loginform.h"
#include "tableform.h"
#include "creategroupform.h"
#include "createuserform.h"

#include "importfilesform.h"

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
    CreateGroupForm *groupForm;
    CreateUserForm *userForm;

    void initUI();                              // Hide main menu and show login screen
    void login(bool value);                     // Login
    void setMainView(TableForm::Type type);     // Set view type
    void createView(TableForm::Type type);      // Create view in dependency of needed view type
};

#endif // MAINWINDOW_H
