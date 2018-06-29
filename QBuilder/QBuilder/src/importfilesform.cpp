#include "importfilesform.h"
#include "ui_importfilesform.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>
#include <QMessageBox>

ImportFilesForm::ImportFilesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImportFilesForm)
{
    ui->setupUi(this);

    ui->uploadButton->setEnabled(false);
    ui->executeButton->setEnabled(false);
    ui->clearButton->setVisible(false);

    // Select file
    connect(ui->mainButton, &QToolButton::clicked, this, &ImportFilesForm::importFiles);

    // Delete selected file
    connect(ui->clearButton, &QToolButton::clicked, this, [this] {
        ui->mainButton->setText("Drop files here to upload");
        ui->clearButton->setVisible(false);
    });

    // Execute selected file
    connect(ui->executeButton, &QToolButton::clicked, this, &ImportFilesForm::executeFile);
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
                                                 "Supported files (*.sql | *.xlsx | *.xls | *.csv);;"
                                                 "All files (*.*);; *.sql;; *.xlsx;; *.xls;; *.csv;; Text documents (*.txt)");

    if(fName.isEmpty()) return;

    ui->mainButton->setText(QFileInfo(fName).fileName());

    ui->uploadButton->setEnabled(true);
    ui->executeButton->setEnabled(true);
    ui->clearButton->setVisible(true);
}

void ImportFilesForm::executeFile()
{
    // Execute selected file
    QMessageBox::information(this, "Information", "File was successfully executed ", QMessageBox::Ok);
}
