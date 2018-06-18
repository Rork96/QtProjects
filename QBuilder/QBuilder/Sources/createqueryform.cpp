#include "../Headers/createqueryform.h"
#include "ui_createqueryform.h"

CreateQueryForm::CreateQueryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateQueryForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateQueryForm::submitChanges);
}

CreateQueryForm::~CreateQueryForm()
{
    delete ui;
}

void CreateQueryForm::submitChanges()
{
    // Save changes to database

    // Send sygnal
    emit sygnalSubmit();
}
