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

    ui->submitButton->setEnabled(false); // All columns

    initData(Table);

    mapper->addMapping(ui->entryNameLine, 1);
    mapper->addMapping(ui->questionLine, 2);

    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateQuestionForm::submitChanges);

    // All columns
    connect(ui->entryNameLine, &QLineEdit::textChanged, this, [this] {
        ui->submitButton->setEnabled(!ui->entryNameLine->text().isEmpty() && !ui->questionLine->text().isEmpty());
    });
    connect(ui->questionLine, &QLineEdit::textChanged, ui->entryNameLine, &QLineEdit::textChanged);
}

CreateQuestionForm::~CreateQuestionForm()
{
    delete ui;
}
