#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>

#include "loginform.h"
#include "tableform.h"
#include <editorform.h>

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
    EditorForm *editorForm;

    QWidget *prewView = nullptr; // Current view
    QString userName;
    int rights;
    const QString company = trUtf8("\t\t© 2018 masterarrows@gmail.com");
    const QString appName = trUtf8("Job Accounting");

    void initUI();                                  // Hide main menu and show login screen
    void login(const QString &user, int rights);    // Login
    void setMainView();                             // Set view type
};

#endif // MAINWINDOW_H
