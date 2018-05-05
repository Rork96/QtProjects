#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Full screen
    QShortcut *fullScreenShortcut = new QShortcut(QKeySequence(Qt::Key_F11), this);
    QShortcut *showMenu = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_M), this);
    QShortcut *showToolBar = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_I), this);
    QShortcut *showStatusBar = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this);

    /* * * Connections * * */ {
        // Open archive
        connect(ui->openArc, &QAction::triggered, this, &MainWindow::OpenArchive);
        // Extract archive
        connect(ui->extractToDir, &QAction::triggered, this, &MainWindow::ExtractArc);
        // Compress into archive
        connect(ui->compessArc, &QAction::triggered, this, &MainWindow::CompressIntoArchive);

        // Full screen
        connect(ui->fullScrean, &QAction::triggered, fullScreenShortcut, &QShortcut::activated);
        connect(fullScreenShortcut, &QShortcut::activated, this, [this] {
            if (isFullScreen()) {
                showNormal();
            } else {
                showFullScreen();
            }
        });
        // Show or hide MainMenu, ToolBar, StatusBar
        connect(showMenu, &QShortcut::activated, [this] {
            ui->mainMenuShow->setChecked(!ui->mainMenuShow->isChecked());
            ui->mainMenuBar->setVisible(ui->mainMenuShow->isChecked());
        });
        connect(showToolBar, &QShortcut::activated, [this] {
            ui->mainToolBarShow->setChecked(!ui->mainToolBarShow->isChecked());
            ui->mainToolBar->setVisible(ui->mainToolBarShow->isChecked());
        });
        connect(showStatusBar, &QShortcut::activated, [this] {
            ui->statusBarShow->setChecked(!ui->statusBarShow->isChecked());
            ui->statusBar->setVisible(ui->statusBarShow->isChecked());
        });
        // About program
        connect(ui->aboutProgram, &QAction::triggered, [this] {
            QString aboutText;
            aboutText = "          QtArc v 1.0.0  \n\n";
            aboutText += "Автор  : \tmasterarrow\n\n";
            aboutText += "email  : \tmasterarrows@gmail.com\n\n";
            aboutText += "          Copyright © 2018\n";

            QMessageBox::about(this, "About QtArc", aboutText);
        });
        // About Qt
        connect(ui->aboutQt, &QAction::triggered, [this] {
           QMessageBox::aboutQt(this, "О Qt");
        });
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
    /* * * Open archive when program starts * * */
}

void MainWindow::ExtractArc()
{
    /* * * Extract archive * * */

    if (archiveName.isEmpty()) {
        // Set archive name
        setArchiveName(
                QFileDialog::getOpenFileName(this, "Выберите файл",
                                             QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                             "Архивы (*.zip | *.7z | *.tar.gz | *.bz2)")
        );
    }

    // If user didn't choose file
    if (archiveName.isEmpty())
        return;

    QFileInfo fInfo(archiveName);
    // Extraction result
    bool result = false;

    if (fInfo.suffix() == "zip") {
        result = ExtractZip();
    }
    else if (fInfo.suffix() == "7z") {
        result = Extract7Zip();
    }
    else if (fInfo.suffix() == "gz") {
        result = ExtractTarGz();
    }
    else { // bz2
        result = ExtractBz2();
    }

    if (result) {
        QMessageBox::information(this, "QtArc", "Архив успешно извлечен!", QMessageBox::Ok);
    }
    else {
        QMessageBox::warning(this, "QtArc", "Ошибка извлечения архива!", QMessageBox::Ok);
    }
}

bool MainWindow::ExtractZip()
{
    /* * * Extract zip * * */

    QFileInfo archiveInfo(archiveName);
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

    // Extraction result
    return result;
}

bool MainWindow::Extract7Zip()
{
    /* * * Extract 7zip * * */

    QFileInfo archiveInfo(archiveName);
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

    // Extraction result
    return result;
}

bool MainWindow::ExtractTarGz()
{
    /* * * Extract tar.gz * * */

    QFileInfo archiveInfo(archiveName);
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

    // Extraction result
    return result;
}

bool MainWindow::ExtractBz2()
{
    /* * * Extract bz2 * * */

    QFileInfo archiveInfo(archiveName);
    bool result = false;

    return result;
}

void MainWindow::CompressIntoArchive()
{
    /* * * Compress into archive * * */

    QString str = QFileDialog::getSaveFileName(this, "Выберите папку для сохранения",
                                               QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                               "Zip архив (*.zip );; 7Zip архив (*.7z );; Tar gzip архив (*.tar.gz);;"
                                               "Bzip2 архив (*.bz2)");

    // If user didn't choose file
    if (str.isEmpty())
        return;

    // Add default suffix ".zip"
    if (QFileInfo(str).suffix().isEmpty()) {
        str.append(".zip");
    }

    // Set archive name
    setArchiveName(str);

    QFileInfo fInfo(archiveName);
    // Extraction result
    bool result = false;

    if (fInfo.suffix() == "zip") {
        result = CompressZip();
    }
    else if (fInfo.suffix() == "7z") {
        result = Compress7Zip();
    }
    else if (fInfo.suffix() == "gz") {
        result = CompressTarGz();
    }
    else { // bz2
        result = CompressBz2();
    }

    if (result) {
        QMessageBox::information(this, "QtArc", "Архивация успешна!", QMessageBox::Ok);
    }
    else {
        QMessageBox::warning(this, "QtArc", "Ошибка архивации!", QMessageBox::Ok);
    }
}

bool MainWindow::CompressZip()
{
    /* * * Compress into zip * * */

    // Compression result
    bool result = false;
/*
#ifdef Q_OS_LINUX
        if (QFileInfo(archiveName).suffix() != "zip") {
            archiveName += ".zip";
        }
#endif*/

    KZip zip(archiveName);
    if (zip.open(QIODevice::WriteOnly)) {
        QFileInfo fInfo(archiveName);
        QFile f(fInfo.absolutePath() + "/Word.doc");
        f.open(QFile::ReadOnly);
        const QByteArray arr = f.readAll();
        bool writeOk = zip.writeFile(QFileInfo(f.fileName()).fileName(), arr);

        if (!writeOk) {
            return result;
        }

        result = true;
    }

    return result;
}

bool MainWindow::Compress7Zip()
{
    /* * * Compress into 7z * * */

    // Compression result
    bool result = false;

    KTar tarZip(archiveName);
    if (tarZip.open(QIODevice::WriteOnly)) {
        QFileInfo fInfo(archiveName);
        QFile f(fInfo.absolutePath() + "/Word.doc");
        f.open(QFile::ReadOnly);
        const QByteArray arr = f.readAll();
        bool writeOk = tarZip.writeFile(QFileInfo(f.fileName()).fileName(), arr);

        if (!writeOk) {
            return result;
        }

        result = true;
    }

    return result;
}

bool MainWindow::CompressTarGz()
{
    /* * * Compress into tar.gz * * */

    // Compression result
    bool result = false;

    KZip zip(archiveName);
    if (zip.open(QIODevice::WriteOnly)) {
        QFileInfo fInfo(archiveName);
        QFile f(fInfo.absolutePath() + "/Word.doc");
        f.open(QFile::ReadOnly);
        const QByteArray arr = f.readAll();
        bool writeOk = zip.writeFile(QFileInfo(f.fileName()).fileName(), arr);

        if (!writeOk) {
            return result;
        }

        result = true;
    }

    return result;
}

bool MainWindow::CompressBz2()
{
    /* * * Compress into bz2 * * */

    // Compression result
    bool result = false;

    KCompressionDevice device(archiveName, KCompressionDevice::BZip2);
    if (device.open(QIODevice::WriteOnly)) {
        QFileInfo fInfo(archiveName);
        QFile f(fInfo.absolutePath() + "/Word.doc");
        f.open(QFile::ReadOnly);
        const QByteArray data = f.readAll();
        const int written = device.write(data);

        if (written != data.size()) {
            return result;
        }
        result = true;
    }

    return result;
}

void MainWindow::setArchiveName(const QString &arcName)
{
    /* * * Set archive name * * */

    archiveName = arcName;
}

void MainWindow::CloseArchive()
{
    /* * * Close current archive * * */

    // Clear view

    // Set archive name
    setArchiveName(QString());
}
