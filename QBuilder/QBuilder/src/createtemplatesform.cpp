#include "createtemplatesform.h"
#include "ui_createtemplatesform.h"

CreateTemplatesForm::CreateTemplatesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateTemplatesForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateTemplatesForm::submitChanges);
}

CreateTemplatesForm::~CreateTemplatesForm()
{
    delete ui;
}

void CreateTemplatesForm::submitChanges()
{
    // Save changes to database

    // Send sygnal
    emit sygnalSubmit();
}
