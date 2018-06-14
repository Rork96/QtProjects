#include "createmenuform.h"
#include "ui_createmenuform.h"

CreateMenuForm::CreateMenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateMenuForm)
{
    ui->setupUi(this);
}

CreateMenuForm::~CreateMenuForm()
{
    delete ui;
}
