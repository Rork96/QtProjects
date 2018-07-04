#include "createtemplatesform.h"
#include "ui_createtemplatesform.h"

CreateTemplatesForm::CreateTemplatesForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateTemplatesForm)
{
    ui->setupUi(this);

    initData(Table);

    // View data in lineEdit with mapper
    mapper->addMapping(ui->libraryNameline, 1);
    mapper->addMapping(ui->functionLine, 2);
    mapper->addMapping(ui->tableNameLine, 3);
    mapper->addMapping(ui->tableColumnLine, 4);
    mapper->addMapping(ui->columnTypeLine, 5);
    mapper->addMapping(ui->descriptionEdit, 6);

    model->insertRow(model->rowCount(QModelIndex()));

    mapper->toLast();

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateTemplatesForm::submitChanges);
}

CreateTemplatesForm::~CreateTemplatesForm()
{
    delete ui;
}
