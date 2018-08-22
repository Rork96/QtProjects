#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QStandardItemModel>

#include <QtCore/QFileInfo>

// For zip, 7z, tar.gz
#include "Archive.h"

#include <karchivedirectory.h>

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
    QString archiveName;                                    // Current archive
    QStringList archiveItems;                               // Items for compression
    QStandardItemModel *fModel;                             // Model for view
    QString arcDir;                                         // Current directory in an archive

private:
    void OpenArc();                                         // Open archive
    void ExtractArc();                                      // Extract
    inline Archiver *GetArcType();                          // Get Archive type
    void CompressIntoArchive();                             // Compress into archive
    void CloseArchive();                                    // Close current archive or clear list
    void AddFiles();                                        // Add files into list for compression
    void AddFolders();                                      // Add folders into list for compression
    inline bool AddItemsToModel(const QFileInfoList &items);    // Add items to list
    void DelItem();                                         // Delete file or folder from list
    void SaveAsArc();                                       // Save archive as ...
    void OpenItem(const QModelIndex &index);                // Open file or folder
    void GoBack();                                          // Go to previous folder
    // Identify size of the file or the folder
    // Return QString and objType
    QString objSize(const QFileInfo &fileInfo, QString &objType);
    // Folder size (return num)
    void dirSize(const QFileInfo &inf, float &num);
    // Add files from archive to list
    void ListRecursive(const KArchiveDirectory *dir, const QString &path);
    // Customize table
    void CustomizeTable();
    // Enable or disable actions (1 - for archive, 2 - for files and folders, 0 - default state)
    void EnableActions(const int &state = 0);
    // Open file from archive
    void OpenArchFile(Archiver *archive, const int &row);
    // Before exit delete temporary folder
    void closeEvent(QCloseEvent *e) override;
};

#endif // MAINWINDOW_H
