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
    arcReader.start();
}