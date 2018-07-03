#include "createtemplatesform.h"
#include "ui_createtemplatesform.h"

#include <QSqlQuery>
#include <QMessageBox>

CreateTemplatesForm::CreateTemplatesForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateTemplatesForm)
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
    mapper->addMapping(ui->libraryNameline, 1);
    mapper->addMapping(ui->functionLine, 2);
    mapper->addMapping(ui->tableNameLine, 3);
    mapper->addMapping(ui->tableColumnLine, 4);
    mapper->addMapping(ui->columnTypeLine, 5);
    mapper->addMapping(ui->descriptionEdit, 6);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

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

void CreateTemplatesForm::submitChanges()
{
    // Save changes to database

    QSqlQuery query;
    QString str = QString("SELECT EXISTS (SELECT 'Group name' FROM" + Table +
        " WHERE id NOT LIKE '%1' )").arg(model->data(model->index(mapper->currentIndex(), 0), Qt::DisplayRole).toInt());

    query.prepare(str);
    query.exec();
    query.next();

    // Insert new data
    mapper->submit();
    model->submitAll();

    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateTemplatesForm::setRowIndex(int rowIndex, int)
{
    // User chose to edit data from the table
    mapper->setCurrentIndex(rowIndex);
}
