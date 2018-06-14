#include "createlogoform.h"
#include "ui_createlogoform.h"

CreateLogoForm::CreateLogoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateLogoForm)
{
    ui->setupUi(this);
}

CreateLogoForm::~CreateLogoForm()
{
    delete ui;
}
