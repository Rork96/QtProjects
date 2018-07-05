#include "createtenantform.h"
#include "ui_createtenantform.h"

#include <QPainter>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>

#include "basecombomodel.h"

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
    // 9 - header logo
    // 10 - main logo
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

    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();

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

    // Add comboboxes and their models to QLists
    combo = {ui->countryBox, ui->cityBox, ui->regionBox, ui->languageBox, ui->currencyBox, ui->currencyTypeBox,
             ui->timezoneBox, ui->timeFormatBox, ui->dateBox, ui->buttonsStyleBox, ui->menuTypeBox};
    cbModel = {countryCModel, cityCModel, stateCModel, langCModel, currencyModel, currencyTypeModel, timezoneModel,
               timeFormatModel, dateModel, bntModel, menuModel};

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateTenantForm::submitChanges);

    QList<QComboBox*> elements = {ui->backColorBox, ui->menuTextColorBox, ui->borderColorBox, ui->linkColorBox, ui->headBordColorBox,
                                 ui->headColorBox, ui->infoColorBox, ui->menuBackColorBox, ui->menuTextColorBox, ui->msgColorBox,
                                 ui->searchBordColorBox, ui->sectBackColorBox, ui->sectHeaderColorBox, ui->selectionColorBox,
                                 ui->tabSelectColorBox, ui->tabUnselectColorBox, ui->textColorBox, ui->sectHeaderBackBox,
                                 ui->selectedSearchBox, ui->fieldsBordColorBox, ui->selectedFieldBox, ui->msgBackBox, ui->fChatColorBox,
                                 ui->sChatColorBox, ui->thChatColorBox, ui->fourChatColorBox};

    initComboBox(elements);   // Init comboboxes with colors
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
        cbModel.at(i)->saveToDB(combo.at(i)->currentIndex(), id);
    }

    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateTenantForm::initComboBox(QList<QComboBox*> elements)
{
    // Init comboboxes with colors
    foreach (QComboBox *element, elements) {
        QStringList colorNames;
        colorNames = QColor::colorNames();

        element ->setFocusPolicy(Qt::NoFocus);
        int size = element ->style()->pixelMetric(QStyle::PM_SmallIconSize);
        QPixmap pixmap(size, size-5);

        int con = 0;
        foreach (const QString &colorName, colorNames) {
            element->addItem(colorName);                                // Color name
            pixmap.fill(QColor(colorName));

            QRect rBorder(0, 0, size-1, size-6);
            QPainter p(&pixmap);
            QPen pen(Qt::lightGray, 1, Qt::SolidLine);
            p.setPen(pen);
            p.drawRect(rBorder);

            element->setItemData(con, pixmap, Qt::DecorationRole);      // Color icon
            con = con + 1;
        }
    }
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
}
