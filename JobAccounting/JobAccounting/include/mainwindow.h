#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>

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

protected:
    void changeEvent(QEvent * event) override;
    void translate(QString language);

private:
    Ui::MainWindow *ui;

    QTranslator qtLanguageTranslator;

    LoginForm *loginForm;
    TableForm *mainForm;

    QWidget *prewView = nullptr; // Current view
    QString userName;
    const QString company = "\t\t© 2018 masterarrows@gmail.com";
    const QString appName = "Job Accounting";

    void initUI();                                                  // Hide main menu and show login screen
    void login(const QString &user, const int rights);              // Login
    void setMainView(const int rights);                             // Set view type
    void createView();                                              // Create view in dependency of user rights
};

#endif // MAINWINDOW_H
