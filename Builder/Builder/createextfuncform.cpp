#include "createextfuncform.h"
#include "ui_createextfuncform.h"

CreateExtFuncForm::CreateExtFuncForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateExtFuncForm)
{
    ui->setupUi(this);
}

CreateExtFuncForm::~CreateExtFuncForm()
{
    delete ui;
}
