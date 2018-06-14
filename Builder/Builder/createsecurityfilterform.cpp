#include "createsecurityfilterform.h"
#include "ui_createsecurityfilterform.h"

CreateSecurityFilterForm::CreateSecurityFilterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateSecurityFilterForm)
{
    ui->setupUi(this);
}

CreateSecurityFilterForm::~CreateSecurityFilterForm()
{
    delete ui;
}
