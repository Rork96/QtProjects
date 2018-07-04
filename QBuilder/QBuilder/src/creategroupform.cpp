#include "creategroupform.h"
#include "ui_creategroupform.h"

#include <QSqlQuery>
#include <QMessageBox>

CreateGroupForm::CreateGroupForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateGroupForm)
{
    ui->setupUi(this);

    initData(Table);

    // View data in lineEdit with mapper
    mapper->addMapping(ui->groupNameLine, 1);
    mapper->addMapping(ui->groupDescrEdit, 2);

    model->insertRow(model->rowCount(QModelIndex()));

    mapper->toLast();

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateGroupForm::submitChanges);
}

CreateGroupForm::~CreateGroupForm()
{
    delete ui;
}

void CreateGroupForm::submitChanges()
{
    // Save changes to database

    QSqlQuery query;
    QString str = QString("SELECT EXISTS (SELECT 'Group name' FROM" + Table +
            " WHERE '" + Record + "' = '%1' AND id NOT LIKE '%2' )").arg(ui->groupNameLine->text(),
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

    // Send signal
    emit sygnalSubmit();
}
