#include "tableform.h"
#include "ui_tableform.h"

#include "database.h"
#include <QScreen>

TableForm::TableForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableForm)
{
    ui->setupUi(this);

    ui->builderCreateButton->setVisible(false);     // Hide "Create with builder" button
    ui->builderUpdateButton->setVisible(false);     // Hide "Update with builder" button
    // Hide widgets for search
    ui->searchLine->setVisible(false);
    ui->searchParamBox->setVisible(false);

    connect(ui->searchButton, &QToolButton::clicked, this, &TableForm::showSearchWidgets);

    connect(ui->searchLine, &QLineEdit::textChanged, this, &TableForm::searchInDB); // Interactive search in database

    connect(ui->createButton, &QToolButton::clicked, this, [this] {
        emit createData(this->viewType); // Create new data
    });

    connect(ui->editButton, &QToolButton::clicked, this, [this] {
        // Edit existing data, second parameter - selected row in the table
        emit createData(this->viewType, ui->mainTableView->selectionModel()->selectedRows().at(0).row());
    });

    connect(ui->deleteButton, &QToolButton::clicked, this, &TableForm::deleteDatafromDB); // A row was selected in the table
}

TableForm::~TableForm()
{
    delete ui;
}

void TableForm::loadDataFromDB()
{
    // Load data

    QStringList headers;

    switch (this->viewType) {
        case TableForm::groups:
            mainModel = new QSqlTableModel(this);
            this->table = "groups";
            mainModel->setTable(this->table);

            mainModel->setSort(0, Qt::AscendingOrder);
            mainModel->select();
            ui->mainTableView->setModel(mainModel);
            ui->mainTableView->setColumnHidden(0, true); // Hide

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
            }
            break;
        case TableForm::users:
            /*mainModel = new QSqlTableModel(this);
            this->table = "user";
            mainModel->setTable(this->table);

            mainModel->setSort(0, Qt::AscendingOrder);
            mainModel->select();
            ui->mainTableView->setModel(mainModel);
            ui->mainTableView->setColumnHidden(0, true);    // Hide
            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
            }*/
            break;
        case TableForm::tenant:
            break;
        case TableForm::logo:
            break;
        case TableForm::security_filters:
            break;
        case TableForm::menu:
            break;
        case TableForm::group_screens:
            break;
        case TableForm::screens:
            break;
        case TableForm::document_family:
            break;
        case TableForm::document_groups:
            break;
        case TableForm::lists:
            mainModel = new QSqlTableModel(this);
            this->table = "lists";
            mainModel->setTable(this->table);

            mainModel->setSort(0, Qt::AscendingOrder);
            mainModel->select();
            ui->mainTableView->setModel(mainModel);

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                if (i < 1 || i > 3)
                    ui->mainTableView->setColumnHidden(i, true);    // Hide columns
            }
            break;
        case TableForm::templates:
            mainModel = new QSqlTableModel(this);
            this->table = "templates";
            mainModel->setTable(this->table);

            mainModel->setSort(0, Qt::AscendingOrder);
            mainModel->select();
            ui->mainTableView->setModel(mainModel);

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                if (i < 1 || i > 5)
                    ui->mainTableView->setColumnHidden(i, true);    // Hide columns
            }
            break;
        case TableForm::custom_data_sources:
            break;
        case TableForm::extension_functions:
            mainModel = new QSqlTableModel(this);
            this->table = "extension_functions";
            mainModel->setTable(this->table);

            mainModel->setSort(0, Qt::AscendingOrder);
            mainModel->select();
            ui->mainTableView->setModel(mainModel);

            ui->mainTableView->setColumnHidden(0, true);    // Hide columns
            ui->mainTableView->setColumnHidden(3, true);    // Hide columns

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
            }
            break;
        case TableForm::servers:
            break;
        case TableForm::security_questions:
            break;
        case TableForm::custom_query:
            break;
        default:
            break;
    }
    ui->mainTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->mainTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->mainTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TableForm::showSearchWidgets()
{
    // Show widgets for providing search
    ui->searchLine->setVisible(!ui->searchLine->isVisible());
    ui->searchParamBox->setVisible(!ui->searchParamBox->isVisible());
    ui->searchLine->clear();
    ui->searchParamBox->clear();

    // Get column header names from table
    QSqlQuery query;
    if (query.exec( "SELECT column_name FROM INFORMATION_SCHEMA.COLUMNS WHERE table_name = '" +
                    this->table + "' AND NOT column_name LIKE '%id%'" )) {
        while (query.next()) {
            ui->searchParamBox->addItem(query.value(0).toString());
        }
    }
}

void TableForm::searchInDB(const QString &arg1)
{
    // Interactive search in current database table

    // Set parameters for search

    /*
     *
     *
     * Is'n work properly
     *
     *
     */


    QString searchStr = ui->searchParamBox->currentText();

    qDebug() << searchStr;
    qDebug() << arg1;

    if ((searchStr.isEmpty()) || (arg1.isEmpty())) {
        mainModel->setFilter("'%' LIKE '%'");
    }
    else {
        mainModel->setFilter("'" + searchStr + "' LIKE '%" + arg1 + "%'");
    }

    mainModel->select();
}

void TableForm::setViewType(Type type)
{
    this->viewType = type;

    if (this->viewType == Type::screens || this->viewType == Type::custom_query) {
        ui->builderCreateButton->setVisible(true);  // Show "Create with builder" button
        ui->builderUpdateButton->setVisible(true);  // Show "Update with builder" button

        connect(ui->builderCreateButton, &QToolButton::clicked, this, [this] {
            emit createDataWithBuilder(this->viewType);  // Create new data with builder
        });
    }

    loadDataFromDB();
}

void TableForm::deleteDatafromDB()
{
    // Delete current data from database
    int row = ui->mainTableView->selectionModel()->selectedRows().at(0).row();
    mainModel->removeRow(row);
    mainModel->submitAll();
    mainModel->select();
    ui->mainTableView->selectRow(row);
}
