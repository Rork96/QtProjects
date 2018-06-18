#include "../Headers/loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

    connect(ui->loginButton, &QPushButton::clicked, this, &LoginForm::checkLogin);
    connect(ui->userLine, &QLineEdit::returnPressed, this, &LoginForm::checkLogin);
    connect(ui->passwordLine, &QLineEdit::returnPressed, this, &LoginForm::checkLogin);

    // Hide worning message in infoLabel
    connect(ui->userLine, &QLineEdit::textChanged, this, [this] {
        ui->infoLabel->clear();
    });
    connect(ui->passwordLine, &QLineEdit::textChanged, this, [this] {
        ui->infoLabel->clear();
    });
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::checkLogin()
{
    QString userName = ui->userLine->text();
    QString password = ui->passwordLine->text();

    // Check userName and password in database ...
    if (userName == "Admin" && password == "123") {
        // Login allowed
        emit isLogin(true);
    }
    else if (userName.isEmpty() || password.isEmpty()) {
        ui->infoLabel->setText("User name or password cannot be blank.");

    }
    else {
        ui->infoLabel->setText("Incorrect username or password.");
    }
}
