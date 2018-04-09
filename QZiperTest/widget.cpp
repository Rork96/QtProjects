#include "widget.h"
#include "ui_widget.h"

#include <QFileInfo>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QDir>

#include <QDebug>

#include "quazip-Qt5/quazip/JlCompress.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked() // Works
{
    // Zip file
    QString fName = QFileDialog::getOpenFileName(this, "Open file",
                                                 QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                 "All files (*.*)");

    if (fName.isEmpty())
        return; // Файл не выбран

    QFileInfo fInfo(fName);
    QString path = fInfo.path() + "/" + fInfo.baseName() + ".zip";

    ui->label_2->setText("File: " + fName);
    ui->label->setText("Archive: " + path);

    JlCompress::compressFile(path, fName);
}

void Widget::on_pushButton_2_clicked() // Works
{
    // Unzip file
    QString fName = QFileDialog::getOpenFileName(this, "Choose file",
                                                 QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                 "All files (*.*)");

    if (fName.isEmpty())
        return; // Файл не выбран

    QFileInfo fInfo(fName);
    QString dirName = fInfo.path();

    ui->label_2->setText("Dir: " + dirName);
    ui->label->setText("Archive: " + fName);

    JlCompress::extractDir(fName, dirName);
}

void Widget::on_pushButton_5_clicked() // Works
{
    // Zip files
    QStringList fNames = QFileDialog::getOpenFileNames(this, "Choose files",
                                                 QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                 "All files (*.*)");

    if (fNames.isEmpty())
        return; // Файл не выбран

    QFileInfo fInfo(fNames.at(0));
    QString path = fInfo.path() + "/" + fInfo.baseName() + ".zip";

    ui->label_2->setText("File: " + fNames.at(0));
    ui->label->setText("Archive: " + path);

    JlCompress::compressFiles(path, fNames);
}

void Widget::on_pushButton_4_clicked() // Works
{
    // Unzip files
    QString fName = QFileDialog::getOpenFileName(this, "Choose archive",
                                                 QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                 "Archive files (*.zip)");

    if (fName.isEmpty())
        return; // Файл не выбран

    QFileInfo fInfo(fName);
    QString dirName = fInfo.path();

    ui->label_2->setText("Dir: " + dirName);
    ui->label->setText("Archive: " + fName);

    JlCompress::extractDir(fName, dirName);
}

void Widget::on_pushButton_6_clicked() // Works
{
    // Zip folder
    QString dirName = QFileDialog::getExistingDirectory(this, "Choose directory",
                                                       QStandardPaths::locate(QStandardPaths::HomeLocation, QString()));

    if (dirName.isEmpty())
        return; // Файл не выбран

    qDebug() << dirName;

    QDir dir(dirName);
    QString path = dir.currentPath() + "/" + dir.dirName() + ".zip";

    ui->label_2->setText("Dir: " + dirName);
    ui->label->setText("Archive: " + path);

    JlCompress::compressDir(path, dirName);
}

void Widget::on_pushButton_3_clicked()  // Works
{
    // Unzip folder
    QString fName = QFileDialog::getOpenFileName(this, "Choose archive",
                                                 QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                 "Archive files (*.zip)");

    if (fName.isEmpty())
        return; // Файл не выбран

    QFileInfo fInfo(fName);
    QString dirName = fInfo.path() + "/" + fInfo.baseName();

    ui->label_2->setText("Dir: " + dirName);
    ui->label->setText("Archive: " + fName);

    JlCompress::extractDir(fName, dirName);
}
