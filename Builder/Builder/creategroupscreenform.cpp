#include "creategroupscreenform.h"
#include "ui_creategroupscreenform.h"

CreateGroupScreenForm::CreateGroupScreenForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateGroupScreenForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateGroupScreenForm::submitChanges);
}

CreateGroupScreenForm::~CreateGroupScreenForm()
{
    delete ui;
}

void CreateGroupScreenForm::submitChanges()
{
    // Save changes to database

    // Send sygnal
    emit sygnalSubmit();
}
