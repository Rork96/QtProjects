#include "createqueryform.h"
#include "ui_createqueryform.h"

#include <QSqlQuery>
#include <QMessageBox>

CreateQueryForm::CreateQueryForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateQueryForm)
{
    ui->setupUi(this);

    initData(Table);

    // View data in lineEdit with mapper
    mapper->addMapping(ui->nameLine, 1);
    mapper->addMapping(ui->valueEdit, 2);
    mapper->addMapping(ui->paramline, 3);
    mapper->addMapping(ui->descrEdit, 4);

    model->insertRow(model->rowCount(QModelIndex()));

    mapper->toLast();

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateQueryForm::submitChanges);
}

CreateQueryForm::~CreateQueryForm()
{
    delete ui;
}

void CreateQueryForm::submitChanges()
{
    // Save changes to database

    QSqlQuery query;
    QString str = QString("SELECT EXISTS (SELECT 'Group name' FROM" + Table +
        " WHERE '" + Record + "' = '%1' AND id NOT LIKE '%2' )").arg(ui->nameLine->text(),
                    model->data(model->index(mapper->currentIndex(), 0), Qt::DisplayRole).toInt());

    query.prepare(str);
    query.exec();
    query.next();

    // If exists
    if (mapper->currentIndex() > model->rowCount() && query.value(0) != 0) {
        QMessageBox::information(this, trUtf8("Error"), Record + trUtf8(" is already exists"));
        return;
    }
    else {
        // Insert new data
        mapper->submit();
        model->submitAll();
    }
    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}
