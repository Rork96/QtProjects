#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);

    // Window without frame
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint |
        Qt::WindowCloseButtonHint | // close button
        Qt::WindowSystemMenuHint);
    // Set attributes
    this->setAttribute(Qt::WA_CustomWhatsThis);

    // Port filtration
    QRegExp rx("^[0-9]{3,5}");
    auto validator = new QRegExpValidator(rx, this);
    ui->portLine->setValidator(validator);

    // Program settings (ini in current program directory)
    set = new QSettings("settings.ini", QSettings::IniFormat, this);

    // Load settings
    loadSettings();

    connect(ui->submitButton, &QToolButton::clicked, this, &ConnectionDialog::setConnectParams);
    connect(ui->rejectButton, &QToolButton::clicked, this, [this] { close(); });
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}
void ConnectionDialog::setConnectParams()
{
    // Set parameters to connection to database
    set->setValue("JobAccounting/host", ui->hostLine->text());
    set->setValue("JobAccounting/port", ui->portLine->text());

    close();
}

void ConnectionDialog::loadSettings()
{
    // Load settings
    ui->hostLine->setText(set->value("JobAccounting/host", "localhost").toString());
    ui->portLine->setText(set->value("JobAccounting/port", "5432").toString());
}
