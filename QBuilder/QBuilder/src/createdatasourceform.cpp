#include "createdatasourceform.h"
#include "ui_createdatasourceform.h"

#include <QMessageBox>
#include <QSqlRelationalDelegate>

CreateDataSourceForm::CreateDataSourceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateDataSourceForm)
{
    ui->setupUi(this);

    model = new QSqlRelationalTableModel(this);
    model->setTable(TABLE);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0, Qt::AscendingOrder);

    // Set relation between tables
    int funcTypeIndex = model->fieldIndex("Function type");
    model->setRelation(funcTypeIndex, QSqlRelation("function_type", "id", "func_type"));
    int directTypeIndex = model->fieldIndex("Direction type");
    model->setRelation(directTypeIndex, QSqlRelation("direction_type", "id", "direct_type"));

    model->select();

    // New relation model for fTypeBox
    QSqlTableModel *relModel = model->relationModel(funcTypeIndex); // Relation index
    ui->fTypeBox->setModel(relModel);
    ui->fTypeBox->setModelColumn(relModel->fieldIndex("func_type"));

    // New relation model for dTypeBox
    QSqlTableModel *rModel = model->relationModel(directTypeIndex); // Relation index
    ui->dTypeBox->setModel(rModel);
    ui->dTypeBox->setModelColumn(rModel->fieldIndex("direct_type"));

    // Mapper
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    // View data with mapper
    mapper->addMapping(ui->nameLine, 1);
    mapper->addMapping(ui->tableLine, 2);
    mapper->addMapping(ui->descreptionEdit, 3);
    mapper->addMapping(ui->fTypeBox, funcTypeIndex);        // Relation by index
    mapper->addMapping(ui->dTypeBox, directTypeIndex);      // Relation by index
    mapper->addMapping(ui->layoutTypeLine, 6);
    mapper->addMapping(ui->relFuncLine, 7);
    mapper->addMapping(ui->relFieldLine, 8);

    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateDataSourceForm::submitChanges);
}

CreateDataSourceForm::~CreateDataSourceForm()
{
    delete ui;
}

void CreateDataSourceForm::submitChanges()
{
    // Save changes to database

    mapper->submit();
    model->submitAll();

    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateDataSourceForm::setRowIndex(int rowIndex)
{
    // User chose to edit data from the table
    mapper->setCurrentIndex(rowIndex);
}
