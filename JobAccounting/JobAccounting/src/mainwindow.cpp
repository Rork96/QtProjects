#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Program settings (ini in current program directory)
    set = new QSettings("settings.ini", QSettings::IniFormat, this);

    // Load translations
    QString lang = set->value("JobAccounting/lang", "ru").toString();
    qtLanguageTranslator.load(QString("translations/") + lang);
    qApp->installTranslator(&qtLanguageTranslator);

    ui->setupUi(this);

    setWindowState(Qt::WindowMaximized);
    setWindowTitle(appName);
    ui->statusBar->showMessage(company);

    initUI();   // Hide main menu and view login screen

    // region MenuBar connections
    connect(ui->actionLogout, &QAction::triggered, this, &MainWindow::initUI);

    connect(ui->actionJob_accounting, &QAction::triggered, this, [this] { setMainView(MAIN_TABLE); });

    connect(ui->actionWorkers, &QAction::triggered, this, [this] { setMainView(WORKER_TABLE); });

    connect(ui->actionEquipment, &QAction::triggered, this, [this] { setMainView(EQUIPMENT_TABLE); });

    connect(ui->actionOrders, &QAction::triggered, this, [this] { setMainView(ORDER_TABLE); });

    connect(ui->actionParts, &QAction::triggered, this, [this] { setMainView(PART_TABLE); });
    // endregion MenuBar connections

    // region Translations
    connect(ui->actionEnglish, &QAction::triggered, this, [this] { translate("en"); });
    connect(ui->actionRussian, &QAction::triggered, this, [this] { translate("ru"); });
    connect(ui->actionUkrainian, &QAction::triggered, this, [this] { translate("uk"); });
    // endregion Translations
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *event)
{
    // Change language
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

void MainWindow::translate(QString language)
{
    qtLanguageTranslator.load("translations/" + language, ".");
    qApp->installTranslator(&qtLanguageTranslator);
    set->setValue("JobAccounting/lang", language);
    mainForm->reloadView(); ////////////////////////////
}

void MainWindow::initUI()
{
    // Hide main menu and show login screen
    loginForm = new LoginForm(this);
    setCentralWidget(loginForm);
    ui->menuBar->setVisible(false);

    connect(loginForm, &LoginForm::isLogin, this, &MainWindow::login);

    // Delete last view
    if (this->prewView != nullptr) {
        delete this->prewView;
        this->prewView = nullptr;
    }
}

void MainWindow::login(const QString &user, int rights)
{
    setWindowTitle(appName + " - " + user);
    if (rights == 18) {
        ui->menuBar->setVisible(true);
        ui->actionJob_accounting->setVisible(true);
        ui->actionWorkers->setVisible(true);
        ui->actionEquipment->setVisible(true);
        ui->actionOrders->setVisible(true);
        ui->actionParts->setVisible(true);
        setMainView(MAIN_TABLE); // full access
    }
    else if (rights >= 3 && rights < 18) {
        // write only mode
        ui->menuBar->setVisible(false);
        editorForm = new EditorForm(this);
        setCentralWidget(editorForm);
    }
    else if (rights <= 1) {
        // Read only mode
        ui->actionJob_accounting->setVisible(false);
        ui->actionWorkers->setVisible(false);
        ui->actionEquipment->setVisible(false);
        ui->actionOrders->setVisible(false);
        ui->actionParts->setVisible(false);
        setMainView(ACCOUNT_TABLE);
    }
    delete loginForm;
    ui->statusBar->showMessage(company);
}

void MainWindow::setMainView(const QString &table)
{
    // Show table
    if (table == ACCOUNT_TABLE) {
        accountForm = new AccountForm(this);
        setCentralWidget(accountForm);
    }
    else {
        mainForm = new TableForm(this, table);
        setCentralWidget(mainForm);
    }
    ui->menuBar->setVisible(true);
    ui->statusBar->showMessage(company);

    // Delete last view
    if (this->prewView != nullptr) {
        delete this->prewView;
        this->prewView = nullptr;
    }
    this->prewView = mainForm;
}
