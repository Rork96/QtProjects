#include "createsecurityfilterform.h"
#include "ui_createsecurityfilterform.h"

CreateSecurityFilterForm::CreateSecurityFilterForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateSecurityFilterForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateSecurityFilterForm::submitChanges);
}

CreateSecurityFilterForm::~CreateSecurityFilterForm()
{
    delete ui;
}

void CreateSecurityFilterForm::submitChanges()
{
    // Save changes to database

    // Send sygnal
    emit sygnalSubmit();
}

void CreateSecurityFilterForm::setRowIndex(int rowIndex, int)
{
    // User chose to edit data from the table
    mapper->setCurrentIndex(rowIndex);
}
