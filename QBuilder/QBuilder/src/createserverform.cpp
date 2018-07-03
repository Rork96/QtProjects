#include "createserverform.h"
#include "ui_createserverform.h"

#include <QSqlQuery>
#include <QMessageBox>

CreateServerForm::CreateServerForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateServerForm)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable(Table);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0, Qt::AscendingOrder);
    model->select();

    // View data in lineEdit with mapper
    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->addMapping(ui->ipAddressLine, 1);
    mapper->addMapping(ui->portLine, 2);
    mapper->addMapping(ui->descrEdit, 3);
    mapper->addMapping(ui->noteEdit, 4);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

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

void CreateServerForm::submitChanges()
{
    // Save changes to database

    mapper->submit();
    model->submitAll();

    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateServerForm::setRowIndex(int rowIndex, int)
{
    // User chose to edit data from the table
    mapper->setCurrentIndex(rowIndex);
}
