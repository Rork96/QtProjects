#include "createquestionform.h"
#include "ui_createquestionform.h"

CreateQuestionForm::CreateQuestionForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateQuestionForm)
{
    ui->setupUi(this);

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

    // Send sygnal
    emit sygnalSubmit();
}
