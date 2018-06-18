#include "creategroupform.h"
#include "ui_creategroupform.h"

CreateGroupForm::CreateGroupForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateGroupForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateGroupForm::submitChanges);
}

CreateGroupForm::~CreateGroupForm()
{
    delete ui;
}

void CreateGroupForm::submitChanges()
{
    // Save changes to database

    // Send sygnal
    emit sygnalSubmit();
}
