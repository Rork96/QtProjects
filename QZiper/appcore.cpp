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
}

void AppCore::compressFiles(QObject *window)
{
    /* * * Compress dir * * */

    /*QStringList fNames = QFileDialog::getOpenFileNames(nullptr, "Choose files",
                                                       QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                       "All files (*.*)");

    if (fNames.isEmpty())
        return; // Файл не выбран*/

    QString fileName = (window->property("fileName")).toString(); // Wrong type ?
    QUrl folderPath = (window->property("folderPath")).toUrl();
    QString archiveName = (window->property("archiveName")).toString();

    qDebug() << fileName;
    qDebug() << folderPath;
    qDebug() << archiveName;

    QStringList fNames; // = fileName;

#ifdef Q_OS_WIN
    QString regExp = "file:///";
#endif

#ifdef Q_OS_LINUX
    QString regExp = "file://";
#endif

    foreach (QString str, fileName) {
        str.replace("file://","");
        qDebug() << str;
        fNames.append(str);
    }

    /*
    var path = compress.folderPath.toString()
    console.log(path)
    // Remove prefixed "file:///"
    path = path.replace(/^(file:\/{3})/,"")
    // Unescape html codes like '%23' for '#'
    var cleanPath = decodeURIComponent(path)
    pathField.text = cleanPath
    */


    QString path = folderPath.toLocalFile() + "/" + archiveName + ".zip";

    qDebug() << path;

    //QFileInfo fInfo(fNames.at(0));
    //QDir dir(fInfo.path());
    //QString path = fInfo.path() + "/" + dir.dirName() + ".zip";

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

void AppCore::compressDir(QObject *window)
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

void AppCore::openArchive(QObject *treeView)
{
    /* * * Open archive * * */

    QString fName = QFileDialog::getOpenFileName(nullptr, "Choose archive",
                                                 QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                 "Archive files (*.zip)");

    if (fName.isEmpty())
        return; // Файл не выбран

    QFileInfo fInfo(fName);

    // Path for temporary files + file name without path and symbolic link (.zip)
    QString temp = tempPaht + fInfo.baseName();

    // If dir is exist - delete
    QDir tempDir(temp);
    if (tempDir.exists())
        tempDir.removeRecursively();

    // Create dir
    tempDir.mkdir(temp);

    // Extract to temporary dir
    JlCompress::extractDir(fName, temp);

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
    treeView->setProperty("elemntVisible", true);
}

void AppCore::saveAs()
{
    /* * * Save archive as * * */
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
