#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QStandardItemModel>

// Library
#include <kzip.h>                   // zip
#include <k7zip.h>                  // 7zip
#include <ktar.h>                   // tar.gz
#include <kcompressiondevice.h>     // bz2
#include <QtCore/QFileInfo>

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
    void ExtractArc();                              // Extract
    bool ExtractZip(const QString &arcName);        // Extract zip
    bool Extract7Zip(const QString &arcName);       // Extract 7zip
    bool ExtractTarGz(const QString &arcName);      // Extract tar.gz
    void CompressIntoArchive();                     // Compress into archive
    bool CompressZip();                             // Compress into zip
    bool Compress7Zip();                            // Compress into 7zip
    bool CompressTarGz();                           // Compress into tar.gz
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
};

#endif // MAINWINDOW_H
