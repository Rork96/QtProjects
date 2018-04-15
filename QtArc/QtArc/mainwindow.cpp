#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QFileDialog>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* * * Connections * * */ {
        // Quit
        connect(ui->quitProgram, &QAction::triggered, this, &MainWindow::close);
        // Open archive
        connect(ui->openArc, &QAction::triggered, this, &MainWindow::OpenArchive);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenArchive()
{
    /* * * Open archive * * */

    OpenArc(QString());
}

void MainWindow::OpenArc(QString archiveName)
{
    /* * * Open archive when program starts * * */

    if (archiveName.isEmpty()) {
        archiveName = QFileDialog::getOpenFileName(this, "Choose files",
                                                    QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                    "Archives (*.zip | *.rar | *.7z | *.bz  | *.bz2 | *.gz | *.cpio)");
    }
/*
    // Archive
    QArchive::Reader arcReader(archiveName);
    // Connect
    connect(&arcReader, &QArchive::Reader::archiveFiles, [&](QString archive, QStringList files) {
        qDebug() << archive << " :: ";
        qDebug() << files;
    });
    // If error
    connect(&arcReader, &QArchive::Reader::error, [&](short code, QString file) {
        switch(code) {
            case QArchive::ARCHIVE_READ_ERROR:
                qDebug() << "Unable to find archive :: " << file;
                break;
            case QArchive::ARCHIVE_QUALITY_ERROR:
                qDebug() << "Bad archive! :: " << file;
                break;
            case QArchive::ARCHIVE_UNCAUGHT_ERROR:
                qDebug() << "Fatal error. :: " << file;
                break;
            default:
                qDebug() << "Unknown error. :: " << file;
                break;
        }
    });
    // Extract
    arcReader.start();*/
/*
    QString dirName = QString();
    if (archiveName.isEmpty()) {
        dirName = QFileDialog::getExistingDirectory(this, "Choose files",
                                                    QStandardPaths::locate(QStandardPaths::HomeLocation, QString()));
    }
    QDir dir;
    dir.cd(dirName);
    QString file7z = dir.path() + ".7z";
    qDebug() << dir;
    qDebug() << dirName;
    qDebug() << file7z;
    QArchive::Compressor e(file7z, dirName);
    QObject::connect(&e, &QArchive::Compressor::finished, [&]() {
        qDebug() << "Finished all jobs";
    });
    QObject::connect(&e, &QArchive::Compressor::error, [&](short code, QString file) {
        qDebug() << "error code:: " << code << " :: " << file;
    });
    e.start();
    */
    //QArchive::Extractor Archiver(archiveName);


    QFileInfo fInfo(archiveName);
    QString destPath = fInfo.path() + "/" + fInfo.baseName() + "/";

    QDir dir;
    dir.mkdir(destPath);

    // Set destination path
/*   Archiver.setDestination(fInfo.path() + "/" + fInfo.baseName());

    // connect callback
    QObject::connect(&Archiver , &QArchive::Extractor::extracted , [&](QString file)
    {
        qDebug() << "extracted :: " << file;
    });

    // Start Extraction
    Archiver.start(); // never use run
    */

    QArchive::Extractor Extractor(archiveName, destPath);
    Extractor.start();
}