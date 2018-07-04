#include "createserverform.h"
#include "ui_createserverform.h"

CreateServerForm::CreateServerForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateServerForm)
{
    ui->setupUi(this);

    initData(Table);

    mapper->addMapping(ui->ipAddressLine, 1);
    mapper->addMapping(ui->portLine, 2);
    mapper->addMapping(ui->descrEdit, 3);
    mapper->addMapping(ui->noteEdit, 4);

    model->insertRow(model->rowCount(QModelIndex()));

    mapper->toLast();

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
        emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateServerForm::submitChanges);
}

CreateServerForm::~CreateServerForm()
{
    delete ui;
}
