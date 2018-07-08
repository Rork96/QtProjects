#include "createsecurityfilterform.h"
#include "ui_createsecurityfilterform.h"

#include <QSqlRecord>
#include <QSqlQuery>

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

    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();

    questionModel = new BaseComboModel("type", "question", this, Table, "secret_questions");
    ui->questionListView->setModel(questionModel);
    ui->questionListView->setRowHidden(0, true);

    authModel = new BaseComboModel("auth_type", "authorization_table", this, Table, "authorization_type");
    ui->authTypeListView->setModel(authModel);
    ui->authTypeListView->setRowHidden(0, true);

    // Init comboBox models with data
    tenantCModel = new BaseComboModel("tenant_code || ': ' || name", "tenant", this, Table, "tenant");
    acTypeCModel = new BaseComboModel("acc_type", "account_table", this, Table, "account_type");
    regSceenModel = new BaseComboModel("data_source_library", "extension_functions", this, Table, "registration_screen");

    // Add comboBoxes and their models to QLists
    combo = {ui->tenantBox, ui->accountTypeBox, ui->regScreenBox};
    cbModel = {tenantCModel, acTypeCModel, regSceenModel};

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

    auto saveListData = [&id](BaseComboModel *model, QListView *view, QString table, QString column)
    {
        qDebug() << table;

        QModelIndex index = view->currentIndex();
        qDebug() << index;
        QString itemText = index.data(Qt::DisplayRole).toString();
        qDebug() << itemText;

        QString str = QString("SELECT id FROM " + table + " WHERE " + column + " = '%1'").arg(itemText);
        qDebug() << str;
        QSqlQuery query;
        query.exec(str);
        query.next(); // Query doesn't work properly in second time
        qDebug() << query.value(0).toInt();
        qDebug() << query.value(1).toInt();
        model->saveToDB(query.value(0).toInt(), id);
    };

/*
    // ListView
    QModelIndex index = ui->questionListView->currentIndex();
    QString itemText = index.data(Qt::DisplayRole).toString();
    QSqlQuery query;
    QString str = QString("SELECT id FROM " + QuestionTable + " WHERE type = '%1'").arg(itemText);
    query.exec(str);
    query.next();
    questionModel->saveToDB(query.value(0).toInt(), id);
*/

    //saveListData(questionModel, ui->questionListView, QuestionTable, "type");
    //saveListData(authModel, ui->authTypeListView, AuthTable, "auth_type");

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

    //ui->questionListView->setCurrentIndex();
    // ui->questionListView, questionModel
    // ui->authTypeListView, authModel
}
