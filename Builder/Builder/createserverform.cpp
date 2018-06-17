#include "createserverform.h"
#include "ui_createserverform.h"

CreateServerForm::CreateServerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateServerForm)
{
    ui->setupUi(this);
}

CreateServerForm::~CreateServerForm()
{
    delete ui;
}
