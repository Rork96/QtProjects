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

    initData(Table);

    // Set relation between tables
    int typeIndex = model->fieldIndex("security_question");
    model->setRelation(typeIndex, QSqlRelation("question", "id", "type"));
    model->select();

    // New relation model for combobox
    QSqlTableModel *relModel = model->relationModel(typeIndex); // Relation index
    ui->sQuestionBox->setModel(relModel);
    ui->sQuestionBox->setModelColumn(relModel->fieldIndex("type"));

    // View data with mapper
    mapper->addMapping(ui->sQuestionBox, typeIndex);    // Relation by index
    mapper->addMapping(ui->answerLine, 2);

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
