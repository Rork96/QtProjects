#include "createlistform.h"
#include "ui_createlistform.h"

CreateListForm::CreateListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateListForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateListForm::submitChanges);
}

CreateListForm::~CreateListForm()
{
    delete ui;
}

void CreateListForm::submitChanges()
{
    // Save changes to database

    // Send sygnal
    emit sygnalSubmit();
}
