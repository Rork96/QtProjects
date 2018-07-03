#include "createquestionform.h"
#include "ui_createquestionform.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlRelationalDelegate>

CreateQuestionForm::CreateQuestionForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateQuestionForm)
{
    ui->setupUi(this);

    model = new QSqlRelationalTableModel(this);
    model->setTable(Table);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0, Qt::AscendingOrder);

    // Set relation between tables
    int typeIndex = model->fieldIndex("Security question");
    model->setRelation(typeIndex, QSqlRelation("question", "id", "type"));
    model->select();

    // New relation model for combobox
    QSqlTableModel *relModel = model->relationModel(typeIndex); // Relation index
    ui->sQuestionBox->setModel(relModel);
    ui->sQuestionBox->setModelColumn(relModel->fieldIndex("type"));

    // Mapper
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    // View data with mapper
    mapper->addMapping(ui->sQuestionBox, typeIndex);    // Relation by index
    mapper->addMapping(ui->answerLine, 2);

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

void CreateQuestionForm::setRowIndex(int rowIndex, int)
{
    // User chose to edit data from the table
    mapper->setCurrentIndex(rowIndex);
}
