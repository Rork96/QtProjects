#include "../Headers/importfilesform.h"
#include "ui_importfilesform.h"

#include <QFileDialog>
#include <QStandardPaths>

ImportFilesForm::ImportFilesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImportFilesForm)
{
    ui->setupUi(this);

    ui->uploadButton->setEnabled(false);
    ui->executeButton->setEnabled(false);

    // Click on import lable
}

ImportFilesForm::~ImportFilesForm()
{
    delete ui;
}

void ImportFilesForm::importFiles()
{
    // Import files

    QString fName = QFileDialog::getOpenFileName(this, "Choose files",
                    QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                     "Files (*.*)");

    if(fName.isEmpty()) return;

    ui->uploadButton->setEnabled(true);
    ui->executeButton->setEnabled(true);
}
