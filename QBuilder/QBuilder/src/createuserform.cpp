#include "createuserform.h"
#include "ui_createuserform.h"

#include <QPainter>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QBuffer>
#include <QList>

CreateUserForm::CreateUserForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateUserForm)
{
    ui->setupUi(this);

    initData(Table);

    // View data with mapper
    mapper->addMapping(ui->userNameLine, 1);
    // Do not display existing password - 2
    mapper->addMapping(ui->emailLine, 3);
    mapper->addMapping(ui->accountNameLine, 6);
    mapper->addMapping(ui->companyLine, 9);
    mapper->addMapping(ui->productLine, 10);
    // Last login - 11 - type: timestamp (date and time without time zone)
    mapper->addMapping(ui->phoneLine, 12);
    mapper->addMapping(ui->colorBackLine, 22);
    mapper->addMapping(ui->colorMenuTextLine, 23);
    mapper->addMapping(ui->colorHighlightLine, 24);
    mapper->addMapping(ui->colorBorderLine, 25);
    mapper->addMapping(ui->colorBodyBackLine, 26);
    mapper->addMapping(ui->colorLinkLine, 27);
    mapper->addMapping(ui->colorBodyTextLine, 28);
    mapper->addMapping(ui->colorBodyInfoLine, 29);
    mapper->addMapping(ui->colorSectionLine, 30);
    mapper->addMapping(ui->colorSectionHeaderLine, 31);
    mapper->addMapping(ui->colorSectionBackLine, 32);
    mapper->addMapping(ui->colorHeaderLine, 33);
    mapper->addMapping(ui->colorHBorderLine, 34);
    mapper->addMapping(ui->colorSearchLine, 35);
    mapper->addMapping(ui->colorSelectedSearchLine, 36);
    mapper->addMapping(ui->colorFieldLine, 37);
    mapper->addMapping(ui->colorFieldSelectedLine, 38);
    mapper->addMapping(ui->colorTabLine, 39);
    mapper->addMapping(ui->colorTabUnselectedLine, 40);
    mapper->addMapping(ui->colorMessageLine, 41);
    mapper->addMapping(ui->colorMessageBackLine, 42);
    mapper->addMapping(ui->colorChart_1_Line, 43);
    mapper->addMapping(ui->colorChart_2_Line, 44);
    mapper->addMapping(ui->colorChart_3_Line, 45);
    mapper->addMapping(ui->colorChart_4_Line, 46);
    mapper->addMapping(ui->avatarLabel, 47);
    mapper->addMapping(ui->menuLabel, 48);
    mapper->addMapping(ui->bodyLabel, 51);

    groupModel = new BaseComboModel("name", "groups", this, Table, "");
    ui->groupAreaListView->setModel(groupModel);
    ui->groupAreaListView->setRowHidden(0, true);
    ui->groupAreaListView->setSelectionMode(QAbstractItemView::MultiSelection);

    docModel = new BaseComboModel("group_name", "document_group", this, Table, "");
    ui->docGroupListView->setModel(docModel);
    ui->docGroupListView->setRowHidden(0, true);
    ui->docGroupListView->setSelectionMode(QAbstractItemView::MultiSelection);

    // Init comboBox models with data
    accountModel = new BaseComboModel("acc_type", "account_table", this, Table, "account_type");
    tenantModel = new BaseComboModel("tenant_code || ': ' || name", "tenant", this, Table, "tenant_code");
    userModel = new BaseComboModel("user_type || ' - '", "security_filters", this, Table, "users_type");
    currencyModel = new BaseComboModel("currency_format", "currency_table", this, Table, "currency");
    currencyTypeModel = new BaseComboModel("curr_type", "currency_type_table", this, Table, "currency_type");
    timezoneModel = new BaseComboModel("timezone_name", "timezone_table", this, Table, "timezone");
    timeFormatModel = new BaseComboModel("standard_format", "time_format_table", this, Table, "time_format");
    dateModel = new BaseComboModel("date_format", "date_table", this, Table, "date");

    bntModel = new BaseComboModel("style", "button_style_table", this, Table, "button_style");
    menuModel = new BaseComboModel("m_type", "menu_type_table", this, Table, "menu_type");
    borderModel = new BaseComboModel("size", "border_size_table", this, Table, "border_size");
    headerBorderModel = new BaseComboModel("size", "border_size_table", this, Table, "header_border_size");

    // Add comboBoxes and their models to QLists
    combo = {ui->accountTypeBox, ui->tenantCodeBox, ui->userTypeBox, ui->curFormatBox, ui->curTypeBox, ui->timeZoneBox,
             ui->timeFormatBox, ui->dateFormatBox, ui->btnStyleBox, ui->btnFormatBox, ui->borderSizeBox, ui->hborderBox};
    cbModel = {accountModel, tenantModel, userModel, currencyModel, currencyTypeModel, timezoneModel, timeFormatModel,
               dateModel, bntModel, menuModel, borderModel, headerBorderModel};

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

        QString str = QString("UPDATE %1 SET active_account = '%2' WHERE id = %3").arg(Table).arg(value).arg(id);
        query.exec(str);

        // Write password
        if (!isEdit || !ui->passwordLine->text().isEmpty()) {
            QString str = QString("UPDATE %1 SET password = '%2' WHERE id = %3").arg(Table).arg(ui->passwordLine->text()).arg(id);
            query.exec(str);
        }

        // Save data from listViews
        auto saveListData = [&id](QModelIndexList list, QString table, QString column)
        {
            for (QModelIndex index : list) {
                int itemId = index.data(Qt::UserRole).toInt();
                QString str = QString("INSERT INTO %1 (user_id, %2) VALUES (%3, %4)").arg(table).arg(column).arg(id).arg(itemId);
                QSqlQuery query;
                query.exec(str);
            }
        };
        str = QString("DELETE FROM users_in_groups WHERE user_id = %1").arg(id);
        query.exec(str);
        saveListData(ui->groupAreaListView->selectionModel()->selectedIndexes(), "users_in_groups", "group_id");
        str = QString("DELETE FROM users_in_doc WHERE user_id = %1").arg(id);
        query.exec(str);
        saveListData(ui->docGroupListView->selectionModel()->selectedIndexes(), "users_in_doc", "doc_group_id");

        // Save images
        auto saveImage = [this, &id](QLabel *imageLabel, QString column) {
            QPixmap pix = QPixmap(*imageLabel->pixmap());
            QByteArray array;
            QBuffer buffer(&array);
            buffer.open(QIODevice::WriteOnly);
            pix.save(&buffer, "PNG");
            QVariant data = array;
            QSqlQuery query;
            query.prepare( "UPDATE " + Table + " SET " + column + " = ? WHERE id = ?" );
            query.addBindValue(data.toByteArray());
            query.addBindValue(id);
            query.exec();
        };

        if (avatarChanged) {
            saveImage(ui->avatarImgLabel, "avatar_image");
        }
        if (menuImgChanged) {
            saveImage(ui->menuImgLabel, "menu_image");
        }
        if (bodyImgChanged) {
            saveImage(ui->bodyImgLabel, "body_image");
        }
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
        ui->avatarLabel->setText(QFileInfo(fName).fileName());
        avatarChanged = true;   // Write new image into database
        QPixmap pix = QPixmap(fName);
        ui->avatarImgLabel->setPixmap(pix.scaled(400, 100, Qt::KeepAspectRatio));
    }
    else if (button == ui->bodyImgButton) {
        ui->bodyLabel->setText(QFileInfo(fName).fileName());
        bodyImgChanged = true;
        QPixmap pix = QPixmap(fName);
        ui->bodyImgLabel->setPixmap(pix.scaled(400, 100, Qt::KeepAspectRatio));
    }
    else {
        ui->menuLabel->setText(QFileInfo(fName).fileName());
        menuImgChanged = true;
        ui->menuLabel->setText(QFileInfo(fName).fileName());
        QPixmap pix = QPixmap(fName);
        ui->menuImgLabel->setPixmap(pix.scaled(400, 100, Qt::KeepAspectRatio));
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

    // Select data in listViews
    auto loadListData = [&id](QListView *view, QString table, QString column) {
        QString str = QString("SELECT %1 FROM %2 WHERE user_id = %3").arg(column).arg(table).arg(id);
        QSqlQuery query;
        query.exec(str);
        QList<int> list;
        while (query.next()) {
            list.append(query.value(0).toInt());
        }
        for (int i = 0; i < view->model()->rowCount(); i++) {
            QModelIndex index = view->model()->index(i, 0);
            for (int value : list) {
                if (view->model()->data(index, Qt::UserRole).toInt() == value) {
                    view->selectionModel()->select(index, QItemSelectionModel::Select);
                }
            }
        }
    };
    loadListData(ui->groupAreaListView, "users_in_groups", "group_id");
    loadListData(ui->docGroupListView, "users_in_doc", "doc_group_id");

    // Image names
    QString str = QString("SELECT avatar_text, menu_image_text, body_image_text FROM %1 WHERE id = %2").arg(Table).arg(id);
    query.exec(str);
    query.next();
    ui->avatarLabel->setText(query.value(0).toString());
    ui->menuLabel->setText(query.value(1).toString());
    ui->bodyLabel->setText(query.value(2).toString());

    // Images
    str = QString("SELECT avatar_image, menu_image, body_image FROM %1 WHERE id = %2").arg(Table).arg(id);
    query.exec(str);
    query.next();
    QPixmap img = QPixmap();
    img.loadFromData(query.value(0).toByteArray());
    ui->avatarImgLabel->setPixmap(img.scaled(400, 100, Qt::KeepAspectRatio));
    img.loadFromData(query.value(1).toByteArray());
    ui->menuImgLabel->setPixmap(img.scaled(400, 100, Qt::KeepAspectRatio));
    img.loadFromData(query.value(2).toByteArray());
    ui->bodyImgLabel->setPixmap(img.scaled(400, 100, Qt::KeepAspectRatio));

    ui->colorBackLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorBackLine->text() + ";} ");
    ui->colorMenuTextLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorMenuTextLine->text() + ";} ");
    ui->colorHighlightLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorHighlightLine->text() + ";} ");
    ui->colorBorderLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorBorderLine->text() + ";} ");
    ui->colorBodyBackLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorBodyBackLine->text() + ";} ");
    ui->colorLinkLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorLinkLine->text() + ";} ");
    ui->colorBodyTextLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorBodyTextLine->text() + ";} ");
    ui->colorBodyInfoLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorBodyInfoLine->text() + ";} ");
    ui->colorSectionLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorSectionLine->text() + ";} ");
    ui->colorSectionHeaderLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorSectionHeaderLine->text() + ";} ");
    ui->colorSectionBackLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorSectionBackLine->text() + ";} ");
    ui->colorHeaderLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorHeaderLine->text() + ";} ");
    ui->colorHBorderLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorHBorderLine->text() + ";} ");
    ui->colorSearchLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorSearchLine->text() + ";} ");
    ui->colorSelectedSearchLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorSelectedSearchLine->text() + ";} ");
    ui->colorFieldLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorFieldLine->text() + ";} ");
    ui->colorFieldSelectedLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorFieldSelectedLine->text() + ";} ");
    ui->colorTabLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorTabLine->text() + ";} ");
    ui->colorTabUnselectedLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorTabUnselectedLine->text() + ";} ");
    ui->colorMessageLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorMessageLine->text() + ";} ");
    ui->colorMessageBackLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorMessageBackLine->text() + ";} ");
    ui->colorChart_1_Line->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorChart_1_Line->text() + ";} ");
    ui->colorChart_2_Line->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorChart_2_Line->text() + ";} ");
    ui->colorChart_3_Line->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorChart_3_Line->text() + ";} ");
    ui->colorChart_4_Line->setStyleSheet("ClickeLineEdit { background-color: " + ui->colorChart_4_Line->text() + ";} ");
}

void CreateUserForm::checkPasswordLength(const QString &arg1)
{
    // Check password length

    int length = ui->passwordLine->text().length();

    if (length < 5 && !ui->passwordLengthBox->isChecked()) {
        ui->passwordLine->setStyleSheet("QLineEdit { color: red; }");
    }
    else {
        ui->passwordLine->setStyleSheet("QLineEdit { color: black; }");
    }
}
