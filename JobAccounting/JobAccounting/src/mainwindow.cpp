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
}

void MainWindow::login(const QString &user, const int rights)
{
    this->userName = user;
    if (rights != 3) {
        setMainView(rights); // edit and read / write mode
    }
    else {
        // Read only mode
    }
    delete loginForm;
}

void MainWindow::setMainView(const int rights)
{
    // Show table
    mainForm = new TableForm(this);
    setCentralWidget(mainForm);
    ui->menuBar->setVisible(true);
    ui->statusBar->showMessage(company);

    // Delete last view
    if (this->prewView != nullptr) {
        delete this->prewView;
        this->prewView = nullptr;
    }
}
