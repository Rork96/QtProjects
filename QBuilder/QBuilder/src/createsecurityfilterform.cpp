#include "createsecurityfilterform.h"
#include "ui_createsecurityfilterform.h"

#include <QSqlRecord>
#include <QSqlQuery>

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

    questionModel = new BaseComboModel("type", "question", this, Table, "");
    ui->questionListView->setModel(questionModel);
    ui->questionListView->setRowHidden(0, true);
    ui->questionListView->setSelectionMode(QAbstractItemView::MultiSelection);

    authModel = new BaseComboModel("auth_type", "authorization_table", this, Table, "");
    ui->authTypeListView->setModel(authModel);
    ui->authTypeListView->setRowHidden(0, true);
    ui->authTypeListView->setSelectionMode(QAbstractItemView::MultiSelection);

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

    // Save data from listViews
    auto saveListData = [&id](QModelIndexList list, QString table, QString column)
    {
        for (QModelIndex index : list) {
            int itemId = index.data(Qt::UserRole).toInt();
            QString str = QString("INSERT INTO %1 (filter_id, %2) VALUES (%3, %4)").arg(table).arg(column).arg(id).arg(itemId);
            QSqlQuery query;
            query.exec(str);
        }
    };
    QString str = QString("DELETE FROM filters_in_authorization WHERE filter_id = %1").arg(id);
    QSqlQuery query;
    query.exec(str);
    saveListData(ui->authTypeListView->selectionModel()->selectedIndexes(), "filters_in_authorization", "auth_id");
    str = QString("DELETE FROM filters_in_question WHERE filter_id = %1").arg(id);
    query.exec(str);
    saveListData(ui->questionListView->selectionModel()->selectedIndexes(), "filters_in_question", "quest_id");

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

    // Select data in listViews
    auto loadListData = [&id](QListView *view, QString table, QString column) {
        QString str = QString("SELECT %1 FROM %2 WHERE filter_id = %3").arg(column).arg(table).arg(id);
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
    loadListData(ui->authTypeListView, "filters_in_authorization", "auth_id");
    loadListData(ui->questionListView, "filters_in_question", "quest_id");
}
