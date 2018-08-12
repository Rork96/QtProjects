#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QShortcut>
#include <QFileSystemModel>
#include <QDesktopServices>

#include <QDebug>
//#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Add model into view
    fModel = new QStandardItemModel(this);
    ui->mainView->setModel(fModel);
    // Set edit mode
    ui->mainView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Full screen
    QShortcut *fullScreenShortcut = new QShortcut(QKeySequence(Qt::Key_F11), this);
    QShortcut *showMenu = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_M), this);
    QShortcut *showToolBar = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_I), this);
    QShortcut *showStatusBar = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this);

    // Default - 0
    EnableActions();
    ui->closeArc->setEnabled(false);

    // region Connections
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

        // Open file or folder
        connect(ui->mainView, &QTableView::doubleClicked, this, &MainWindow::OpenItem);

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
    // endregion Connections
}

MainWindow::~MainWindow()
{
    delete ui;
}

// region Archive

void MainWindow::OpenArchive(const QString &arcName)
{
    /* * * Open archive when program starts * * */

    if (arcName.isEmpty())
        return;

    setArchiveName(arcName);

    // Open
    OpenArc();
}

// region Open archive

void MainWindow::OpenArc()
{
    /* * * Open archive * * */

    CloseArchive(); // Close previous archive

    // Enable actions for archive
    EnableActions(1);

    if (archiveName.isEmpty()) {
        QString str = QFileDialog::getOpenFileName(this, "Выберите файл",
                                                   QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                   "Архивы (*.zip | *.7z | *.tar.gz)");

        // User didn't choose file
        if (str.isEmpty())
            return;

        setArchiveName(str);
    }

    // Clear model and list
    fModel->clear();
    archiveItems.clear();

    auto openArcheve = [this] (Archiver *arc) {
        // Open archive
        arc->setFileName(archiveName);
        if (!arc->open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, "QtArc", "Ошибка открытия архива!", QMessageBox::Ok);
            EnableActions(0);   // Default
            return;
        }
        const KArchiveDirectory *dir = arc->directory();

        // Add files from archive to list
        ListRecursive(dir, QString());
        arc->close();
    };

    if (QFileInfo(archiveName).suffix() == "zip") {
        // Initialize class Archiver for managing zip files
        // (class Azip is a wrapper for class KZip)
        openArcheve(new Archiver(new AZip()));
    }
    else if (QFileInfo(archiveName).suffix() == "7z") {
        openArcheve(new Archiver(new A7Zip()));
    }
    else { // gz
        openArcheve(new Archiver(new ATarGz()));
    }

    // Set title
    setWindowTitle("QtArc - " + QFileInfo(archiveName).fileName());
}

void MainWindow::ListRecursive(const KArchiveDirectory *dir, const QString &path)
{
    /* * * Add files from 7-zip archive to list * * */

    // Add columns and size
    if (fModel->columnCount() == 0)
        CustomizeTable();

    QStringList l = dir->entries();
    QStringList::ConstIterator it = l.constBegin();

    for (; it != l.constEnd(); ++it) {
        const KArchiveEntry *entry = dir->entry((*it));

        QString type = "Файл";
        float size = 0;
        if (entry->isDirectory()) {
            type = "Папка";
            /*KArchiveDirectory *ddd;
            ddd = (KArchiveDirectory *)entry, path + (*it) + '/';
            QStringList lst = ddd->entries();
            QStringList::ConstIterator it = lst.constBegin();
            for (; it != lst.constEnd(); ++it) {
                const KArchiveEntry *entry = dir->entry((*it));

                size += (static_cast<const KArchiveFile *>(entry))->size();
            }*/
        }
        else {
            size = (static_cast<const KArchiveFile *>(entry))->size();

//            const KArchiveFile *f = static_cast<const KArchiveFile *>(entry);
//            QByteArray arr(f->data());
//            qDebug() << "data" << arr;
//
//            QIODevice *dev = f->createDevice();
//            QByteArray contents = dev->readAll();
//            qDebug() << "contents" << contents;
//            delete dev;
        }
            // Translate into bytes in К, М, Г, Т
            qint64 i = 0;
            for (; size > 1024; size /= 1024, ++i) {}
            // Return value and type (Б, К, М, Г, Т)
            QString itSize = QString("%1").arg(size, 0, 'f', 1) + " " + "BKMGT"[i];

        QList<QStandardItem*> items;
        items << new QStandardItem(path.toLatin1().constData())                                             // File path (hidden)
              << new QStandardItem((*it).toLatin1().constData())                                            // File name
              << new QStandardItem(type)                                                                    // Type (file or folder)
              << new QStandardItem(itSize)                                                                  // Size
              << new QStandardItem(entry->date().toString("yyyy-MM-dd hh:mm:ss").toLatin1().constData());   // Date
              //<< new QStandardItem((static_cast<const KArchiveFile *>(entry))->date().toLocalTime().toString("yyyy-MM-dd hh:mm:ss"));
        fModel->appendRow(items);

        /*
        // Directory entries
        if (entry->isDirectory()) {
            ListRecursive((KArchiveDirectory *)entry, path + (*it) + '/');
        }
        */
    }
}
// endregion Open archive

// region Extract archive

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
    bool result;

    auto extractQrchive = [this] (Archiver *arc, const QString &dest) -> bool {
        // Extract archive
        QFileInfo archiveInfo(archiveName);

        arc->setFileName(archiveInfo.absoluteFilePath());

        // Open the archive
        if (!arc->open(QIODevice::ReadOnly))
            return false;

        // Take the root folder from the archive and create a KArchiveDirectory object.
        // KArchiveDirectory represents a directory in a KArchive.
        const KArchiveDirectory *root = arc->directory();

        // Extract all contents from a KArchiveDirectory to a destination.
        // true - will also extract subdirectories.
        QString destin = dest + "/" + archiveInfo.baseName();
        bool res = root->copyTo(destin, true);

        arc->close();

        // Extraction result
        return res;
    };

    if (fInfo.suffix() == "zip") {
        // Initialize class Archiver for managing zip files
        // (class Azip is a wrapper for class KZip)
        result = extractQrchive(new Archiver(new AZip()), destination);
    }
    else if (fInfo.suffix() == "7z") {
        result = extractQrchive(new Archiver(new A7Zip()), destination);
    }
    else { // gz
        result = extractQrchive(new Archiver(new ATarGz()), destination);
    }

    if (result) {
        QMessageBox::information(this, "QtArc", "Архив успешно извлечен!", QMessageBox::Ok);
    }
    else {
        QMessageBox::warning(this, "QtArc", "Ошибка извлечения архива!", QMessageBox::Ok);
    }
}
// endregion Extract archive

// region Compress into archive

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
    bool result;

    auto compressArchive = [this] (Archiver *arc) -> bool {
        // Compress into archive
        arc->setFileName(archiveName);
        if (arc->open(QIODevice::WriteOnly)) {
            // For all items
            foreach (QString item, archiveItems) {
                QFile f(item);
                f.open(QFile::ReadOnly);
                const QByteArray arr = f.readAll();                             // Get byte array from file
                bool writeOk = arc->writeFile(QFileInfo(item).fileName(), arr); // Write file

                if (!writeOk) {
                    return !arc->close();   // false
                }
            }
            return arc->close();            // true
        }
        return false;
    };

    if (fInfo.suffix() == "zip") {
        // Initialize class Archiver for managing zip files
        // (class Azip is a wrapper for class KZip)
        result = compressArchive(new Archiver(new AZip()));
    }
    else if (fInfo.suffix() == "7z") {
        result = compressArchive(new Archiver(new A7Zip()));
    }
    else { // gz
        result = compressArchive(new Archiver(new ATarGz()));
    }

    if (result) {
        QMessageBox::information(this, "QtArc", "Архивация успешна!", QMessageBox::Ok);
        setWindowTitle("QtArc - " + QFileInfo(archiveName).fileName());
    }
    else {
        QMessageBox::warning(this, "QtArc", "Ошибка архивации!", QMessageBox::Ok);
    }
}
//endregion Compress into archive

// region Save arc as...

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
// rendregion Save arc as...

void MainWindow::setArchiveName(const QString &arcName)
{
    /* * * Set archive name * * */

    archiveName = arcName;
}

void MainWindow::CloseArchive()
{
    /* * * Close current archive or clear list * * */

    // Default - 0
    EnableActions();

    // Clear view and model
    fModel->clear();
    // Clear saved items
    archiveItems.clear();

    // Set archive name
    setArchiveName(QString());

    // Set title
    setWindowTitle("QtArc");
}
// endregion Archive

// region Files and folders

void MainWindow::AddFiles() {
    /* * * Add files into list for compression * * */

    // Enable actions for files and folders
    EnableActions(2);

    archiveItems = QFileDialog::getOpenFileNames(this, "Выберите файлы",
                                             QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                             "Все файлы (*.*)");

    // If user didn't choose file
    if (archiveItems.isEmpty())
        return;

    // Add columns and size
    if (fModel->columnCount() == 0)
        CustomizeTable();

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

void MainWindow::DelFile()
{
    /* * * Delete file from list * * */

    fModel->removeRow(ui->mainView->selectionModel()->currentIndex().row());

    // Delete from list
    archiveItems.removeAt(ui->mainView->selectionModel()->currentIndex().row() + 1);
}

void MainWindow::OpenItem(const QModelIndex &index)
{
    /* * * Open file or folder * * */

    // Open file
    if (archiveName.isEmpty()) {
        // Local file
        QDesktopServices::openUrl(QUrl::fromLocalFile(ui->mainView->model()->data(fModel->index(index.row(), 0)).toString()));
    }
    else {
        // File from archive
        if (QFileInfo(archiveName).suffix() == "zip") {
            // Initialize class Archiver for managing zip files
            // (class Azip is a wrapper for class KZip)
            OpenArchFile(new Archiver(new AZip()), index.row());
        }
        else if (QFileInfo(archiveName).suffix() == "7z") {
            OpenArchFile(new Archiver(new A7Zip()), index.row());
        }
        else { // gz
            OpenArchFile(new Archiver(new ATarGz()), index.row());
        }
    }
}

void MainWindow::OpenArchFile(Archiver *archive, const int &row)
{
    /* * * Open file from archive * * */

    archive->setFileName(archiveName);
    if (!archive->open(QIODevice::ReadOnly)) {
        return;
    }
    const KArchiveDirectory *dir = archive->directory();

    QStringList l = dir->entries();
    QStringList::ConstIterator it = l.constBegin();

    for (; it != l.constEnd(); ++it)
        if (ui->mainView->model()->data(fModel->index(row, 1)).toString() == (*it).toLatin1().constData()) {
            // Create temporary dir
            QDir(QDir::tempPath()).mkdir(".QtArc");

            // Extract the file to a temporary folder and open it
            if (dir->file((*it))->copyTo(QDir::tempPath() + "/.QtArc")) {
                QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::tempPath() + "/.QtArc/" + (*it).toLatin1().constData()));
            }
            return;
        }
    archive->close();
}
// endregion Files and folders

// region Object size

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

        foreach (QFileInfo fInfo, list) {
            /* If the current item is a directory and not "." or ".."
             * (in Linux "." is a pointer to the current directory,
             * ".." is a pointer to the parent directory) -
             * skip them
             */
            if(fInfo.isDir()) {
                float s = 0;
                // Call dirSize recursively
                dirSize(fInfo, s);
                num += s;
            }
            // Determine the size of the included files
            num += fInfo.size();
        }
}
// endregion Object size

// region Appearance

void MainWindow::CustomizeTable()
{
    /* * * Customize table * * */

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
}

void MainWindow::EnableActions(const int &state)
{
    /* * * Enable or disable actions (1 - for archive, 2 - for files and folders, 0 - default state) * * */

    switch (state) {
    case 1: // Archive
        ui->saveArcCopy->setEnabled(true);
        ui->compessArc->setEnabled(false);

        ui->addFiles->setEnabled(false);
        ui->addFolder->setEnabled(false);
        ui->extractToDir->setEnabled(true);

        ui->openFile->setEnabled(false);
        ui->deleteFile->setEnabled(false);
        ui->closeArc->setEnabled(true);
        break;
    case 2: // Files and folders
        ui->saveArcCopy->setEnabled(false);
        ui->compessArc->setEnabled(true);

        ui->addFiles->setEnabled(true);
        ui->addFolder->setEnabled(true);
        ui->extractToDir->setEnabled(false);

        ui->openFile->setEnabled(true);
        ui->deleteFile->setEnabled(true);
        ui->closeArc->setEnabled(true);
        break;
    default:    // Default
        ui->saveArcCopy->setEnabled(false);
        ui->compessArc->setEnabled(false);

        ui->addFiles->setEnabled(true);
        ui->addFolder->setEnabled(true);
        ui->extractToDir->setEnabled(false);

        ui->openFile->setEnabled(false);
        ui->deleteFile->setEnabled(false);
        ui->closeArc->setEnabled(false);
        break;
    }
}
// endregion Appearance

void MainWindow::closeEvent(QCloseEvent *e)
{
    /* * * Before exit delete temporary folder * * */

    if (QDir(QDir::tempPath() + "/.QtArc").exists())
        QDir(QDir::tempPath() + "/.QtArc").removeRecursively();

    QWidget::closeEvent(e);
}
