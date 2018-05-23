#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QStandardItemModel>

#include <QtCore/QFileInfo>

// For zip, 7z, tar.gz
#include "Archive.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    // Open archive when program starts
    void OpenArchive(const QString &arcName);

private:
    Ui::MainWindow *ui;
    QString archiveName;                            // Current archive
    QStringList archiveItems;                       // Items for compression
    QStandardItemModel *fModel;                     // Model for view

private:
    void OpenArc();                                 // Open archive
    void OpenArch(Archiver *arc);
    void ExtractArc();                              // Extract
    bool ExtractArch(Archiver *arc, const QString &dest);
    void CompressIntoArchive();                     // Compress into archive
    bool CompressArch(Archiver *arc);
    void CloseArchive();                            // Close current archive
    void AddFiles();                                // Add files into list for compression
    void DelFile();                                 // Delete file from list
    void SaveAsArc();                               // Save archive as ...
    void setArchiveName(const QString &arcName);    // Set archive name
    // Identify size of the file or the folder
    // Return QString and objType
    QString objSize(const QFileInfo fileInfo, QString &objType);
    // Folder size (return num)
    void dirSize(const QFileInfo inf, float &num);
    // Add files from archive to list
    void ListRecursive(const KArchiveDirectory *dir, const QString &path);
    // Customize table
    void CustomizeTable();
};

#endif // MAINWINDOW_H
