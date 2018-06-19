#include "createtenantform.h"
#include "ui_createtenantform.h"

CreateTenantForm::CreateTenantForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateTenantForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateTenantForm::submitChanges);
}

CreateTenantForm::~CreateTenantForm()
{
    delete ui;
}

void CreateTenantForm::submitChanges()
{
    // Save changes to database

    // Send sygnal
    emit sygnalSubmit();
}
