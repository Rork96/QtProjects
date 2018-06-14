#include "createtemplatesform.h"
#include "ui_createtemplatesform.h"

CreateTemplatesForm::CreateTemplatesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateTemplatesForm)
{
    ui->setupUi(this);
}

CreateTemplatesForm::~CreateTemplatesForm()
{
    delete ui;
}
