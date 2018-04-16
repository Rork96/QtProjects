#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* * * Connections * * */ {
        // Open archive
        connect(ui->openArc, &QAction::triggered, this, &MainWindow::OpenArchive);

        // Quit
        connect(ui->quitProgram, &QAction::triggered, this, &MainWindow::close);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenArchive()
{
    /* * * Open archive * * */

    OpenArc(QString());
}

void MainWindow::OpenArc(QString archiveName)
{
    /* * * Open archive when program starts * * */

    if (archiveName.isEmpty()) {
        archiveName = QFileDialog::getOpenFileName(this, "Choose files",
                                                    QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                    "Archives (*.zip | *.7z | *.tar.gz | *.bz2)");
    }

    if (archiveName.isEmpty())
        return;

    QFileInfo fInfo(archiveName);
    bool result = false;

    if (fInfo.suffix() == "zip") {
        result = ReadZip(fInfo);
    }
    else if (fInfo.suffix() == "7z") {
        result = Read7Zip(fInfo);
    }
    else if (fInfo.suffix() == "gz") {
        result = ReadTarGz(fInfo);
    }
    else {
        result = ReadBz2(fInfo);
    }

    if (result) {
        QMessageBox::information(this, "QtArc", "Archive successfully extracted!", QMessageBox::Ok);
    }
    else {
        QMessageBox::warning(this, "QtArc", "Error! Cannot extract archive!", QMessageBox::Ok);
    }
}

bool MainWindow::ReadZip(QFileInfo archiveInfo)
{
    /* * * Decompress zip * * */

    KZip archive(archiveInfo.absoluteFilePath());
    bool result = false;

    // Open the archive
    if (!archive.open(QIODevice::ReadOnly))
        return result;

    // Take the root folder from the archive and create a KArchiveDirectory object.
    // KArchiveDirectory represents a directory in a KArchive.
    const KArchiveDirectory *root = archive.directory();

    // Extract all contents from a KArchiveDirectory to a destination.
    // true - will also extract subdirectories.
    QString destination = QDir::currentPath() + "/" + archiveInfo.baseName();
    result = root->copyTo(destination, true);

    archive.close();

    return result;
}

bool MainWindow::Read7Zip(QFileInfo archiveInfo)
{
    /* * * Decompress 7zip * * */

    K7Zip archive(archiveInfo.absoluteFilePath());
    bool result = false;

    // Open the archive
    if (!archive.open(QIODevice::ReadOnly))
        return result;

    // Take the root folder from the archive and create a KArchiveDirectory object.
    // KArchiveDirectory represents a directory in a KArchive.
    const KArchiveDirectory *root = archive.directory();

    // Extract all contents from a KArchiveDirectory to a destination.
    // true - will also extract subdirectories.
    QString destination = QDir::currentPath() + "/" + archiveInfo.baseName();
    result = root->copyTo(destination, true);

    archive.close();

    return result;
}

bool MainWindow::ReadTarGz(QFileInfo archiveInfo)
{
    /* * * Decompress tar.gz * * */

    KTar archive(archiveInfo.absoluteFilePath());
    bool result = false;

    // Open the archive
    if (!archive.open(QIODevice::ReadOnly))
        return result;

    // Take the root folder from the archive and create a KArchiveDirectory object.
    // KArchiveDirectory represents a directory in a KArchive.
    const KArchiveDirectory *root = archive.directory();

    // Extract all contents from a KArchiveDirectory to a destination.
    // true - will also extract subdirectories.
    QString destination = QDir::currentPath();
    result = root->copyTo(destination, true);

    archive.close();

    return result;
}

bool MainWindow::ReadBz2(QFileInfo archiveInfo)
{
    /* * * Decompress bz2 * * */

    bool result = false;

    return result;
}
