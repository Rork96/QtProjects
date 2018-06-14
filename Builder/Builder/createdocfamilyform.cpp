#include "createdocfamilyform.h"
#include "ui_createdocfamilyform.h"

CreateDocFamilyForm::CreateDocFamilyForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateDocFamilyForm)
{
    ui->setupUi(this);
}

CreateDocFamilyForm::~CreateDocFamilyForm()
{
    delete ui;
}
