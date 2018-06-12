#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowState(Qt::WindowMaximized);

    initUI();   // Hide main menu and view login screen

    connect(loginForm, &LoginForm::isLogin, this, &MainWindow::Login);
    connect(ui->actionLogout, &QAction::triggered, this, &MainWindow::initUI);
    connect(ui->actionGroups, &QAction::triggered, this, [this] {
        // View group table
        mainForm = new TableForm(this);
        setCentralWidget(mainForm);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    // Hide main menu and view login screen
    loginForm = new LoginForm(this);
    setCentralWidget(loginForm);
    ui->menuBar->setVisible(false);
}

void MainWindow::Login(bool value)
{
    if (value) {
        // Login
        setCentralWidget(NULL);
        ui->menuBar->setVisible(true);
    }
}
