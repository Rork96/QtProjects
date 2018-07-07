#include "createsecurityfilterform.h"
#include "ui_createsecurityfilterform.h"

#include <QSqlRecord>

#include <QDebug>

CreateSecurityFilterForm::CreateSecurityFilterForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateSecurityFilterForm)
{
    ui->setupUi(this);

    initData(Table);

    mapper->addMapping(ui->userTypeLine, 3);
    mapper->addMapping(ui->descriptionEdit, 4);
    mapper->addMapping(ui->filter_1_Line, 5);
    mapper->addMapping(ui->filter_1_SpinBox, 6);
    mapper->addMapping(ui->filter_2_Line, 7);
    mapper->addMapping(ui->filter_2_SpinBox, 8);
    mapper->addMapping(ui->changePasswCheckBox, 9);
    mapper->addMapping(ui->changeSetCheckBox, 10);
    mapper->addMapping(ui->selfRegCheckBox, 11);
    mapper->addMapping(ui->ldapCheckBox, 12);
    mapper->addMapping(ui->chatCheckBox, 13);
    // 14
    // 15
    // 16


    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();

    // Init comboBox models with data
    tenantCModel = new BaseComboModel("tenant_code || ': ' || name", "tenant", this, Table, "tenant");
    //acTypeCModel = new BaseComboModel("entry_name || ': ' || list_name", "location_city", this, Table, "city");

    // Add comboBoxes and their models to QLists
    combo = {ui->tenantBox /*, ui->accountTypeBox*/};
    cbModel = {tenantCModel /*, acTypeCModel*/};

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateSecurityFilterForm::submitChanges);
}

CreateSecurityFilterForm::~CreateSecurityFilterForm()
{
    delete ui;
}

void CreateSecurityFilterForm::submitChanges()
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
        cbModel.at(i)->saveToDB(combo.at(i)->itemData(combo.at(i)->currentIndex(), Qt::UserRole).toInt(), id);
    }

    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateSecurityFilterForm::setRowIndex(int rowIndex, int id)
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
}
