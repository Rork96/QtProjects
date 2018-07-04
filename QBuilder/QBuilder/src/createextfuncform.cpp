#include "createextfuncform.h"
#include "ui_createextfuncform.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>
#include "basecombomodel.h"

CreateExtFuncForm::CreateExtFuncForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateExtFuncForm)
{
    ui->setupUi(this);

    initData(Table);

    // Set relation between tables
    int typeIndex = model->fieldIndex("extension_type");
    model->setRelation(typeIndex, QSqlRelation("extension_type", "id", "type"));
    model->select();

    // New relation model for combobox
    QSqlTableModel *relModel = model->relationModel(typeIndex); // Relation index
    ui->extTypeBox->setModel(relModel);
    ui->extTypeBox->setModelColumn(relModel->fieldIndex("type"));

    // View data with mapper
    mapper->addMapping(ui->dataLibLine, 1);
    mapper->addMapping(ui->dataFuncLine, 2);
    mapper->addMapping(ui->extLibLine, 3);
    mapper->addMapping(ui->extFuncLine, 4);
    mapper->addMapping(ui->extFreeMemline, 5);
    mapper->addMapping(ui->extTypeBox, typeIndex);    // Relation by index

    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateExtFuncForm::submitChanges);
}

CreateExtFuncForm::~CreateExtFuncForm()
{
    delete ui;
}

void CreateExtFuncForm::submitChanges()
{
    // Save changes to database
    mapper->submit();
    model->submitAll();

    BaseComboModel *extTypeCModel = new BaseComboModel("type", "extension_type", this, Table, "extension_type");

    int id = -1;
    if (isEdit) {
        id = model->record(mapper->currentIndex()).value("id").toInt();
    }
    extTypeCModel->saveToDB(ui->extTypeBox->currentIndex(), id);

    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateExtFuncForm::setRowIndex(int rowIndex, int id)
{
    // User chose to edit data from the table
    BaseForm::setRowIndex(rowIndex, id);

    BaseComboModel *extTypeCModel = new BaseComboModel("type", "extension_type", this, Table, "extension_type");
    ui->extTypeBox->setModel(extTypeCModel);
    ui->extTypeBox->setCurrentIndex(extTypeCModel->getIndex(id));
}
