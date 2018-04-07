#include "appcore.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>

#include <QDebug>

#include "quazip-Qt5/quazip/JlCompress.h"

AppCore::AppCore(QObject *parent) :
        BaseClass(parent)
{
    fileSystemModel.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);
    fileSystemModel.setRootPath(QDir().homePath());
}

void AppCore::compressFiles()
{
    /* * * Receive data from qml * * */
    /* * * Compress dir * * */

    QStringList fNames = QFileDialog::getOpenFileNames(nullptr, "Choose files",
                                                       QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                       "All files (*.*)");

    if (fNames.isEmpty())
        return; // Файл не выбран

    QFileInfo fInfo(fNames.at(0));
    QDir dir(fInfo.path());
    QString path = fInfo.path() + "/" + dir.dirName() + ".zip";

    JlCompress::compressFiles(path, fNames);
}

void AppCore::extractArchive()
{
    /* * * Extract archive * * */

    QString fName = QFileDialog::getOpenFileName(nullptr, "Choose archive",
                                                 QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                 "Archive files (*.zip)");

    if (fName.isEmpty())
        return; // Файл не выбран

    QFileInfo fInfo(fName);
    QString dirName = fInfo.path() + "/" + fInfo.baseName();

    JlCompress::extractDir(fName, dirName);
}

void AppCore::compressDir()
{
    /* * * Compress dir * * */

    QString DirName = QFileDialog::getExistingDirectory(nullptr, "Choose directory",
                                                        QStandardPaths::locate(QStandardPaths::HomeLocation, QString()));

    if (DirName.isEmpty())
        return; // Файл не выбран

    QDir dir(DirName);
    QString ArchiveName = dir.currentPath() + "/" + dir.dirName() + ".zip";

    JlCompress::compressDir(ArchiveName, DirName);
}

void AppCore::openArchive()
{
    /* * * Open archive * * */

    QString fName = QFileDialog::getOpenFileName(nullptr, "Choose archive",
                                                 QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                 "Archive files (*.zip)");

    if (fName.isEmpty())
        return; // Файл не выбран

    QFileInfo fInfo(fName);

#ifdef Q_OS_WIN
    // Path for temporary files in Windows + file name without path and symbolic link (.zip)
    QString tempPath = "C:/Users/Default/AppData/Local/Temp/QZiper/" + fInfo.baseName();
#endif

#ifdef Q_OS_LINUX
    // Path for temporary files in Linux + file name without path and symbolic link (.zip)
    QString tempPath = "/tmp/QZiper/" + fInfo.baseName();
#endif

    // If dir is exist - delete
    QDir dir(tempPath);
    if (dir.exists())
        dir.removeRecursively();

    // Create dir
    dir.mkdir(tempPath);

    // Extract to temporary dir
    JlCompress::extractDir(fName, tempPath);

    // View extracted files

//    fileSystemModel.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);
//    fileSystemModel.setRootPath(tempPath);
}

void AppCore::aboutQt()
{
    /* * * About Qt * * */

    QMessageBox::aboutQt(nullptr, "About Qt");
}

void AppCore::aboutProgram()
{
    /* * * About program * * */

    QString aboutText;
    aboutText = "          QZiper v 1.0.0  \n\n";
    aboutText += "Автор  : \tmasterarrow\n\n";
    aboutText += "email  : \tmasterarrows@gmail.com\n\n";
    aboutText += "          Copyright © 2018\n";

    QMessageBox::about(nullptr, "About QImageViewer", aboutText);
}
