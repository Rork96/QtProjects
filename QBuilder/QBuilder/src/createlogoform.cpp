#include "createlogoform.h"
#include "ui_createlogoform.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlRecord>
#include <QBuffer>

CreateLogoForm::CreateLogoForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateLogoForm)
{
    ui->setupUi(this);

    initData(Table);

    // View data in lineEdit with mapper
    mapper->addMapping(ui->listNameLine, 1);
    mapper->addMapping(ui->entryNameLine, 2);
    mapper->addMapping(ui->descreptionEdit, 3);
    mapper->addMapping(ui->imageNameLabel, 6);

    model->insertRow(model->rowCount(QModelIndex()));

    mapper->toLast();

    connect(ui->backButton, &QToolButton::clicked, this, [this] { emit sygnalBack(); });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateLogoForm::submitChanges);

    connect(ui->openImageButton, &QPushButton::clicked, this, &CreateLogoForm::openImage);
}

CreateLogoForm::~CreateLogoForm()
{
    delete ui;
}

void CreateLogoForm::submitChanges()
{
    // Save changes to database

    QSqlQuery query;
    QString str = QString("SELECT EXISTS (SELECT 'Entry name' FROM" + Table +
            " WHERE '" + Record + "' = '%1' AND id NOT LIKE '%2' )").arg(ui->entryNameLine->text(),
                                    model->data(model->index(mapper->currentIndex(), 0), Qt::DisplayRole).toInt());

    query.prepare(str);
    query.exec();
    query.next();

    // If exists
    if (mapper->currentIndex() > model->rowCount() && query.value(0) != 0) {
        QMessageBox::information(this, trUtf8("Error"), Record + trUtf8(" is already exists"));
        return;
    }
    else {
        // Insert new data

        mapper->submit();
        model->submitAll();

        int id = -1;
        if (isEdit) {
            id = model->record(mapper->currentIndex()).value("id").toInt();
        }

        // Write access type
        QString value;
        if (ui->headLogoRButton->isChecked()) value = "LOGO_HEADER";
        else value = "LOGO_MAIN";

        query.prepare( "UPDATE " + Table + " SET type = ? WHERE id = ?" );
        query.addBindValue(value);
        query.addBindValue(id);
        query.exec();

        // Save image
        if (imageChanged) {
            QPixmap pix = QPixmap(*ui->imageLabel->pixmap());
            QByteArray byteArray;
            QBuffer buffer(&byteArray);
            buffer.open(QIODevice::WriteOnly);
            pix.save(&buffer, "PNG");
            QVariant data = byteArray;
            query.prepare( "UPDATE " + Table + " SET image = ? WHERE id = ?" );
            query.addBindValue(data.toByteArray());
            query.addBindValue(id);
            query.exec();
        }
    }
    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateLogoForm::openImage()
{
    // Open image

    QString fName = QFileDialog::getOpenFileName(this, "Choose files",
                    QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                 "Supported files (*.png | *.jpg | *.jpeg);;"
                                                 "All files (*.*)");

    if(fName.isEmpty()) return;

    ui->imageNameLabel->setText(QFileInfo(fName).fileName());
    QPixmap pix = QPixmap(fName);
    ui->imageLabel->setPixmap(pix.scaled(400, 100, Qt::KeepAspectRatio));

    imageChanged = true;    // Write new image into database
}

void CreateLogoForm::setRowIndex(int rowIndex, int id)
{
    // User chose to edit data from the table
    BaseForm::setRowIndex(rowIndex, id);

    // Connect radioButtons
    QSqlQuery query;
    query.prepare( "SELECT type FROM " + Table + " WHERE id = ?" );
    query.addBindValue(id);
    query.exec();

    while (query.next()) {
        if (query.value(0).toString() == "LOGO_HEADER") {
            ui->headLogoRButton->setChecked(true);
        }
        else {
            ui->mainLogoRButton->setChecked(true);
        }
    }

    // Image logo name
    QString str = QString("SELECT image_name FROM %1 WHERE id = %2").arg(Table).arg(id);
    query.exec(str);
    query.next();
    ui->imageNameLabel->setText(query.value(0).toString());

    // Image
    QPixmap img = QPixmap();
    str = QString("SELECT image FROM %1 WHERE id = %2").arg(Table).arg(id);
    query.exec(str);
    query.next();
    img.loadFromData(query.value(0).toByteArray());
    ui->imageLabel->setPixmap(img.scaled(400, 100, Qt::KeepAspectRatio));
}
