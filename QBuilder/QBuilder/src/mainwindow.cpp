#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowState(Qt::WindowMaximized);
    setWindowTitle("Application");
    ui->statusBar->showMessage("\t\t© 2018 Company.");

    initUI();   // Hide main menu and view login screen

    // region MenuBar connections

    connect(ui->actionLogout, &QAction::triggered, this, &MainWindow::initUI);

    connect(ui->actionGroups, &QAction::triggered, this, [this] {
        setWindowTitle("Application - Admin groups");
        setMainView(TableForm::groups);
    });
    connect(ui->actionUsers, &QAction::triggered, this, [this] {
        setWindowTitle("Application - Admin users");
        setMainView(TableForm::users);
    });
    connect(ui->actionTenant, &QAction::triggered, this, [this] {
        setWindowTitle("Application - Admin tenants");
        setMainView(TableForm::tenant);
    });
    connect(ui->actionLogo, &QAction::triggered, this, [this] {
        setWindowTitle("Application - Admin logo");
        setMainView(TableForm::logo);
    });
    connect(ui->actionSecurity_filters, &QAction::triggered, this, [this] {
        setWindowTitle("Application - Security filters");
        setMainView(TableForm::security_filters);
    });
    connect(ui->actionMenu, &QAction::triggered, this, [this] {
        setWindowTitle("Application - Security filters");
        setMainView(TableForm::menu);
    });
    connect(ui->actionGroup_screens, &QAction::triggered, this, [this] {
        setWindowTitle("Application - Admin group screen");
        setMainView(TableForm::group_screens);
    });
    connect(ui->actionScreens, &QAction::triggered, this, [this] {
        setWindowTitle("Application - Admin screen");
        setMainView(TableForm::screens);
    });
    connect(ui->actionDocument_family, &QAction::triggered, this, [this] {
        setWindowTitle("Application - Document family");
        setMainView(TableForm::document_family);
    });
    connect(ui->actionDocument_groups, &QAction::triggered, this, [this] {
        setWindowTitle("Application - Admin groups");
        setMainView(TableForm::document_groups);
    });
    connect(ui->actionLists, &QAction::triggered, this, [this] {
        setWindowTitle("Application - Admin lists");
        setMainView(TableForm::lists);
    });
    connect(ui->actionTemplates, &QAction::triggered, this, [this] {
        setWindowTitle("Application - Admin templates");
        setMainView(TableForm::templates);
    });
    connect(ui->actionCustom_data_sourcess, &QAction::triggered, this, [this] {
        setWindowTitle("Application - Admin templates");
        setMainView(TableForm::custom_data_sources);
    });
    connect(ui->actionExtention_functions, &QAction::triggered, this, [this] {
        setWindowTitle("Application - Admin extension functions");
        setMainView(TableForm::extension_functions);
    });
    connect(ui->actionServers, &QAction::triggered, this, [this] {
        setWindowTitle("Application - Admin servers");
        setMainView(TableForm::servers);
    });
    connect(ui->actionSecuriry_questions, &QAction::triggered, this, [this] {
        setWindowTitle("Application - Admin lists");
        setMainView(TableForm::security_questions);
    });
    connect(ui->actionCustom_query, &QAction::triggered, this, [this] {
        setWindowTitle("Application - Custom query");
        setMainView(TableForm::custom_query);
    });


    // Import files
    connect(ui->actionImport_files, &QAction::triggered, this, [this] {
        setWindowTitle("Application - Import files");
        importForm = new ImportFilesForm(this);
        setCentralWidget(importForm);
    });

    // endregion MenuBar connections
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

    connect(loginForm, &LoginForm::isLogin, this, &MainWindow::login);
}

void MainWindow::login()
{
    setCentralWidget(nullptr);
    ui->menuBar->setVisible(true);
    delete loginForm;
}

void MainWindow::setMainView(TableForm::Type type)
{
    // Show table
    mainForm = new TableForm(this);
    mainForm->setViewType(type);
    setCentralWidget(mainForm);

    connect(mainForm, &TableForm::createData, this, &MainWindow::createView);

    if (type == TableForm::Type::screens || type == TableForm::Type::custom_query) {
        connect(mainForm, &TableForm::createDataWithBuilder, this, &MainWindow::createViewWithBuilder);
    }

    // Delete last view
    if (this->prewView != nullptr) {
        delete this->prewView;
        this->prewView = nullptr;
    }
}

void MainWindow::createView(TableForm::Type type, int rowIndex, int id)
{
    auto initForm = [this, &rowIndex, &type](auto form) {
    //auto initForm = [this](auto form) {
        setCentralWidget(form);
        delete mainForm;
        this->prewView = form;  // Save current view

        if (rowIndex > -1) {
            form->setRowIndex(rowIndex);    // Edit existing data (current selected row index)
        }
        /*else {
            form->setRowIndex(rowIndex, -1);
        }*/

        connect(form, &CreateUserForm::sygnalBack, this, [this, type]() { setMainView(type); });
        connect(form, &CreateUserForm::sygnalSubmit, this, [this, type]() { setMainView(type); });
    };

    switch (type) {
    case TableForm::groups:
        groupForm = new CreateGroupForm(this);
        initForm(groupForm);
        break;
    case TableForm::users:
        userForm = new CreateUserForm(this);
        initForm(userForm);
        break;
    case TableForm::tenant:
        tenantForm = new CreateTenantForm(this);
        initForm(tenantForm);
        break;
    case TableForm::logo:
        logoForm = new CreateLogoForm(this);
        initForm(logoForm);
        break;
    case TableForm::security_filters:
        securityFilterForm = new CreateSecurityFilterForm(this);
        initForm(securityFilterForm);
        break;
    case TableForm::menu:
        menuForm = new CreateMenuForm(this);
        initForm(menuForm);
        break;
    case TableForm::group_screens:
        groupScreenForm = new CreateGroupScreenForm(this);
        initForm(groupScreenForm);
        break;
    case TableForm::screens:
        screenForm = new CreateScreeForm(this);
        initForm(screenForm);
        break;
    case TableForm::document_family:
        docFamilyForm = new CreateDocFamilyForm(this);
        initForm(docFamilyForm);
        break;
    case TableForm::document_groups:
        docGroupsForm = new CreateDocGroupsForm(this);
        initForm(docGroupsForm);
        break;
    case TableForm::lists:
        listForm = new CreateListForm(this);
        initForm(listForm);
        break;
    case TableForm::templates:
        templatesForm = new CreateTemplatesForm(this);
        initForm(templatesForm);
        break;
    case TableForm::custom_data_sources:
        dataSourceForm = new CreateDataSourceForm(this);
        initForm(dataSourceForm);
        break;
    case TableForm::extension_functions:
        extFuncForm = new CreateExtFuncForm(this);
        initForm(extFuncForm);
        break;
    case TableForm::servers:
        serverForm = new CreateServerForm(this);
        initForm(serverForm);
        break;
    case TableForm::security_questions:
        questionForm = new CreateQuestionForm(this);
        initForm(questionForm);
        break;
    case TableForm::custom_query:
        queryForm = new CreateQueryForm(this);
        initForm(queryForm);
        break;
    default:
        break;
    }
}

void MainWindow::createViewWithBuilder(TableForm::Type type)
{
    switch (type) {
    case TableForm::screens:
        scrBuilderForm = new CreateScrBuilderForm(this);
        setCentralWidget(scrBuilderForm);
        delete mainForm;
        this->prewView = scrBuilderForm; // Save current view

        connect(scrBuilderForm, &CreateScrBuilderForm::sygnalBack, this, [this, type]() { setMainView(type); });
        break;
    case TableForm::custom_query:
        custQBuilder = new CreateCustQBuildForm(this);
        setCentralWidget(custQBuilder);
        delete mainForm;
        this->prewView = custQBuilder; // Save current view

        connect(custQBuilder, &CreateCustQBuildForm::sygnalBack, this, [this, type]() { setMainView(type); });
        connect(custQBuilder, &CreateCustQBuildForm::sygnalSubmit, this, [this, type]() { setMainView(type); });
        break;
    default:
        break;
    }
}
