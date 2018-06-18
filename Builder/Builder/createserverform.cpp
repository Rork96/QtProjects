#include "createserverform.h"
#include "ui_createserverform.h"

CreateServerForm::CreateServerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateServerForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateServerForm::submitChanges);
}

CreateServerForm::~CreateServerForm()
{
    delete ui;
}

void CreateServerForm::submitChanges()
{
    // Save changes to database

    // Send sygnal
    emit sygnalSubmit();
}
