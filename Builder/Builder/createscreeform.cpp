#include "createscreeform.h"
#include "ui_createscreeform.h"

CreateScreeForm::CreateScreeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateScreeForm)
{
    ui->setupUi(this);
}

CreateScreeForm::~CreateScreeForm()
{
    delete ui;
}
