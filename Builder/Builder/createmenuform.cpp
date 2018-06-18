#include "createmenuform.h"
#include "ui_createmenuform.h"

CreateMenuForm::CreateMenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateMenuForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateMenuForm::submitChanges);
}

CreateMenuForm::~CreateMenuForm()
{
    delete ui;
}

void CreateMenuForm::submitChanges()
{
    // Save changes to database

    // Send sygnal
    emit sygnalSubmit();
}
