#include "appcore.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QVariant>

#include "quazip-Qt5/quazip/JlCompress.h"

AppCore::AppCore(QObject *parent) :
        BaseClass(parent)
{
}

bool AppCore::compressFiles(QObject *window)
{
    /* * * Compress dir * * */

    // Get data from QML
    QString fileName = (window->property("fileName")).toString(); // String "abc;abc;abc;"
    QUrl folderPath = (window->property("folderPath")).toUrl();
    QString archiveName = (window->property("archiveName")).toString();

    if (fileName.isEmpty())
        return false;

    QStringList fNames;

#ifdef Q_OS_WIN
    QString regExp = "file:///";
#endif

#ifdef Q_OS_LINUX
    QString regExp = "file://";
#endif

    // Split string (";" - separator), without empty strings
    QStringList strList = fileName.split(";", QString::SkipEmptyParts);

    // Format string "file:///abc" to "/abc" - Linux
    // Format string "file:///abc" to "abc" - Windows
    foreach (QString str, strList) {
        str.replace(regExp,"");
        fNames.append(str);
    }

    // Archive path
    QString path = folderPath.toLocalFile() + "/" + archiveName + ".zip";

    // Compress
    return JlCompress::compressFiles(path, fNames);
}

bool AppCore::extractArchive(QObject *window)
{
    /* * * Extract archive * * */

    // Get data from QML
    QUrl fileName = (window->property("fileName")).toUrl();
    QUrl folderPath = (window->property("folderPath")).toUrl();

    if (fileName.isEmpty())
        return false;

    if (folderPath.toLocalFile().isEmpty()) {
        // Choose folder
        folderPath = QFileDialog::getExistingDirectoryUrl(nullptr,"Choose folder",
            QUrl(QStandardPaths::locate(QStandardPaths::HomeLocation, QString())));
    }

    // Format from QUrl to QString
    QString fName = fileName.toLocalFile();
    QString path = folderPath.toLocalFile() + "/" + QFileInfo(fName).baseName();

    if (!JlCompress::extractDir(fName, path).isEmpty()) {
        return true;
    }
    else {
        return false;
    }
}

bool AppCore::compressDir(QObject *window)
{
    /* * * Compress dir * * */

    // Get data from QML
    QUrl fileName = (window->property("fileName")).toUrl();
    QUrl folderPath = (window->property("folderPath")).toUrl();
    QString archiveName = (window->property("archiveName")).toString();

    if (fileName.isEmpty())
        return false;

    // Format from QUrl to QString
    QString fName = fileName.toLocalFile();

    // Archive path
    QString path = folderPath.toLocalFile() + "/" + archiveName + ".zip";

    // Compress
    return JlCompress::compressDir(path, fName);
}

bool AppCore::openArchive(QObject *treeView, QUrl fileName)
{
    /* * * Open archive * * */

    // Format from QUrl to QString
    QString fName = fileName.toLocalFile();

    if (fName.isEmpty())
        return false;

    QFileInfo fInfo(fName);

    // Path for temporary files + file name without path and symbolic link (.zip)
    QString temp = tempPaht + fInfo.baseName();

    // If dir is exist - delete
    QDir tempDir(temp);
    if (tempDir.exists())
        tempDir.removeRecursively();

    // Create dir
    tempDir.mkdir(temp);

    bool result = false;

    // Extract to temporary dir
    if (!JlCompress::extractDir(fName, temp).isEmpty())
        result = true;

    // View extracted files in treeView in QMl
#ifdef Q_OS_WIN
    treeView->setProperty("path", "file:///" + temp);
    // Save start path
    treeView->setProperty("startPath", "file:///" + temp);
#endif

#ifdef Q_OS_LINUX
    treeView->setProperty("path", "file://" + temp);
    // Save start path
    treeView->setProperty("startPath", "file://" + temp);
#endif
    // Set elements visible
    treeView->setProperty("elemntVisible", result);

    return result;
}

bool AppCore::saveAs(QObject *window)
{
    /* * * Save archive as * * */

    // Get data from QML
    QUrl fileName = (window->property("fileName")).toUrl();

    // Format from QUrl to QString
    QString fName = fileName.toLocalFile();

    if (fName.isEmpty())
        return false;

    QString newName = QFileDialog::getSaveFileName(nullptr, "Choose folder for saving",
        QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                   "Archive files (*.zip)");

#ifdef Q_OS_LINUX
    newName += ".zip";
#endif

    return QFile::copy(fName, newName);
}

void AppCore::close()
{
    /* * * Delete temporary folder before closing * * */

    // Delete folder QZiper in temporary dir
    QDir dir(tempPaht);
    dir.cdUp();
    dir.removeRecursively();
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
