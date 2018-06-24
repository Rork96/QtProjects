#include "createquestionform.h"
#include "ui_createquestionform.h"

#include <QSqlQuery>
#include <QMessageBox>

CreateQuestionForm::CreateQuestionForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateQuestionForm)
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
    //mapper->addMapping(ui->sQuestionBox, 1);
    mapper->addMapping(ui->answerLine, 2);

    QSqlQueryModel *select = new QSqlQueryModel(this);
    select->setQuery("select type from question");
    ui->sQuestionBox->setModel(select);

    mapper->addMapping(ui->sQuestionBox, model->fieldIndex("Security question"), "currentIndex");

    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    model->insertRow(model->rowCount(QModelIndex()));

    mapper->toLast();

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateQuestionForm::submitChanges);
}

CreateQuestionForm::~CreateQuestionForm()
{
    delete ui;
}

void CreateQuestionForm::submitChanges()
{
    // Save changes to database

    mapper->submit();
    model->submitAll();

    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateQuestionForm::setRowIndex(int rowIndex)
{
    // User chose to edit data from the table
    mapper->setCurrentIndex(rowIndex);
}
