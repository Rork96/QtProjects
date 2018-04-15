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
                                                    "Archives (*.zip | *.7z *.tar)");
    }

    if (archiveName.isEmpty())
        return;

    QFileInfo fInfo(archiveName);

    if (fInfo.suffix() == "zip") {

        KZip archive(archiveName);

        // Open the archive
        if (!archive.open(QIODevice::ReadOnly)) {
            return;
        }

        // Take the root folder from the archive and create a KArchiveDirectory object.
        // KArchiveDirectory represents a directory in a KArchive.
        const KArchiveDirectory *root = archive.directory();

        // We can extract all contents from a KArchiveDirectory to a destination.
        // recursive true will also extract subdirectories.
        QString destination = QDir::currentPath() + "/" + fInfo.baseName();
        bool recursive = true;
        root->copyTo(destination, recursive);

        archive.close();
    }
}
