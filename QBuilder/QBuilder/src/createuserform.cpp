#include "createuserform.h"
#include "ui_createuserform.h"

#include <QPainter>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>
#include <QMessageBox>
#include <QSqlQuery>

CreateUserForm::CreateUserForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateUserForm)
{
    ui->setupUi(this);

    initData(Table);

    // View data with mapper
    mapper->addMapping(ui->userNameLine, 1);
    mapper->addMapping(ui->passwordLine, 2);

    model->insertRow(model->rowCount(QModelIndex()));

    mapper->toLast();

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateUserForm::submitChanges);

    connect(ui->avatarButton, &QPushButton::clicked, this, &CreateUserForm::openImage);
    connect(ui->bodyImgButton, &QPushButton::clicked, this, &CreateUserForm::openImage);
    connect(ui->menuImgButton, &QPushButton::clicked, this, &CreateUserForm::openImage);

    connect(ui->passwordLine, &QLineEdit::textChanged, this, &CreateUserForm::checkPasswordLength);
}

CreateUserForm::~CreateUserForm()
{
    delete ui;
}

void CreateUserForm::submitChanges()
{
    // Save changes to database

    QSqlQuery query;
    QString str = QString("SELECT EXISTS (SELECT 'Group name' FROM" + Table +
                          " WHERE '" + Record + "' = '%1' AND id NOT LIKE '%2' )").arg(ui->userNameLine->text(),
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
    }
    model->select();
    mapper->toLast();

    // Send signal
    emit sygnalSubmit();
}

void CreateUserForm::openImage(/*QWidget *sender*/)
{
    // Open image

    QString fName = QFileDialog::getOpenFileName(this, "Choose files",
                           QStandardPaths::locate(QStandardPaths::HomeLocation, QString()),
                                                 "Supported files (*.png | *.jpg | *.jpeg);;"
                                                 "*.png;; *.jpg;; *.jpeg;; All files (*.*)");

    if(fName.isEmpty()) return;

    QPushButton *button = ((QPushButton *)sender());

    if (button == ui->avatarButton) {
        ui->avatarNameLabel->setText(QFileInfo(fName).fileName());
    }
    else if (button == ui->bodyImgButton) {
        ui->bodyImgNameLabel->setText(QFileInfo(fName).fileName());
    }
    else {
        ui->menuImgNameLabel->setText(QFileInfo(fName).fileName());
    }
}
/*
void CreateUserForm::setRowIndex(int rowIndex, int)
{
    // User chose to edit data from the table
    mapper->setCurrentIndex(rowIndex);
}
*/
void CreateUserForm::checkPasswordLength(const QString &arg1)
{
    // Check password length

    int length = ui->passwordLine->text().length();

    if (length > 5 && !ui->passwordLengthBox->isChecked()) {
        ui->passwordLabel->setText("Password - Too short");
    }
}
