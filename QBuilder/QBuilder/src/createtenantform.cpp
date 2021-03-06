#include "createtenantform.h"
#include "ui_createtenantform.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>

CreateTenantForm::CreateTenantForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateTenantForm)
{
    ui->setupUi(this);

    ui->submitButton->setEnabled(false) ; // Name, city, contact, email, address 1 and country cannot be blank

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
    /* 33 - 43, 45 - 58: ClickeLineEdit for colors */

    // Init comboBox models with data
    countryCModel = new BaseComboModel("country_name", "location_country", this, Table, "country");
    cityCModel = new BaseComboModel("city_name", "location_city", this, Table, "city");
    stateCModel = new BaseComboModel("state_name", "location_state", this, Table, "state");
    langCModel = new BaseComboModel("language_name", "language_table", this, Table, "language");
    currencyModel = new BaseComboModel("currency_format", "currency_table", this, Table, "currency");
    currencyTypeModel = new BaseComboModel("curr_type", "currency_type_table", this, Table, "currency_type");
    timezoneModel = new BaseComboModel("timezone_name", "timezone_table", this, Table, "timezone");
    timeFormatModel = new BaseComboModel("standard_format", "time_format_table", this, Table, "time_format");
    dateModel = new BaseComboModel("date_format", "date_table", this, Table, "date");
    bntModel = new BaseComboModel("style", "button_style_table", this, Table, "button_style");
    menuModel = new BaseComboModel("m_type", "menu_type_table", this, Table, "menu_type");
    borderModel = new BaseComboModel("size", "border_size_table", this, Table, "border_size");
    headerLogoModel = new BaseComboModel("entry_name || ': ' || list_name", "logo WHERE type = 'LOGO_HEADER'", this, Table, "header_logo");
    mainLogoModel = new BaseComboModel("entry_name || ': ' || list_name", "logo WHERE type = 'LOGO_MAIN'", this, Table, "main_logo");
    headerBorderModel = new BaseComboModel("size", "border_size_table", this, Table, "header_border_size");

    // Add comboBoxes and their models to QLists
    combo = {ui->countryBox, ui->cityBox, ui->regionBox, ui->languageBox, ui->currencyBox, ui->currencyTypeBox,
             ui->timezoneBox, ui->timeFormatBox, ui->dateBox, ui->buttonsStyleBox, ui->menuTypeBox, ui->borderSizeBox,
             ui->headerBox, ui->mainBox, ui->headBorderSizeBox};
    cbModel = {countryCModel, cityCModel, stateCModel, langCModel, currencyModel, currencyTypeModel, timezoneModel,
               timeFormatModel, dateModel, bntModel, menuModel, borderModel, headerLogoModel, mainLogoModel, headerBorderModel};

    // Color lineEdits
    colorLine = {ui->menuBackColorLine, ui->menuTextColorLine, ui->selectionColorLine, ui->borderColorLine, ui->backColorLine,
                 ui->linkColorLine, ui->textColorLine, ui->infoColorLine, ui->sectHeaderColorLine, ui->sectHeaderBackColorLine,
                 ui->sectBackColorLine, ui->headColorLine, ui->headBordColorLine, ui->searchBordColorLine, ui->selectedSearchLine,
                 ui->fieldsBordColorLine, ui->selectedFieldLine, ui->tabSelectColorLine, ui->tabUnselectColorLine, ui->msgColorLine,
                 ui->msgBackLine, ui->fChatColorLine, ui->sChatColorLine, ui->thChatColorLine, ui->fourChatColorLine};

    /* 33 - 43, 45 - 58 */
    int i = 33;
    for (ClickeLineEdit *line : colorLine) {
        if (i != 44) mapper->addMapping(line, i++);
    }

    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateTenantForm::submitChanges);

    // Check Name, city, contact, email, address 1 and country
    connect(ui->tenantNameLine, &QLineEdit::textChanged, this, [this] {
        ui->submitButton->setEnabled(!ui->tenantNameLine->text().isEmpty() && ui->cityBox->currentIndex() > 0 &&
        ui->countryBox->currentIndex() > 0 && !ui->contactLine->text().isEmpty() && !ui->emailLine->text().isEmpty() &&
        !ui->address_1_Line->text().isEmpty());
    });
    connect(ui->cityBox, &QComboBox::currentTextChanged, ui->tenantNameLine, &QLineEdit::textChanged);
    connect(ui->countryBox, &QComboBox::currentTextChanged, ui->tenantNameLine, &QLineEdit::textChanged);
    connect(ui->contactLine, &QLineEdit::textChanged, ui->tenantNameLine, &QLineEdit::textChanged);
    connect(ui->emailLine, &QLineEdit::textChanged, ui->tenantNameLine, &QLineEdit::textChanged);
    connect(ui->address_1_Line, &QLineEdit::textChanged, ui->tenantNameLine, &QLineEdit::textChanged);
}

CreateTenantForm::~CreateTenantForm()
{
    delete ui;
}

void CreateTenantForm::submitChanges()
{
    // Save changes to database

    QSqlQuery query;
    QString str = QString("SELECT EXISTS (SELECT " + Record1 + ", " + Record2 + " FROM " + Table +
            " WHERE " + Record1 + " = %1 OR " + Record2 + " = '%2' AND id != %3 )").arg(ui->tenantCodeSBox->text().toInt()).
            arg(ui->tenantNameLine->text()).arg(model->data(model->index(mapper->currentIndex(), 0), Qt::DisplayRole).toInt());

    query.exec(str);
    query.next();

    // If exists
    if (query.value(0) != 0 && !isEdit) {
        QMessageBox::information(this, trUtf8("Error"), trUtf8("Tenant code or name is already exists"));
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
        box->setCurrentIndex(box->findText(comboModel->getTextValue(id)));
    };

    for (int i = 0; i < cbModel.count(); i++) {
        initComboBox(combo.at(i), cbModel.at(i));
    }

    // Colors
    for (ClickeLineEdit *line : colorLine) {
        line->setStyleSheet("ClickeLineEdit { background-color: " + line->text() + ";} ");
    }
}
