#include "createextfuncform.h"
#include "ui_createextfuncform.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlRelationalDelegate>

CreateExtFuncForm::CreateExtFuncForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateExtFuncForm)
{
    ui->setupUi(this);

    model = new QSqlRelationalTableModel(this);
    model->setTable(Table);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0, Qt::AscendingOrder);

    // Set relation between tables
    int typeIndex = model->fieldIndex("Extension type");
    model->setRelation(typeIndex, QSqlRelation("extension_type", "id", "type"));
    model->select();

    // New relation model for combobox
    QSqlTableModel *relModel = model->relationModel(typeIndex); // Relation index
    ui->extTypeBox->setModel(relModel);
    ui->extTypeBox->setModelColumn(relModel->fieldIndex("type"));

    // Mapper
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    // View data with mapper
    mapper->addMapping(ui->dataLibLine, 1);
    mapper->addMapping(ui->dataFuncLine, 2);
    mapper->addMapping(ui->extLibLine, 3);
    mapper->addMapping(ui->extFuncLine, 4);
    mapper->addMapping(ui->extFreeMemline, 5);
    mapper->addMapping(ui->extTypeBox, typeIndex);    // Relation by index

    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
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

    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateExtFuncForm::setRowIndex(int rowIndex, int)
{
    // User chose to edit data from the table
    mapper->setCurrentIndex(rowIndex);
}
