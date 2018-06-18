#include "../Headers/createlogoform.h"
#include "ui_createlogoform.h"

CreateLogoForm::CreateLogoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateLogoForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateLogoForm::submitChanges);
}

CreateLogoForm::~CreateLogoForm()
{
    delete ui;
}

void CreateLogoForm::submitChanges()
{
    // Save changes to database

    // Send sygnal
    emit sygnalSubmit();
}
