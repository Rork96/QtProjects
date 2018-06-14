#include "createlistform.h"
#include "ui_createlistform.h"

CreateListForm::CreateListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateListForm)
{
    ui->setupUi(this);
}

CreateListForm::~CreateListForm()
{
    delete ui;
}
