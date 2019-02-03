#include "createqueryform.h"
#include "ui_createqueryform.h"

#include <QSqlQuery>
#include <QMessageBox>

CreateQueryForm::CreateQueryForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateQueryForm)
{
    ui->setupUi(this);

    ui->submitButton->setEnabled(false); // Query name

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

    // Query name
    connect(ui->nameLine, &QLineEdit::textChanged, this, [this] {
        ui->submitButton->setEnabled(!ui->nameLine->text().isEmpty());
    });
}

CreateQueryForm::~CreateQueryForm()
{
    delete ui;
}

void CreateQueryForm::submitChanges()
{
    // Save changes to database

    QSqlQuery query;
    QString str = QString("SELECT EXISTS (SELECT '" + Record + "' FROM " + Table +
            " WHERE '" + Record + "' = '%1' AND id NOT LIKE '%2' )").arg(ui->nameLine->text()).
            arg(model->data(model->index(mapper->currentIndex(), 0), Qt::DisplayRole).toInt());

    query.exec(str);
    query.next();

    // If exists
    if (query.value(0) != 0 && !isEdit) {
        QMessageBox::information(this, trUtf8("Error"), trUtf8("Query name is already exists"));
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
