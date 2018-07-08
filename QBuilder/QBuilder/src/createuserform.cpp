#include "createuserform.h"
#include "ui_createuserform.h"

#include <QPainter>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QDebug>

CreateUserForm::CreateUserForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateUserForm)
{
    ui->setupUi(this);

    initData(Table);

    // View data with mapper
    mapper->addMapping(ui->userNameLine, 1);
    // Do not display existing password - 2
    mapper->addMapping(ui->emailLine, 4);
    mapper->addMapping(ui->accountNameLine, 7);
    mapper->addMapping(ui->companyLine, 10);
    mapper->addMapping(ui->productLine, 11);
    // Last login - 12 - type: timestamp (date and time without time zone)
    mapper->addMapping(ui->phoneLine, 13);

    groupModel = new BaseComboModel("name", "groups", this, Table, "group_area");
    ui->groupAreaListView->setModel(groupModel);
    ui->groupAreaListView->setRowHidden(0, true);

    docModel = new BaseComboModel("group_name", "document_group", this, Table, "docum_group");
    ui->docGroupListView->setModel(docModel);
    ui->docGroupListView->setRowHidden(0, true);

    // Init comboBox models with data
    accountModel = new BaseComboModel("acc_type", "account_table", this, Table, "account_type");
    tenantModel = new BaseComboModel("tenant_code || ': ' || name", "tenant", this, Table, "tenant_code");
    userModel = new BaseComboModel("user_type || ' - '", "security_filters", this, Table, "users_type");
    currencyModel = new BaseComboModel("currency_format", "currency_table", this, Table, "currency");
    currencyTypeModel = new BaseComboModel("curr_type", "currency_type_table", this, Table, "currency_type");
    timezoneModel = new BaseComboModel("timezone_name", "timezone_table", this, Table, "timezone");
    timeFormatModel = new BaseComboModel("standard_format", "time_format_table", this, Table, "time_format");
    dateModel = new BaseComboModel("date_format", "date_table", this, Table, "date");

    // Add comboBoxes and their models to QLists
    combo = {ui->accountTypeBox, ui->tenantCodeBox, ui->userTypeBox, ui->curFormatBox, ui->curTypeBox, ui->timeZoneBox,
             ui->timeFormatBox, ui->dateFormatBox};
    cbModel = {accountModel, tenantModel, userModel, currencyModel, currencyTypeModel, timezoneModel, timeFormatModel,
               dateModel};

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
    connect(ui->passwordLengthBox, &QCheckBox::stateChanged, this, [this] {
        checkPasswordLength(QString());
    });
}

CreateUserForm::~CreateUserForm()
{
    delete ui;
}

void CreateUserForm::submitChanges()
{
    // Save changes to database

    QSqlQuery query;
    QString str = QString("SELECT EXISTS (SELECT 'username' FROM" + Table +
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

        int id = -1;
        if (isEdit) {
            id = model->record(mapper->currentIndex()).value("id").toInt();
        }

        // Save data from comboBoxes to database
        for (int i = 0; i < cbModel.count(); i++) {
            cbModel.at(i)->saveToDB(combo.at(i)->itemData(combo.at(i)->currentIndex(), Qt::UserRole).toInt(), id);
        }

        // Write account checkBox
        QString value;
        if (ui->accountCheckBox->isChecked()) value = "Active";
        else value = "Inactive";

        QString str = QString("UPDATE " + Table + " SET active_account = '%1' WHERE id = %2").arg(value).arg(id);
        query.exec(str);

        // Write password
        if (!isEdit || !ui->passwordLabel->text().isEmpty()) {
            QString str = QString("UPDATE " + Table + " SET password = '%1' WHERE id = %2").arg(ui->passwordLine->text()).arg(id);
            query.exec(str);
        }

        auto saveListData = [&id](BaseComboModel *model, QListView *view, QString table, QString column)
        {
            QModelIndex index = view->currentIndex();
            qDebug() << index;
            QString itemText = index.data(Qt::DisplayRole).toString();

            QString str = QString("SELECT id FROM " + table + " WHERE " + column + " = '%1'").arg(itemText);
            QSqlQuery query;
            query.exec(str);
            query.next(); // Query doesn't work properly in second time
            model->saveToDB(query.value(0).toInt(), id);
        };

        //saveListData(groupModel, ui->groupAreaListView, GroupsTable, "name");
        //saveListData(docModel, ui->docGroupListView, DocTable, "group_name");

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

void CreateUserForm::setRowIndex(int rowIndex, int id)
{
    // User chose to edit data from the table
    BaseForm::setRowIndex(rowIndex, id);

    // Init comboBoxes with data from database
    auto initComboBox = [&id](QComboBox *box, BaseComboModel *comboModel)
    {
        box->setModel(comboModel);
        box->setCurrentIndex(box->findText(comboModel->getTextValue(id)));
    };

    for (int i = 0; i < cbModel.count(); i++) {
        initComboBox(combo.at(i), cbModel.at(i));
    }

    // Connect checkBox
    QSqlQuery query;
    query.prepare( "SELECT active_account FROM " + Table + " WHERE id = ?" );
    query.addBindValue(id);
    query.exec();

    while (query.next()) {
        ui->accountCheckBox->setChecked(query.value(0).toString() == "Active");
    }

    // groupModel, ui->groupAreaListView
    // docModel, ui->docGroupListView
}

void CreateUserForm::checkPasswordLength(const QString &arg1)
{
    // Check password length

    int length = ui->passwordLine->text().length();

    if (length < 5 && !ui->passwordLengthBox->isChecked()) {
        ui->passwordLine->setStyleSheet("QLineEdit {color: red;}");
    }
    else {
        ui->passwordLine->setStyleSheet("QLineEdit {color: black;}");
    }
}
