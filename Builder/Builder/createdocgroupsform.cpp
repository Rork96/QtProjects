#include "createdocgroupsform.h"
#include "ui_createdocgroupsform.h"

CreateDocGroupsForm::CreateDocGroupsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateDocGroupsForm)
{
    ui->setupUi(this);
}

CreateDocGroupsForm::~CreateDocGroupsForm()
{
    delete ui;
}
