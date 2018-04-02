#include "appcore.h"
#include <QFileInfo>

#include "quazip-Qt5/quazip/JlCompress.h"

AppCore::AppCore(QObject *parent) :
        BaseClass(parent)
{
}

void AppCore::compressFiles(QStringList FileNames, QString ArchiveName)
{
    /* * * Receive data from qml * * */
    /* * * Compress dir * * */

    if (FileNames.isEmpty() || ArchiveName.isEmpty())
        return;

    if (FileNames.count() == 1) {
        // Single file
        QString File = FileNames.at(0);
        JlCompress::compressFile(File, ArchiveName);
    }
    else {
        // List of files
        JlCompress::compressFiles(ArchiveName, FileNames);
    }
}

void AppCore::extractArch(QString ArchiveName, QString DirName)
{
    /* * * Extract archive * * */

    if (ArchiveName.isEmpty())
        return;

    if (DirName.isEmpty()) {
        // File path and file name without symbolic link (.zip)
        QFileInfo fInfo(ArchiveName);
        DirName = fInfo.canonicalFilePath();
    }

    JlCompress::extractDir(ArchiveName, DirName);
}

void AppCore::compressDir(QString DirName, QString ArchiveName)
{
    /* * * Compress dir * * */

    if (DirName.isEmpty() || ArchiveName.isEmpty())
        return;

    JlCompress::compressDir(DirName, ArchiveName);
}

void AppCore::openArchive(QString ArchiveName)
{
    /* * * Open archive * * */

    QFileInfo fInfo(ArchiveName);

#ifdef Q_OS_WIN
    // Path for temporary files in Windows + file name without path and symbolic link (.zip)
    QString tempPath = "C:/Users/Default/AppData/LocalTemp" + fInfo.baseName();
#endif

#ifdef Q_OS_LINUX
    // Path for temporary files in Linux + file name without path and symbolic link (.zip)
    QString tempPath = "/tmp" + fInfo.baseName();
#endif

    // Extract to temporary dir
    extractArchive(ArchiveName, tempPath);

    // View extracted files
}