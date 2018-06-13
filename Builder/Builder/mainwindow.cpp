#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowState(Qt::WindowMaximized);

    initUI();   // Hide main menu and view login screen

    connect(loginForm, &LoginForm::isLogin, this, &MainWindow::login);
    connect(ui->actionLogout, &QAction::triggered, this, &MainWindow::initUI);

    connect(ui->actionGroups, &QAction::triggered, this, [this] {
        setMainView(TableForm::groups);
    });
    connect(ui->actionUsers, &QAction::triggered, this, [this] {
       setMainView(TableForm::users);
    });

    // Import files
    connect(ui->actionImport_files, &QAction::triggered, this, [this] {
        ImportFilesForm * importForm = new ImportFilesForm(this);
        setCentralWidget(importForm);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    // Hide main menu and show login screen
    loginForm = new LoginForm(this);
    setCentralWidget(loginForm);
    ui->menuBar->setVisible(false);
}

void MainWindow::login(bool value)
{
    if (value) {
        // Login
        setCentralWidget(nullptr);
        ui->menuBar->setVisible(true);
    }
}

void MainWindow::setMainView(TableForm::Type type)
{
    // Show group table
    mainForm = new TableForm(this);
    mainForm->setViewType(type);
    setCentralWidget(mainForm);

    connect(mainForm, &TableForm::createData, this, &MainWindow::createView);
}

void MainWindow::createView(TableForm::Type type)
{
    switch (type) {
    case TableForm::groups:
        groupForm = new CreateGroupForm(this);
        setCentralWidget(groupForm);
        break;
    case TableForm::users:
        userForm = new CreateUserForm(this);
        setCentralWidget(userForm);
        break;
    default:
        break;
    }
}
