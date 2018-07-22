#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Load translation for system language
    QString localeName = locale().name();
    localeName = localeName.mid(0, localeName.indexOf("_"));
    qtLanguageTranslator.load(QString("translations/") + localeName);
    qApp->installTranslator(&qtLanguageTranslator);

    ui->setupUi(this);

    setWindowState(Qt::WindowMaximized);
    setWindowTitle(appName);
    ui->statusBar->showMessage(company);

    initUI();   // Hide main menu and view login screen

    // region MenuBar connections
    connect(ui->actionLogout, &QAction::triggered, this, &MainWindow::initUI);

    connect(ui->actionJob_accounting, &QAction::triggered, this, [this] {
        setMainView(Main_Table);
    });

    connect(ui->actionWorkers, &QAction::triggered, this, [this] {
        setMainView(Worker_Table);
    });

    connect(ui->actionEquipment, &QAction::triggered, this, [this] {
        setMainView(Equipment_Table);
    });
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
    this->userName = user;
    this->rights = rights;
    setWindowTitle(appName + " - " + userName);
    if (this->rights == 1) {
        setMainView(Main_Table); // full access
    }
    else if (this->rights == 2) {
        // write only mode
        ui->menuBar->setVisible(false);
        editorForm = new EditorForm(this);
        setCentralWidget(editorForm);
        ui->statusBar->showMessage(company);
    }
    else if (this->rights == 3) {
        // Read only mode
        ui->menuAdministration->setEnabled(false);
        setMainView(Main_Table);
    }
    delete loginForm;
}

void MainWindow::setMainView(const QString &table)
{
    // Show table
    mainForm = new TableForm(this, table);
    setCentralWidget(mainForm);
    mainForm->setRights(QString(), rights);
    ui->menuBar->setVisible(true);
    ui->statusBar->showMessage(company);

    // Delete last view
    if (this->prewView != nullptr) {
        delete this->prewView;
        this->prewView = nullptr;
    }
    this->prewView = mainForm;
}
