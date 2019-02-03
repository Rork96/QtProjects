#include "createtemplatesform.h"
#include "ui_createtemplatesform.h"

CreateTemplatesForm::CreateTemplatesForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateTemplatesForm)
{
    ui->setupUi(this);

    ui->submitButton->setEnabled(false); // Library name, table name, function, table column, column type

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

    // Library name, table name, function, table column, column type
    connect(ui->libraryNameline, &QLineEdit::textChanged, this, [this] {
        ui->submitButton->setEnabled(!ui->libraryNameline->text().isEmpty() && !ui->tableNameLine->text().isEmpty());
    });
    connect(ui->tableNameLine, &QLineEdit::textChanged, ui->libraryNameline, &QLineEdit::textChanged);
    connect(ui->functionLine, &QLineEdit::textChanged, ui->libraryNameline, &QLineEdit::textChanged);
    connect(ui->tableColumnLine, &QLineEdit::textChanged, ui->libraryNameline, &QLineEdit::textChanged);
    connect(ui->columnTypeLine, &QLineEdit::textChanged, ui->libraryNameline, &QLineEdit::textChanged);
}

CreateTemplatesForm::~CreateTemplatesForm()
{
    delete ui;
}
