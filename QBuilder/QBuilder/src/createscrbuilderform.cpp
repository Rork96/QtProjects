#include "createscrbuilderform.h"
#include "ui_createscrbuilderform.h"

CreateScrBuilderForm::CreateScrBuilderForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateScrBuilderForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });
}

CreateScrBuilderForm::~CreateScrBuilderForm()
{
    delete ui;
}
