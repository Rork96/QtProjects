#include "createdocgroupsform.h"
#include "ui_createdocgroupsform.h"

CreateDocGroupsForm::CreateDocGroupsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateDocGroupsForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateDocGroupsForm::submitChanges);
}

CreateDocGroupsForm::~CreateDocGroupsForm()
{
    delete ui;
}

void CreateDocGroupsForm::submitChanges()
{
    // Save changes to database

    // Send sygnal
    emit sygnalSubmit();
}
