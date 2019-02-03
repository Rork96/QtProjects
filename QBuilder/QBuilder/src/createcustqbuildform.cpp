#include "createcustqbuildform.h"
#include "ui_createcustqbuildform.h"

CreateCustQBuildForm::CreateCustQBuildForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateCustQBuildForm)
{
    ui->setupUi(this);
    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateCustQBuildForm::submitChanges);
}

CreateCustQBuildForm::~CreateCustQBuildForm()
{
    delete ui;
}

void CreateCustQBuildForm::submitChanges()
{
    // Save changes to database

    // Send sygnal
    emit sygnalSubmit();
}

