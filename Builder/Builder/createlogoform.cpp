#include "createlogoform.h"
#include "ui_createlogoform.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>

CreateLogoForm::CreateLogoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateLogoForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateLogoForm::submitChanges);

    connect(ui->openImageButton, &QPushButton::clicked, this, &CreateLogoForm::openImage);
}

CreateLogoForm::~CreateLogoForm()
{
    delete ui;
}

void CreateLogoForm::submitChanges()
{
    // Save changes to database

    // Send sygnal
    emit sygnalSubmit();
}

void CreateLogoForm::openImage()
{
    // Open image

    QString fName = QFileDialog::getOpenFileName(this, "Choose files",
                    QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                 "Supported files (*.png | *.jpg | *.jpeg);;"
                                                 "All files (*.*)");

    if(fName.isEmpty()) return;

    ui->imageNameLabel->setText(QFileInfo(fName).fileName());
}
