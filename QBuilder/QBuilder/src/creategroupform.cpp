#include "creategroupform.h"
#include "ui_creategroupform.h"

#include <QSqlQuery>
#include <QMessageBox>

CreateGroupForm::CreateGroupForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateGroupForm)
{
    ui->setupUi(this);

    ui->submitButton->setEnabled(false); // All columns cannot be blank

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

    // Check all columns
    connect(ui->groupNameLine, &QLineEdit::textChanged, this, [this] {
        ui->submitButton->setEnabled(!ui->groupNameLine->text().isEmpty() && !ui->groupDescrEdit->toPlainText().isEmpty());
    });
}

CreateGroupForm::~CreateGroupForm()
{
    delete ui;
}

void CreateGroupForm::submitChanges()
{
    // Save changes to database

    QSqlQuery query;
    QString str = QString("SELECT EXISTS (SELECT " + Record + " FROM " + Table +
            " WHERE " + Record + " = '%1' AND id != %2 )").arg(ui->groupNameLine->text()).
            arg(model->data(model->index(mapper->currentIndex(), 0), Qt::DisplayRole).toInt());

    query.exec(str);
    query.next();

    // If exists
    if (query.value(0) != 0 && !isEdit) {
        QMessageBox::information(this, trUtf8("Error"), trUtf8("Group name is already exists"));
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
