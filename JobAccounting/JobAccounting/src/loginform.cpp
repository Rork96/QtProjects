#include "loginform.h"
#include "ui_loginform.h"
#include "connectiondialog.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

    // Password field (hide password)
    ui->passwordLine->setEchoMode(QLineEdit::Password);

    // Program settings (ini in current program directory)
    set = new QSettings("settings.ini", QSettings::IniFormat, this);
    ui->userLine->setText(set->value("JobAccounting/user", "").toString());

    connect(ui->loginButton, &QPushButton::clicked, this, &LoginForm::checkLogin);
    connect(ui->userLine, &QLineEdit::returnPressed, this, &LoginForm::checkLogin);
    connect(ui->passwordLine, &QLineEdit::returnPressed, this, &LoginForm::checkLogin);

    // Hide warning message in infoLabel
    connect(ui->userLine, &QLineEdit::textChanged, this, [this] {
        ui->infoLabel->clear();
    });
    connect(ui->passwordLine, &QLineEdit::textChanged, this, [this] {
        ui->infoLabel->clear();
    });

    connect(ui->configureBtn, &QPushButton::clicked, this, &LoginForm::configure);
}
void LoginForm::configure()
{
    // Configure database connection
    auto *dlg = new ConnectionDialog(this);
    dlg->exec();
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::checkLogin()
{
    QString userName = ui->userLine->text();
    QString password = ui->passwordLine->text();

    // Check userName and password in database
    db = new DataBase();
    int rights;
    bool result = db->connectToDataBase(userName, password, rights);
    if (result) {
        // Login allowed
        set->setValue("JobAccounting/user", userName);
        emit isLogin(userName, rights);
    }
    else if (userName.isEmpty() || password.isEmpty()) {
        ui->infoLabel->setText(trUtf8("User name or password cannot be blank."));
    }
    else {
        ui->infoLabel->setText(trUtf8("Incorrect username or password."));
    }
}
