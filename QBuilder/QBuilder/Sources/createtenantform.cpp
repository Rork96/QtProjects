#include "../Headers/createtenantform.h"
#include "ui_createtenantform.h"

CreateTenantForm::CreateTenantForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateTenantForm)
{
    ui->setupUi(this);
}

CreateTenantForm::~CreateTenantForm()
{
    delete ui;
}
