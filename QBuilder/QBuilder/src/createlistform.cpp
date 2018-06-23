#include "createlistform.h"
#include "ui_createlistform.h"

#include <QSqlQuery>
#include <QMessageBox>

CreateListForm::CreateListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateListForm)
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
    mapper->addMapping(ui->listNameline, 1);
    mapper->addMapping(ui->descriptionEdit, 2);
    mapper->addMapping(ui->entryNameline, 3);
    mapper->addMapping(ui->groupsLine, 4);
    mapper->addMapping(ui->noteEdit, 5);
    mapper->addMapping(ui->productsLine, 6);
    mapper->addMapping(ui->restrictCodeLine, 7);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    model->insertRow(model->rowCount(QModelIndex()));

    mapper->toLast();

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateListForm::submitChanges);
}

CreateListForm::~CreateListForm()
{
    delete ui;
}

void CreateListForm::submitChanges()
{
    // Save changes to database

    QSqlQuery query;
    QString str = QString("SELECT EXISTS (SELECT 'Group name' FROM" TABLE
                          " WHERE '" RECORD "' = '%1' AND id NOT LIKE '%2' )").arg(ui->entryNameline->text(),
                                      model->data(model->index(mapper->currentIndex(), 0), Qt::DisplayRole).toInt());

    query.prepare(str);
    query.exec();
    query.next();

    // If exists
    if (mapper->currentIndex() > model->rowCount() && query.value(0) != 0) {
        QMessageBox::information(this, trUtf8("Error"),
                                 trUtf8(RECORD " is already exists"));
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

void CreateListForm::setRowIndex(int rowIndex)
{
    // User chose to edit data from the table
    mapper->setCurrentIndex(rowIndex);
}