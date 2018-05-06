#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QShortcut>

#include <QFileSystemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Add model into view
    fModel = new QStandardItemModel(this);
    ui->mainView->setModel(fModel);

    // Full screen
    QShortcut *fullScreenShortcut = new QShortcut(QKeySequence(Qt::Key_F11), this);
    QShortcut *showMenu = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_M), this);
    QShortcut *showToolBar = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_I), this);
    QShortcut *showStatusBar = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this);

    /* * * Connections * * */ {
        // Open archive
        connect(ui->openArc, &QAction::triggered, this, &MainWindow::OpenArc);
        // Extract archive
        connect(ui->extractToDir, &QAction::triggered, this, &MainWindow::ExtractArc);
        // Compress into archive
        connect(ui->compessArc, &QAction::triggered, this, &MainWindow::CompressIntoArchive);

        // Add files into list for compression
        connect(ui->addFiles, &QAction::triggered, this, &MainWindow::AddFiles);

        // Close archive
        connect(ui->closeArc, &QAction::triggered, this, &MainWindow::CloseArchive);

        // Delete file from list
        connect(ui->deleteFile, &QAction::triggered, this, &MainWindow::DelFile);

        // Save archive as ...
        connect(ui->saveArcCopy, &QAction::triggered, this, &MainWindow::SaveAsArc);

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

void MainWindow::OpenArchive(const QString &arcName)
{
    /* * * Open archive when program starts * * */

    if (arcName.isEmpty())
        return;

    setArchiveName(arcName);

    // Open
    OpenArc();
}

void MainWindow::OpenArc()
{
    /* * * Open archive when program starts * * */

    QString str = QFileDialog::getOpenFileName(this, "Выберите файл",
                                               QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                               "Архивы (*.zip | *.7z | *.tar.gz)");

    // User didn't choose file
    if (str.isEmpty())
        return;

    // Clear model and list
    fModel->clear();
    archiveItems.clear();

    setArchiveName(str);

    // Set title
    setWindowTitle("QtArc - " + QFileInfo(archiveName).fileName());
}

void MainWindow::ExtractArc()
{
    /* * * Extract archive * * */

    if (archiveName.isEmpty()) {
        QMessageBox::information(this, "QtArc", "Сначала откройте архив!", QMessageBox::Ok);
        return;
    }

    // Choose Destination
    QString destination = QFileDialog::getExistingDirectory(this, "Выберите папку",
                                               QStandardPaths::locate(QStandardPaths::HomeLocation, QString()));

    // User didn't choose file
    if (destination.isEmpty())
        return;

    QFileInfo fInfo(archiveName);
    // Extraction result
    bool result = false;

    if (fInfo.suffix() == "zip") {
        result = ExtractZip(destination);
    }
    else if (fInfo.suffix() == "7z") {
        result = Extract7Zip(destination);
    }
    else { // gz
        result = ExtractTarGz(destination);
    }

    if (result) {
        QMessageBox::information(this, "QtArc", "Архив успешно извлечен!", QMessageBox::Ok);
    }
    else {
        QMessageBox::warning(this, "QtArc", "Ошибка извлечения архива!", QMessageBox::Ok);
    }
}

bool MainWindow::ExtractZip(const QString &dest)
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
    QString destination = dest + "/" + archiveInfo.baseName();
    result = root->copyTo(destination, true);

    archive.close();

    // Extraction result
    return result;
}

bool MainWindow::Extract7Zip(const QString &dest)
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
    QString destination = dest + "/" + archiveInfo.baseName();
    result = root->copyTo(destination, true);

    archive.close();

    // Extraction result
    return result;
}

bool MainWindow::ExtractTarGz(const QString &dest)
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
    result = root->copyTo(dest, true);

    archive.close();

    // Extraction result
    return result;
}

void MainWindow::CompressIntoArchive()
{
    /* * * Compress into archive * * */

    // Files for compression must be added
    if (archiveItems.isEmpty()) {
        QMessageBox::information(this, "QtArc", "Сначала выберите файлы для архивации!", QMessageBox::Ok);
        return;
    }

    QString str = QFileDialog::getSaveFileName(this, "Выберите папку для сохранения",
                                               QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                               "Zip архив (*.zip );; 7Zip архив (*.7z );; Tar gzip архив (*.tar.gz)");

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
    else { // gz
        result = CompressTarGz();
    }

    if (result) {
        QMessageBox::information(this, "QtArc", "Архивация успешна!", QMessageBox::Ok);
        setWindowTitle("QtArc - " + QFileInfo(archiveName).fileName());
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

    // Compress
    KZip zip(archiveName);
    if (zip.open(QIODevice::WriteOnly)) {
        // For all items
        foreach (QString item, archiveItems) {
            QFile f(item);
            f.open(QFile::ReadOnly);
            const QByteArray arr = f.readAll();                                     // Get byte array from file
            bool writeOk = zip.writeFile(QFileInfo(f.fileName()).fileName(), arr);  // Write file

            if (!writeOk) {
                return result;  // false
            }
        }

        result = true;
    }

    return result; // true
}

bool MainWindow::Compress7Zip()
{
    /* * * Compress into 7z * * */

    // Compression result
    bool result = false;

    // Compress
    KTar tarZip(archiveName);
    if (tarZip.open(QIODevice::WriteOnly)) {
        // For all items
        foreach (QString item, archiveItems) {
            QFile f(item);
            f.open(QFile::ReadOnly);
            const QByteArray arr = f.readAll();
            bool writeOk = tarZip.writeFile(QFileInfo(f.fileName()).fileName(), arr);

            if (!writeOk) {
                return result; // false
            }
        }

        result = true;
    }

    return result; // true
}

bool MainWindow::CompressTarGz()
{
    /* * * Compress into tar.gz * * */

    // Compression result
    bool result = false;

    // Compress
    KZip zip(archiveName);
    if (zip.open(QIODevice::WriteOnly)) {
        // For all items
        foreach (QString item, archiveItems) {
            QFile f(item);
            f.open(QFile::ReadOnly);
            const QByteArray arr = f.readAll();
            bool writeOk = zip.writeFile(QFileInfo(f.fileName()).fileName(), arr);

            if (!writeOk) {
                return result; // false
            }
        }

        result = true;
    }

    return result; // true
}

void MainWindow::setArchiveName(const QString &arcName)
{
    /* * * Set archive name * * */

    archiveName = arcName;
}

void MainWindow::CloseArchive()
{
    /* * * Close current archive * * */

    // Clear view and model
    fModel->clear();
    // Clear saved items
    archiveItems.clear();

    // Set archive name
    setArchiveName(QString());

    // Set title
    setWindowTitle("QtArc");
}

void MainWindow::AddFiles() {
    /* * * Add files into list for compression * * */

    // Clear archiveName, model and list
    if (!archiveName.isEmpty()) {
        archiveName.clear();
        fModel->clear();
        archiveItems.clear();
        // Set title
        setWindowTitle("QtArc");
    }

    archiveItems = QFileDialog::getOpenFileNames(this, "Выберите файлы",
                                             QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                             "Все файлы (*.*)");

    // If user didn't choose file
    if (archiveItems.isEmpty())
        return;

    // Add columns
    fModel->insertColumns(0, 4);
    fModel->setHorizontalHeaderLabels(QStringList() << "Путь" << "Имя" << "Тип" << "Размер" << "Дата изменения");

    // Hide 0 column "Путь"
    ui->mainView->hideColumn(0);

    ui->mainView->verticalHeader()->hide();
    ui->mainView->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Resize columns
    ui->mainView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->mainView->setColumnWidth(2, 120);
    ui->mainView->setColumnWidth(3, 150);
    ui->mainView->setColumnWidth(4, 250);

    foreach (QString file, archiveItems) {
        QString type = "";
        QString size = objSize(QFileInfo(file), type);
        QList<QStandardItem*> items;
        items << new QStandardItem(file)                                                        // File path (hidden)
              << new QStandardItem(QFileInfo(file).fileName())                                  // File name
              << new QStandardItem(type)                                                        // Type (file or folder)
              << new QStandardItem(size)                                                        // Size
              << new QStandardItem(QFileInfo(file).lastModified().toLocalTime().toString());    // Date
        fModel->appendRow(items);
    }
}

QString MainWindow::objSize(const QFileInfo fileInfo, QString &objType)
{
    // Identify size of the file or the folder
    // Return QString and objType

    // Object exists
    if(!fileInfo.exists()) return "0 байт";
    float size = 0.0;

    // Folder
    if(fileInfo.isDir())
    {
        // Folder size (return num)
        dirSize(fileInfo, size);
        objType = "Папка";
    }
    else // File
    {
        // File size
        size = fileInfo.size();
        objType = "Файл";
    }

    // Translate into bytes in К, М, Г, Т
    qint64 i = 0;
    for (; size > 1024; size /= 1024, ++i) { }
    // Return value and type (Б, К, М, Г, Т)
    return QString("%1").arg(size, 0, 'f', 1) + " " + "BKMGT"[i];
}

void MainWindow::dirSize(const QFileInfo inf, float &num)
{
    // Folder size (return num)

    QDir dir;
    // Browse hidden, skip links
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::Hidden | QDir::NoSymLinks |
                  QDir::NoDotAndDotDot);
    dir.cd(inf.absoluteFilePath());

    // Get file list in the directory
    QFileInfoList list = dir.entryInfoList();

            foreach (QFileInfo fInfo, list)
        {
            /* Если текущий элемент это директория и не "." и ".."
             * (в Linux "." - указатель на текущий каталог,
             * а ".." - на родительский каталог) -
             * их нужно пропустить
             */
            if(fInfo.isDir())
            {
                float s = 0;
                // Call dirSize recursively
                dirSize(fInfo, s);
                num += s;
            }
            // Determine the size of the included files
            num += fInfo.size();
        }
}

void MainWindow::DelFile()
{
    /* * * Delete file from list * * */

    fModel->removeRow(ui->mainView->selectionModel()->currentIndex().row());

    // Delete from list
    archiveItems.removeAt(ui->mainView->selectionModel()->currentIndex().row() + 1);
}

void MainWindow::SaveAsArc()
{
    /* * * Save archive as ... * * */

    // Files for compression must be added
    if (archiveName.isEmpty()) {
        QMessageBox::information(this, "QtArc", "Сначала откройте архив!", QMessageBox::Ok);
        return;
    }

    QString suffix = QFileInfo(archiveName).completeSuffix();

    QString newArchive = QFileDialog::getSaveFileName(this, "Выберите папку для сохранения",
                                               QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                               "Архивы (*." + suffix + ")");

    // User didn't choose file
    if (newArchive.isEmpty())
        return;

    // Add default suffix ".zip"
    if (QFileInfo(newArchive).suffix().isEmpty()) {
        newArchive.append("." + suffix);
    }

    // Copy archive
    if (QFile::copy(archiveName, newArchive)) {
        archiveName = newArchive;
        QMessageBox::information(this, "QtArc", "Архив сохранен!", QMessageBox::Ok);
        setWindowTitle("QtArc - " + QFileInfo(archiveName).fileName());
    }
    else {
        QMessageBox::warning(this, "QtArc", "Ошибка сохранения!", QMessageBox::Ok);
    }
}