#include "../Headers/createextfuncform.h"
#include "ui_createextfuncform.h"

CreateExtFuncForm::CreateExtFuncForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateExtFuncForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateExtFuncForm::submitChanges);
}

CreateExtFuncForm::~CreateExtFuncForm()
{
    delete ui;
}

void CreateExtFuncForm::submitChanges()
{
    // Save changes to database

    // Send sygnal
    emit sygnalSubmit();
}
