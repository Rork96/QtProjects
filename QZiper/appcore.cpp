#include "appcore.h"
#include <QFileInfo>
#include <QMessageBox>

#include <QDebug>

#include "quazip-Qt5/quazip/JlCompress.h"

AppCore::AppCore(QObject *parent) :
        BaseClass(parent)
{
}

void AppCore::compressFiles(QString FileNames, QString ArchiveName)
{
    /* * * Receive data from qml * * */
    /* * * Compress dir * * */

    /*if (FileNames.isEmpty() || ArchiveName.isEmpty())
        return;*/

    if (FileNames.isEmpty())
        return; // Файл не выбран

    qDebug() << FileNames;

    QFileInfo fInfo(FileNames);
    ArchiveName = fInfo.path() + "/" + fInfo.baseName() + ".zip";
    JlCompress::compressFile(ArchiveName, FileNames);

    /*
    if (FileNames.count() == 1) {
        // Single file
        QString fName = FileNames.at(0);
        QFileInfo fInfo(fName);
        ArchiveName = fInfo.path() + "/" + fInfo.baseName() + ".zip";
        JlCompress::compressFile(ArchiveName, fName);
    }
    else {
        // List of files
        QString fName = FileNames.at(0);
        QFileInfo fInfo(fName);
        ArchiveName = fInfo.path() + "/" + fInfo.baseName() + ".zip";
        JlCompress::compressFiles(ArchiveName, FileNames);
    }
    */
}

void AppCore::extractArchive(QString ArchiveName, QString DirName)
{
    /* * * Extract archive * * */
/*
    if (ArchiveName.isEmpty())
        return;

    if (DirName.isEmpty()) {
        // File path and file name without symbolic link (.zip)
        QFileInfo fInfo(ArchiveName);
        DirName = fInfo.canonicalFilePath();
    }

    JlCompress::extractDir(ArchiveName, DirName);*/
    QStringList list = JlCompress::getFileList(ArchiveName);

    foreach (QString item, list) {
        qDebug() << item;
    }
}

void AppCore::compressDir(QString DirName, QString ArchiveName)
{
    /* * * Compress dir * * */

    if (DirName == "") {
        QFileInfo fInfo(ArchiveName);
        DirName = fInfo.path() + "/";
    }

    if (DirName.isEmpty() || ArchiveName.isEmpty())
        return;

    JlCompress::compressDir(ArchiveName, DirName);
}

void AppCore::openArchive(QString ArchiveName)
{
    /* * * Open archive * * */

    QFileInfo fInfo(ArchiveName);

#ifdef Q_OS_WIN
    // Path for temporary files in Windows + file name without path and symbolic link (.zip)
    QString tempPath = "C:/Users/Default/AppData/Local/Temp/";
#endif

#ifdef Q_OS_LINUX
    // Path for temporary files in Linux + file name without path and symbolic link (.zip)
    QString tempPath = "/tmp/";
#endif

    // Extract to temporary dir
    extractArchive(ArchiveName, tempPath);

    // View extracted files
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
