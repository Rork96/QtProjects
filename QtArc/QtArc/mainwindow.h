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
    void OpenArchive();

private:
    Ui::MainWindow *ui;
    QString archiveName;        // Current archive
    QStringList archiveItems;   // Items for compression
    QStandardItemModel *fModel; // Model for view

public:
    void setArchiveName(const QString &arcName);    // Set archive name

private:
    void ExtractArc();              // Extract
    bool ExtractZip();              // Extract zip
    bool Extract7Zip();             // Extract 7zip
    bool ExtractTarGz();            // Extract tar.gz
    bool ExtractBz2();              // Extract bz2
    void CompressIntoArchive();     // Compress into archive
    bool CompressZip();             // Compress into zip
    bool Compress7Zip();            // Compress into 7zip
    bool CompressTarGz();           // Compress into tar.gz
    bool CompressBz2();             // Compress into bz2
    void CloseArchive();            // Close current archive
    void AddFiles();                // Add file into archive

    // Identify size of the file or the folder
    // Return QString and objType
    QString objSize(const QFileInfo fileInfo, QString &objType);
    // Folder size (return num)
    void dirSize(const QFileInfo inf, float &num);
};

#endif // MAINWINDOW_H
