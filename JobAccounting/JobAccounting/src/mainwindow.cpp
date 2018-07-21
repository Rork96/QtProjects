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
    setWindowTitle(appName + " - " + user);
    if (rights == 1) {
        setMainView(); // full access
    }
    else if (rights == 2) {
        // write only mode
        ui->menuBar->setVisible(false);
        editorForm = new EditorForm(this);
        setCentralWidget(editorForm);
        ui->statusBar->showMessage(company);
    }
    else if (rights == 3) {
        // Read only mode
        ui->menuAdministration->setEnabled(false);
        setMainView();
    }
    delete loginForm;
}

void MainWindow::setMainView()
{
    // Show table
    mainForm = new TableForm(this);
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
