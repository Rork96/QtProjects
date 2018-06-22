#include "creategroupform.h"
#include "ui_creategroupform.h"

#include <QSqlQuery>
#include <QMessageBox>

CreateGroupForm::CreateGroupForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateGroupForm)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable("admin_groups");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    // Отображение данных в lineEdit через mapper
    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->addMapping(ui->groupNameLine, 1);
    mapper->addMapping(ui->groupDescrEdit, 2);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

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
    QString str = QString("SELECT EXISTS (SELECT 'Group name' FROM admin_groups"
            " WHERE 'Group name' = '%1' AND key NOT LIKE '%2' )").arg(ui->groupNameLine->text(),
         model->data(model->index(mapper->currentIndex(), 0),
                     Qt::DisplayRole).toString());

    query.prepare(str);
    query.exec();
    query.next();

    // If exists
    if(query.value(0) != 0) {
        QMessageBox::information(this, trUtf8("Error"),
                                 trUtf8("Group name is already exists"));
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
