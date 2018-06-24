#include "createextfuncform.h"
#include "ui_createextfuncform.h"

#include <QSqlQuery>
#include <QMessageBox>

CreateExtFuncForm::CreateExtFuncForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateExtFuncForm)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable(TABLE);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0, Qt::AscendingOrder);
    model->select();

    // View data in lineEdit with mapper
    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->addMapping(ui->dataLibLine, 1);
    mapper->addMapping(ui->dataFuncLine, 2);
    mapper->addMapping(ui->extLibLine, 3);
    mapper->addMapping(ui->extFuncLine, 4);
    mapper->addMapping(ui->extFreeMemline, 5);
    //mapper->addMapping(ui->extTypeBox, 6);      // Extension type ? (maybe type integer and link to comboBox, or type integer and link to record un other table)

    QSqlQueryModel *select = new QSqlQueryModel(this);
    select->setQuery("select type from extension_type");
    ui->extTypeBox->setModel(select);

    mapper->addMapping(ui->extTypeBox, model->fieldIndex("Extension type"), "currentIndex");

    //ui->extTypeBox->setCurrentIndex(mapper->currentIndex());

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

void CreateExtFuncForm::setRowIndex(int rowIndex)
{
    // User chose to edit data from the table
    mapper->setCurrentIndex(rowIndex);
}
