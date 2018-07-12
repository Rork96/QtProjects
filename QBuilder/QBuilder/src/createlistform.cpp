#include "createlistform.h"
#include "ui_createlistform.h"

#include <QSqlQuery>
#include <QMessageBox>

CreateListForm::CreateListForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateListForm)
{
    ui->setupUi(this);

    ui->submitButton->setEnabled(false); // Entry name and list name

    initData(Table);

    // View data in lineEdit with mapper
    mapper->addMapping(ui->listNameline, 1);
    mapper->addMapping(ui->descriptionEdit, 2);
    mapper->addMapping(ui->entryNameline, 3);
    mapper->addMapping(ui->groupsLine, 4);
    mapper->addMapping(ui->noteEdit, 5);
    mapper->addMapping(ui->productsLine, 6);
    mapper->addMapping(ui->restrictCodeLine, 7);

    model->insertRow(model->rowCount(QModelIndex()));

    mapper->toLast();

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateListForm::submitChanges);

    // Entry name and list name
    connect(ui->entryNameline, &QLineEdit::textChanged, this, [this] {
        ui->submitButton->setEnabled(!ui->entryNameline->text().isEmpty() && !ui->listNameline->text().isEmpty());
    });
    connect(ui->listNameline, &QLineEdit::textChanged, ui->entryNameline, &QLineEdit::textChanged);
}

CreateListForm::~CreateListForm()
{
    delete ui;
}

void CreateListForm::submitChanges()
{
    // Save changes to database

    QSqlQuery query;
    QString str = QString("SELECT EXISTS (SELECT '" + Record1 + "', '" + Record2 + "' FROM" + Table +
            " WHERE '" + Record1 + "' = '%1', '" + Record2 + "' = '%2' AND id != %3 )").arg(ui->entryNameline->text()).
            arg(ui->listNameline->text()).arg(model->data(model->index(mapper->currentIndex(), 0), Qt::DisplayRole).toInt());

    query.exec(str);
    query.next();

    // If exists
    if (query.value(0) != 0 && !isEdit) {
        QMessageBox::information(this, trUtf8("Error"), trUtf8("List name or entry name is already exists"));
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
