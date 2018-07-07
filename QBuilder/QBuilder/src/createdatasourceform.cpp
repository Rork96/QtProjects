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

    BaseComboModel *fTypeCModel = new BaseComboModel("func_type", "function_type", this, Table, "function_type");
    BaseComboModel *dTypeCModel = new BaseComboModel("direct_type", "direction_type", this, Table, "direction_type");

    int id = -1;
    if (isEdit) {
        id = model->record(mapper->currentIndex()).value("id").toInt();
    }
    fTypeCModel->saveToDB(ui->fTypeBox->itemData(ui->fTypeBox->currentIndex(), Qt::UserRole).toInt(), id);
    dTypeCModel->saveToDB(ui->dTypeBox->itemData(ui->dTypeBox->currentIndex(), Qt::UserRole).toInt(), id);

    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateDataSourceForm::setRowIndex(int rowIndex, int id)
{
    // User chose to edit data from the table
    BaseForm::setRowIndex(rowIndex, id);

    BaseComboModel *fTypeCModel = new BaseComboModel("func_type", "function_type", this, Table, "function_type");
    ui->fTypeBox->setModel(fTypeCModel);
    ui->fTypeBox->setCurrentIndex(ui->fTypeBox->findText(fTypeCModel->getTextValue(id)));

    BaseComboModel *dTypeCModel = new BaseComboModel("direct_type", "direction_type", this, Table, "direction_type");
    ui->dTypeBox->setModel(dTypeCModel);
    ui->dTypeBox->setCurrentIndex(ui->dTypeBox->findText(dTypeCModel->getTextValue(id)));
}
