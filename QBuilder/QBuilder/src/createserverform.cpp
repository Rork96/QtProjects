#include "createserverform.h"
#include "ui_createserverform.h"

CreateServerForm::CreateServerForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateServerForm)
{
    ui->setupUi(this);

    ui->submitButton->setEnabled(false); // IP address, port

    initData(Table);

    mapper->addMapping(ui->ipAddressLine, 1);
    mapper->addMapping(ui->portLine, 2);
    mapper->addMapping(ui->descrEdit, 3);
    mapper->addMapping(ui->noteEdit, 4);

    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();

    // IP address filtration
    QRegExp rgx("^[0-9]{3}[.][0-9]{3}[.][0-9]{1,3}[.][0-9]{1,3}");
    QRegExpValidator *validat = new QRegExpValidator(rgx, this);
    ui->ipAddressLine->setValidator(validat);

    // Port filtration
    QRegExp rx("^[0-9]{3,5}");
    QRegExpValidator *validator = new QRegExpValidator(rx, this);
    ui->portLine->setValidator(validator);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
        emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateServerForm::submitChanges);

    // IP address, port
    connect(ui->ipAddressLine, &QLineEdit::textChanged, this, [this] {
        ui->submitButton->setEnabled(!ui->ipAddressLine->text().isEmpty() && !ui->portLine->text().isEmpty());
    });
    connect(ui->portLine, &QLineEdit::textChanged, ui->ipAddressLine, &QLineEdit::textChanged);
}

CreateServerForm::~CreateServerForm()
{
    delete ui;
}
