#include "createtenantform.h"
#include "ui_createtenantform.h"

#include <QSqlRecord>

CreateTenantForm::CreateTenantForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateTenantForm)
{
    ui->setupUi(this);

    initData(Table);

    // View data in lineEdit with mapper
    mapper->addMapping(ui->tenantCodeSBox, 1);
    mapper->addMapping(ui->tenantNameLine, 2);
    mapper->addMapping(ui->emailLine, 3);
    mapper->addMapping(ui->phoneLine, 4);
    mapper->addMapping(ui->expTimeLine, 7);
    mapper->addMapping(ui->contactLine, 8);
    mapper->addMapping(ui->address_1_Line, 11);
    mapper->addMapping(ui->address_2_Line, 12);
    mapper->addMapping(ui->address_3_Line, 13);
    mapper->addMapping(ui->postalCodeLine, 15);
    mapper->addMapping(ui->postalExtendsLine, 16);
    mapper->addMapping(ui->commentsEdit, 17);
    mapper->addMapping(ui->emailServerLine, 24);
    mapper->addMapping(ui->emailAccountLine, 25);
    mapper->addMapping(ui->emailpasswLine, 26);
    mapper->addMapping(ui->twilioSidLine, 27);
    mapper->addMapping(ui->twilioTokenLine, 28);
    mapper->addMapping(ui->twPhoneLine, 29);
    mapper->addMapping(ui->menuBackColorLine, 33);
    mapper->addMapping(ui->menuTextColorLine, 34);
    mapper->addMapping(ui->selectionColorLine, 35);
    mapper->addMapping(ui->borderColorLine, 36);
    mapper->addMapping(ui->backColorLine, 37);
    mapper->addMapping(ui->linkColorLine, 38);
    mapper->addMapping(ui->textColorLine, 39);
    mapper->addMapping(ui->infoColorLine, 40);
    mapper->addMapping(ui->sectHeaderColorLine, 41);
    mapper->addMapping(ui->sectHeaderBackColorLine, 42);
    mapper->addMapping(ui->sectBackColorLine, 43);
    mapper->addMapping(ui->headColorLine, 45);
    mapper->addMapping(ui->headBordColorLine, 46);
    mapper->addMapping(ui->searchBordColorLine, 47);
    mapper->addMapping(ui->selectedSearchLine, 48);
    mapper->addMapping(ui->fieldsBordColorLine, 49);
    mapper->addMapping(ui->selectedFieldLine, 50);
    mapper->addMapping(ui->tabSelectColorLine, 51);
    mapper->addMapping(ui->tabUnselectColorLine, 52);
    mapper->addMapping(ui->msgColorLine, 53);
    mapper->addMapping(ui->msgBackLine, 54);
    mapper->addMapping(ui->fChatColorLine, 55);
    mapper->addMapping(ui->sChatColorLine, 56);
    mapper->addMapping(ui->thChatColorLine, 57);
    mapper->addMapping(ui->fourChatColorLine, 58);

    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();

    // Init comboBox models with data
    countryCModel = new BaseComboModel("country_name", "location_country", this, Table, "country", "location_country");
    cityCModel = new BaseComboModel("city_name", "location_city", this, Table, "city", "location_city");
    stateCModel = new BaseComboModel("state_name", "location_state", this, Table, "state", "location_state");
    langCModel = new BaseComboModel("language_name", "language_table", this, Table, "language", "language_table");
    currencyModel = new BaseComboModel("currency_format", "currency_table", this, Table, "currency", "currency_table");
    currencyTypeModel = new BaseComboModel("curr_type", "currency_type_table", this, Table, "currency_type", "currency_type_table");
    timezoneModel = new BaseComboModel("timezone_name", "timezone_table", this, Table, "timezone", "timezone_table");
    timeFormatModel = new BaseComboModel("standard_format", "time_format_table", this, Table, "time_format", "time_format_table");
    dateModel = new BaseComboModel("date_format", "date_table", this, Table, "date", "date_table");
    bntModel = new BaseComboModel("style", "button_style_table", this, Table, "button_style", "button_style_table");
    menuModel = new BaseComboModel("m_type", "menu_type_table", this, Table, "menu_type", "menu_type_table");
    borderModel = new BaseComboModel("size", "border_size_table", this, Table, "border_size", "border_size_table");
    headerLogoModel = new BaseComboModel("entry_name || ': ' || list_name", "logo WHERE type = 'LOGO_HEADER'", this, Table, "header_logo", "logo");
    mainLogoModel = new BaseComboModel("entry_name || ': ' || list_name", "logo WHERE type = 'LOGO_MAIN'", this, Table, "main_logo", "logo");
    headerBorderModel = new BaseComboModel("size", "border_size_table", this, Table, "header_border_size", "border_size_table");

    // Add comboBoxes and their models to QLists
    combo = {ui->countryBox, ui->cityBox, ui->regionBox, ui->languageBox, ui->currencyBox, ui->currencyTypeBox,
             ui->timezoneBox, ui->timeFormatBox, ui->dateBox, ui->buttonsStyleBox, ui->menuTypeBox, ui->borderSizeBox,
             ui->headerBox, ui->mainBox, ui->headBorderSizeBox};
    cbModel = {countryCModel, cityCModel, stateCModel, langCModel, currencyModel, currencyTypeModel, timezoneModel,
               timeFormatModel, dateModel, bntModel, menuModel, borderModel, headerLogoModel, mainLogoModel, headerBorderModel};

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateTenantForm::submitChanges);
}

CreateTenantForm::~CreateTenantForm()
{
    delete ui;
}

void CreateTenantForm::submitChanges()
{
    // Save changes to database

    mapper->submit();
    model->submitAll();

    int id = -1;
    if (isEdit) {
        id = model->record(mapper->currentIndex()).value("id").toInt();
    }

    // Save data from comboBoxes to database
    for (int i = 0; i < cbModel.count(); i++) {
        cbModel.at(i)->saveToDB(cbModel.at(i)->getId(combo.at(i)->currentText()), id);
    }

    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateTenantForm::setRowIndex(int rowIndex, int id)
{
    // User chose to edit data from the table
    BaseForm::setRowIndex(rowIndex, id);

    // Init comboBoxes with data from database
    auto initComboBox = [&id](QComboBox *box, BaseComboModel *comboModel)
    {
        box->setModel(comboModel);
        box->setCurrentIndex(comboModel->getIndex(id));
    };

    for (int i = 0; i < cbModel.count(); i++) {
        initComboBox(combo.at(i), cbModel.at(i));
    }
/*
    ui->menuBackColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->menuBackColorLine->text() + ";} ");
    ui->menuTextColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->menuTextColorLine->text() + ";} ");
    ui->selectionColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->selectionColorLine->text() + ";} ");
    ui->borderColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->borderColorLine->text() + ";} ");
    ui->backColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->backColorLine->text() + ";} ");
    ui->linkColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->linkColorLine->text() + ";} ");
    ui->textColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->textColorLine->text() + ";} ");
    ui->infoColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->infoColorLine->text() + ";} ");
    ui->sectHeaderColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->sectHeaderColorLine->text() + ";} ");
    ui->sectHeaderBackColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->sectHeaderBackColorLine->text() + ";} ");
    ui->sectBackColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->sectBackColorLine->text() + ";} ");
    ui->headColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->headColorLine->text() + ";} ");
    ui->headBordColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->headBordColorLine->text() + ";} ");
    ui->searchBordColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->searchBordColorLine->text() + ";} ");
    ui->selectedSearchLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->selectedSearchLine->text() + ";} ");
    ui->fieldsBordColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->fieldsBordColorLine->text() + ";} ");
    ui->selectedFieldLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->selectedFieldLine->text() + ";} ");
    ui->tabSelectColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->tabSelectColorLine->text() + ";} ");
    ui->tabUnselectColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->tabUnselectColorLine->text() + ";} ");
    ui->msgColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->msgColorLine->text() + ";} ");
    ui->msgBackLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->msgBackLine->text() + ";} ");
    ui->fChatColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->fChatColorLine->text() + ";} ");
    ui->sChatColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->sChatColorLine->text() + ";} ");
    ui->thChatColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->thChatColorLine->text() + ";} ");
    ui->fourChatColorLine->setStyleSheet("ClickeLineEdit { background-color: " + ui->fourChatColorLine->text() + ";} ");*/
}
