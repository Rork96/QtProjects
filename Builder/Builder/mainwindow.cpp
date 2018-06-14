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
        setWindowTitle("Builder - Admin groups");
        setMainView(TableForm::groups);
    });
    connect(ui->actionUsers, &QAction::triggered, this, [this] {
        setWindowTitle("Builder - Admin users");
       setMainView(TableForm::users);
    });
    connect(ui->actionTenant, &QAction::triggered, this, [this] {
        setWindowTitle("Builder - Admin tenants");
       setMainView(TableForm::tenant);
    });
    connect(ui->actionLogo, &QAction::triggered, this, [this] {
        setWindowTitle("Builder - Admin logo");
       setMainView(TableForm::logo);
    });
    connect(ui->actionSecurity_filters, &QAction::triggered, this, [this] {
        setWindowTitle("Builder - Security filters");
       setMainView(TableForm::security_filters);
    });
    connect(ui->actionMenu, &QAction::triggered, this, [this] {
        setWindowTitle("Builder - Security filters");
       setMainView(TableForm::menu);
    });
    connect(ui->actionGroup_screens, &QAction::triggered, this, [this] {
        setWindowTitle("Builder - Admin group screen");
       setMainView(TableForm::group_screens);
    });
    connect(ui->actionScreens, &QAction::triggered, this, [this] {
        setWindowTitle("Builder - Admin screen");
       setMainView(TableForm::screens);
    });
    connect(ui->actionDocument_family, &QAction::triggered, this, [this] {
        setWindowTitle("Builder - Document family");
       setMainView(TableForm::document_family);
    });
    connect(ui->actionDocument_groups, &QAction::triggered, this, [this] {
        setWindowTitle("Builder - Admin groups");
       setMainView(TableForm::document_groups);
    });
    connect(ui->actionLists, &QAction::triggered, this, [this] {
        setWindowTitle("Builder - Admin lists");
       setMainView(TableForm::lists);
    });
    connect(ui->actionTemplates, &QAction::triggered, this, [this] {
        setWindowTitle("Builder - Admin templates");
       setMainView(TableForm::templates);
    });

    // Import files
    connect(ui->actionImport_files, &QAction::triggered, this, [this] {
        setWindowTitle("Builder - Import files");
        ImportFilesForm *importForm = new ImportFilesForm(this);
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
    case TableForm::tenant:
        tenantForm = new CreateTenantForm(this);
        setCentralWidget(tenantForm);
        break;
    case TableForm::logo:
        logoForm = new CreateLogoForm(this);
        setCentralWidget(logoForm);
        break;
    case TableForm::security_filters:
        securityFilterForm = new CreateSecurityFilterForm(this);
        setCentralWidget(securityFilterForm);
        break;
    case TableForm::menu:
        menuForm = new CreateMenuForm(this);
        setCentralWidget(menuForm);
        break;
    case TableForm::group_screens:
        groupScreenForm = new CreateGroupScreenForm(this);
        setCentralWidget(groupScreenForm);
        break;
    case TableForm::screens:
        screenForm = new CreateScreeForm(this);
        setCentralWidget(screenForm);
        break;
    case TableForm::document_family:
        docFamilyForm = new CreateDocFamilyForm(this);
        setCentralWidget(docFamilyForm);
        break;
    case TableForm::document_groups:
        docGroupsForm = new CreateDocGroupsForm(this);
        setCentralWidget(docGroupsForm);
        break;
    case TableForm::lists:
        listForm = new CreateListForm(this);
        setCentralWidget(listForm);
        break;
    case TableForm::templates:
        templatesForm = new CreateTemplatesForm(this);
        setCentralWidget(templatesForm);
        break;
    default:
        break;
    }
}
