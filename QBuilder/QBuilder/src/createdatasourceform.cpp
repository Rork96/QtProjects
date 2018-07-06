#include "createdatasourceform.h"
#include "ui_createdatasourceform.h"

#include <QSqlRelationalDelegate>
#include <QSqlRecord>
#include "basecombomodel.h"

CreateDataSourceForm::CreateDataSourceForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateDataSourceForm)
{
    ui->setupUi(this);

    initData(Table);

    // View data with mapper
    mapper->addMapping(ui->nameLine, 1);
    mapper->addMapping(ui->tableLine, 2);
    mapper->addMapping(ui->descreptionEdit, 3);
    mapper->addMapping(ui->layoutTypeLine, 6);
    mapper->addMapping(ui->relFuncLine, 7);
    mapper->addMapping(ui->relFieldLine, 8);

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

    BaseComboModel *fTypeCModel = new BaseComboModel("func_type", "function_type", this, Table, "function_type", "function_type");
    BaseComboModel *dTypeCModel = new BaseComboModel("direct_type", "direction_type", this, Table, "direction_type", "direction_type");

    int id = -1;
    if (isEdit) {
        id = model->record(mapper->currentIndex()).value("id").toInt();
    }
    fTypeCModel->saveToDB(fTypeCModel->getId(ui->fTypeBox->currentText()), id);
    dTypeCModel->saveToDB(dTypeCModel->getId(ui->dTypeBox->currentText()), id);
    //fTypeCModel->saveToDB(ui->fTypeBox->currentIndex(), id);
    //dTypeCModel->saveToDB(ui->dTypeBox->currentIndex(), id);

    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateDataSourceForm::setRowIndex(int rowIndex, int id)
{
    // User chose to edit data from the table
    BaseForm::setRowIndex(rowIndex, id);

    BaseComboModel *fTypeCModel = new BaseComboModel("func_type", "function_type", this, Table, "function_type", "function_type");
    ui->fTypeBox->setModel(fTypeCModel);
    ui->fTypeBox->setCurrentIndex(fTypeCModel->getIndex(id));

    BaseComboModel *dTypeCModel = new BaseComboModel("direct_type", "direction_type", this, Table, "direction_type", "direction_type");
    ui->dTypeBox->setModel(dTypeCModel);
    ui->dTypeBox->setCurrentIndex(dTypeCModel->getIndex(id));
}
