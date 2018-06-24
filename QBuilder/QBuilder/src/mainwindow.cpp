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

void MainWindow::createView(TableForm::Type type, int rowIndex)
{
    switch (type) {
    case TableForm::groups:
        groupForm = new CreateGroupForm(this);
        setCentralWidget(groupForm);
        delete mainForm;
        this->prewView = groupForm; // Save current view

        if (rowIndex > -1) {
            groupForm->setRowIndex(rowIndex); // Edit existing data (current selected row index)
        }

        connect(groupForm, &CreateGroupForm::sygnalBack, this, [this, type]() { setMainView(type); });
        connect(groupForm, &CreateGroupForm::sygnalSubmit, this, [this, type]() { setMainView(type); });
        break;
    case TableForm::users:
        userForm = new CreateUserForm(this);
        setCentralWidget(userForm);
        delete mainForm;
        this->prewView = userForm; // Save current view

        if (rowIndex > -1) {
            userForm->setRowIndex(rowIndex); // Edit existing data (current selected row index)
        }

        connect(userForm, &CreateUserForm::sygnalBack, this, [this, type]() { setMainView(type); });
        connect(userForm, &CreateUserForm::sygnalSubmit, this, [this, type]() { setMainView(type); });
        break;
    case TableForm::tenant:
        tenantForm = new CreateTenantForm(this);
        setCentralWidget(tenantForm);
        delete mainForm;
        this->prewView = tenantForm; // Save current view

        connect(tenantForm, &CreateTenantForm::sygnalBack, this, [this, type]() { setMainView(type); });
        connect(tenantForm, &CreateTenantForm::sygnalSubmit, this, [this, type]() { setMainView(type); });
        break;
    case TableForm::logo:
        logoForm = new CreateLogoForm(this);
        setCentralWidget(logoForm);
        delete mainForm;
        this->prewView = logoForm; // Save current view

        connect(logoForm, &CreateLogoForm::sygnalBack, this, [this, type]() { setMainView(type); });
        connect(logoForm, &CreateLogoForm::sygnalSubmit, this, [this, type]() { setMainView(type); });
        break;
    case TableForm::security_filters:
        securityFilterForm = new CreateSecurityFilterForm(this);
        setCentralWidget(securityFilterForm);
        delete mainForm;
        this->prewView = securityFilterForm; // Save current view

        connect(securityFilterForm, &CreateSecurityFilterForm::sygnalBack, this, [this, type]() { setMainView(type); });
        connect(securityFilterForm, &CreateSecurityFilterForm::sygnalSubmit, this, [this, type]() { setMainView(type); });
        break;
    case TableForm::menu:
        menuForm = new CreateMenuForm(this);
        setCentralWidget(menuForm);
        delete mainForm;
        this->prewView = menuForm; // Save current view

        connect(menuForm, &CreateMenuForm::sygnalBack, this, [this, type]() { setMainView(type); });
        connect(menuForm, &CreateMenuForm::sygnalSubmit, this, [this, type]() { setMainView(type); });
        break;
    case TableForm::group_screens:
        groupScreenForm = new CreateGroupScreenForm(this);
        setCentralWidget(groupScreenForm);
        delete mainForm;
        this->prewView = groupScreenForm; // Save current view

        connect(groupScreenForm, &CreateGroupScreenForm::sygnalBack, this, [this, type]() { setMainView(type); });
        connect(groupScreenForm, &CreateGroupScreenForm::sygnalSubmit, this, [this, type]() { setMainView(type); });
        break;
    case TableForm::screens:
        screenForm = new CreateScreeForm(this);
        setCentralWidget(screenForm);
        delete mainForm;
        this->prewView = screenForm; // Save current view

        connect(screenForm, &CreateScreeForm::sygnalBack, this, [this, type]() { setMainView(type); });
        connect(screenForm, &CreateScreeForm::sygnalSubmit, this, [this, type]() { setMainView(type); });
        break;
    case TableForm::document_family:
        docFamilyForm = new CreateDocFamilyForm(this);
        setCentralWidget(docFamilyForm);
        delete mainForm;
        this->prewView = docFamilyForm; // Save current view

        connect(docFamilyForm, &CreateDocFamilyForm::sygnalBack, this, [this, type]() { setMainView(type); });
        connect(docFamilyForm, &CreateDocFamilyForm::sygnalSubmit, this, [this, type]() { setMainView(type); });
        break;
    case TableForm::document_groups:
        docGroupsForm = new CreateDocGroupsForm(this);
        setCentralWidget(docGroupsForm);
        delete mainForm;
        this->prewView = docGroupsForm; // Save current view

        connect(docGroupsForm, &CreateDocGroupsForm::sygnalBack, this, [this, type]() { setMainView(type); });
        connect(docGroupsForm, &CreateDocGroupsForm::sygnalSubmit, this, [this, type]() { setMainView(type); });
        break;
    case TableForm::lists:
        listForm = new CreateListForm(this);
        setCentralWidget(listForm);
        delete mainForm;
        this->prewView = listForm; // Save current view

        if (rowIndex > -1) {
            listForm->setRowIndex(rowIndex); // Edit existing data (current selected row index)
        }

        connect(listForm, &CreateListForm::sygnalBack, this, [this, type]() { setMainView(type); });
        connect(listForm, &CreateListForm::sygnalSubmit, this, [this, type]() { setMainView(type); });
        break;
    case TableForm::templates:
        templatesForm = new CreateTemplatesForm(this);
        setCentralWidget(templatesForm);
        delete mainForm;
        this->prewView = templatesForm; // Save current view

        if (rowIndex > -1) {
            templatesForm->setRowIndex(rowIndex); // Edit existing data (current selected row index)
        }

        connect(templatesForm, &CreateTemplatesForm::sygnalBack, this, [this, type]() { setMainView(type); });
        connect(templatesForm, &CreateTemplatesForm::sygnalSubmit, this, [this, type]() { setMainView(type); });
        break;
    case TableForm::custom_data_sources:
        dataSourceForm = new CreateDataSourceForm(this);
        setCentralWidget(dataSourceForm);
        delete mainForm;
        this->prewView = dataSourceForm; // Save current view

        connect(dataSourceForm, &CreateDataSourceForm::sygnalBack, this, [this, type]() { setMainView(type); });
        connect(dataSourceForm, &CreateDataSourceForm::sygnalSubmit, this, [this, type]() { setMainView(type); });
        break;
    case TableForm::extension_functions:
        extFuncForm = new CreateExtFuncForm(this);
        setCentralWidget(extFuncForm);
        delete mainForm;
        this->prewView = extFuncForm; // Save current view

        if (rowIndex > -1) {
            extFuncForm->setRowIndex(rowIndex); // Edit existing data (current selected row index)
        }

        connect(extFuncForm, &CreateExtFuncForm::sygnalBack, this, [this, type]() { setMainView(type); });
        connect(extFuncForm, &CreateExtFuncForm::sygnalSubmit, this, [this, type]() { setMainView(type); });
        break;
    case TableForm::servers:
        serverForm = new CreateServerForm(this);
        setCentralWidget(serverForm);
        delete mainForm;
        this->prewView = serverForm; // Save current view

        if (rowIndex > -1) {
            serverForm->setRowIndex(rowIndex); // Edit existing data (current selected row index)
        }

        connect(serverForm, &CreateServerForm::sygnalBack, this, [this, type]() { setMainView(type); });
        connect(serverForm, &CreateServerForm::sygnalSubmit, this, [this, type]() { setMainView(type); });
        break;
    case TableForm::security_questions:
        questionForm = new CreateQuestionForm(this);
        setCentralWidget(questionForm);
        delete mainForm;
        this->prewView = questionForm; // Save current view

        if (rowIndex > -1) {
            questionForm->setRowIndex(rowIndex); // Edit existing data (current selected row index)
        }

        connect(questionForm, &CreateQuestionForm::sygnalBack, this, [this, type]() { setMainView(type); });
        connect(questionForm, &CreateQuestionForm::sygnalSubmit, this, [this, type]() { setMainView(type); });
        break;
    case TableForm::custom_query:
        queryForm = new CreateQueryForm(this);
        setCentralWidget(queryForm);
        delete mainForm;
        this->prewView = queryForm; // Save current view

        if (rowIndex > -1) {
            queryForm->setRowIndex(rowIndex); // Edit existing data (current selected row index)
        }

        connect(queryForm, &CreateQueryForm::sygnalBack, this, [this, type]() { setMainView(type); });
        connect(queryForm, &CreateQueryForm::sygnalSubmit, this, [this, type]() { setMainView(type); });
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
