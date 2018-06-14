#include "creategroupscreenform.h"
#include "ui_creategroupscreenform.h"

CreateGroupScreenForm::CreateGroupScreenForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateGroupScreenForm)
{
    ui->setupUi(this);
}

CreateGroupScreenForm::~CreateGroupScreenForm()
{
    delete ui;
}
