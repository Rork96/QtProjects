#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QSettings>
#include "loginform.h"
#include "tableform.h"
#include "editorform.h"
#include "accountform.h"

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

    QSettings *set;
    QTranslator qtLanguageTranslator;

    LoginForm *loginForm;
    TableForm *mainForm;
    EditorForm *editorForm;
    AccountForm *accountForm;
    QWidget *prewView = nullptr; // Current view

    const QString company = trUtf8("\t\t© 2018 masterarrows@gmail.com");
    const QString appName = trUtf8("Job Accounting");

    void initUI();                                          // Hide main menu and show login screen
    void login(const QString &user, int rights);            // Login
    void setMainView(const QString &table);  // Set view type
};

#endif // MAINWINDOW_H
