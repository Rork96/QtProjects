#include "../Headers/createquestionform.h"
#include "ui_createquestionform.h"

CreateQuestionForm::CreateQuestionForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateQuestionForm)
{
    ui->setupUi(this);
}

CreateQuestionForm::~CreateQuestionForm()
{
    delete ui;
}
