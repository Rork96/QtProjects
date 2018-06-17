#include "createqueryform.h"
#include "ui_createqueryform.h"

CreateQueryForm::CreateQueryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateQueryForm)
{
    ui->setupUi(this);
}

CreateQueryForm::~CreateQueryForm()
{
    delete ui;
}
