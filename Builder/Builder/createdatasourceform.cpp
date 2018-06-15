#include "createdatasourceform.h"
#include "ui_createdatasourceform.h"

CreateDataSourceForm::CreateDataSourceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateDataSourceForm)
{
    ui->setupUi(this);
}

CreateDataSourceForm::~CreateDataSourceForm()
{
    delete ui;
}
