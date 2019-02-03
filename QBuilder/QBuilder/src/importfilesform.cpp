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
        ui->mainButton->setText(trUtf8("Click here to upload files"));
        ui->clearButton->setVisible(false);
        ui->uploadButton->setEnabled(false);
        ui->executeButton->setEnabled(false);
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

    QString fName = QFileDialog::getOpenFileName(this, trUtf8("Choose files"),
                    QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                 trUtf8("Supported files (*.sql | *.xlsx | *.xls | *.csv);;"
                                                 "All files (*.*);; *.sql;; *.xlsx;; *.xls;; *.csv;; Text documents (*.txt)"));

    if(fName.isEmpty()) return;

    ui->mainButton->setText(QFileInfo(fName).fileName());

    ui->uploadButton->setEnabled(true);
    ui->executeButton->setEnabled(true);
    ui->clearButton->setVisible(true);
}

void ImportFilesForm::executeFile()
{
    // Execute selected file
    QMessageBox::information(this, trUtf8("Information"), trUtf8("File was successfully executed"), QMessageBox::Ok);
}
