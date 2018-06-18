#include "createscreeform.h"
#include "ui_createscreeform.h"

CreateScreeForm::CreateScreeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateScreeForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateScreeForm::submitChanges);
}

CreateScreeForm::~CreateScreeForm()
{
    delete ui;
}

void CreateScreeForm::submitChanges()
{
    // Save changes to database

    // Send sygnal
    emit sygnalSubmit();
}
