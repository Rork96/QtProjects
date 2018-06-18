#include "createdatasourceform.h"
#include "ui_createdatasourceform.h"

CreateDataSourceForm::CreateDataSourceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateDataSourceForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateDataSourceForm::submitChanges);
}

CreateDataSourceForm::~CreateDataSourceForm()
{
    delete ui;
}

void CreateDataSourceForm::submitChanges()
{
    // Save changes to database

    // Send sygnal
    emit sygnalSubmit();
}
