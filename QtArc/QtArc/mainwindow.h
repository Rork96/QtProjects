#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>

// Library
#include <KArchive.h>
#include <kzip.h>                   // zip
#include <k7zip.h>                  // 7zip
#include <ktar.h>                   // tar.gz
#include <KCompressionDevice.h>     // bz2

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
    void OpenArc(QString archiveName);

private:
    Ui::MainWindow *ui;
    // Open archive
    void OpenArchive();
    bool ReadZip(QFileInfo archiveInfo);    // Decompress zip
    bool Read7Zip(QFileInfo archiveInfo);   // Decompress 7zip
    bool ReadTarGz(QFileInfo archiveInfo);  // Decompress tar.gz
    bool ReadBz2(QFileInfo archiveInfo);    // Decompress bz2
};

#endif // MAINWINDOW_H
