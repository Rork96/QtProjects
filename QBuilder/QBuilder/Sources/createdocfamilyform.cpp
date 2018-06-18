#include "../Headers/createdocfamilyform.h"
#include "ui_createdocfamilyform.h"

CreateDocFamilyForm::CreateDocFamilyForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateDocFamilyForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateDocFamilyForm::submitChanges);
}

CreateDocFamilyForm::~CreateDocFamilyForm()
{
    delete ui;
}

void CreateDocFamilyForm::submitChanges()
{
    // Save changes to database

    // Send sygnal
    emit sygnalSubmit();
}
