#include "creategroupform.h"
#include "ui_creategroupform.h"

CreateGroupForm::CreateGroupForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateGroupForm)
{
    ui->setupUi(this);
}

CreateGroupForm::~CreateGroupForm()
{
    delete ui;
}
