#include "tableform.h"
#include "ui_tableform.h"

#include "database.h"
#include <QScreen>
#include <QSqlQuery>

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
        if (this->table == "document_family") {
            auto id = mainModel->data(mainModel->index(ui->mainTableView->selectionModel()->selectedRows().at(0).row(), 0)); // id
            emit createData(this->viewType, ui->mainTableView->selectionModel()->selectedRows().at(0).row(), id.toInt());
        }
        else {
            emit createData(this->viewType, ui->mainTableView->selectionModel()->selectedRows().at(0).row());
        }
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

    //QStringList headers;

    switch (this->viewType) {
        case TableForm::groups:
            mainModel = new QSqlRelationalTableModel(this);
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

            /*QStringList headers;
            headers.append(QStringList() << trUtf8("id") << trUtf8("Group name") << trUtf8("Group description"));
            for(int i = 0, j = 0; i < mainModel->columnCount(); i++, j++) {
                mainModel->setHeaderData(i,Qt::Horizontal,headers[j]);
            }*/
            break;
        case TableForm::users:
            /*mainModel = new QSqlTableModel(this);
            this->table = "users";
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
            mainModel = new QSqlRelationalTableModel(this);
            this->table = "menus";
            mainModel->setTable(this->table);

            mainModel->setSort(0, Qt::AscendingOrder);
            mainModel->select();
            ui->mainTableView->setModel(mainModel);

            // Select Group name from groups table by id
            mainModel->setRelation(1, QSqlRelation("groups", "id", "name"));
            ui->mainTableView->setItemDelegate(new QSqlRelationalDelegate(ui->mainTableView));
            mainModel->select();

            // Hide columns
            ui->mainTableView->setColumnHidden(0, true);
            ui->mainTableView->setColumnHidden(3, true);

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
            }
            break;
        case TableForm::group_screens:
            mainModel = new QSqlRelationalTableModel(this);
            this->table = "group_screen";
            mainModel->setTable(this->table);

            mainModel->setSort(0, Qt::AscendingOrder);
            mainModel->select();
            ui->mainTableView->setModel(mainModel);

            // Select
            mainModel->setRelation(13, QSqlRelation("groups", "id", "name"));
            mainModel->setRelation(14, QSqlRelation("menus", "id", "text"));
            ui->mainTableView->setItemDelegate(new QSqlRelationalDelegate(ui->mainTableView));
            mainModel->select();

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                if (i < 1 || (i > 6 && i < 13))
                    ui->mainTableView->setColumnHidden(i, true);    // Hide columns
            };
            break;
        case TableForm::screens:
            mainModel = new QSqlRelationalTableModel(this);
            this->table = "screens";
            mainModel->setTable(this->table);

            mainModel->setSort(0, Qt::AscendingOrder);
            mainModel->select();
            ui->mainTableView->setModel(mainModel);

            // Select
            mainModel->setRelation(1, QSqlRelation("menus", "id", "text"));
            mainModel->setRelation(2, QSqlRelation("group_screen", "id", "s_text"));
            mainModel->setRelation(3, QSqlRelation("libraries", "id", "lib_name"));
            ui->mainTableView->setItemDelegate(new QSqlRelationalDelegate(ui->mainTableView));
            mainModel->select();

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                if (i < 1 || (i == 7))
                    ui->mainTableView->setColumnHidden(i, true);    // Hide columns
            };
            break;
        case TableForm::document_family:
            mainModel = new QSqlRelationalTableModel(this);
            this->table = "document_family";
            mainModel->setTable(this->table);

            mainModel->setSort(0, Qt::AscendingOrder);
            mainModel->select();
            ui->mainTableView->setModel(mainModel);

            ui->mainTableView->setColumnHidden(0, true);    // Hide column

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
            }
            break;
        case TableForm::document_groups:
            mainModel = new QSqlRelationalTableModel(this);
            this->table = "document_group";
            mainModel->setTable(this->table);

            mainModel->setSort(0, Qt::AscendingOrder);
            mainModel->select();
            ui->mainTableView->setModel(mainModel);

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                if (i < 1 || i > 2)
                    ui->mainTableView->setColumnHidden(i, true);    // Hide columns
            }
            break;
        case TableForm::lists:
            mainModel = new QSqlRelationalTableModel(this);
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
            mainModel = new QSqlRelationalTableModel(this);
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
            mainModel = new QSqlRelationalTableModel(this);
            this->table = "data_sources";
            mainModel->setTable(this->table);

            mainModel->setSort(0, Qt::AscendingOrder);
            mainModel->select();
            ui->mainTableView->setModel(mainModel);

            // Select
            mainModel->setRelation(4, QSqlRelation("function_type", "id", "func_type"));
            mainModel->setRelation(5, QSqlRelation("direction_type", "id", "direct_type"));
            ui->mainTableView->setItemDelegate(new QSqlRelationalDelegate(ui->mainTableView));
            mainModel->select();

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                if (i < 1 || i == 3 || i > 5)
                    ui->mainTableView->setColumnHidden(i, true);    // Hide columns
            }
            break;
        case TableForm::extension_functions:
            mainModel = new QSqlRelationalTableModel(this);
            this->table = "extension_functions";
            mainModel->setTable(this->table);

            mainModel->setSort(0, Qt::AscendingOrder);
            mainModel->select();
            ui->mainTableView->setModel(mainModel);

            // Select
            mainModel->setRelation(6, QSqlRelation("extension_type", "id", "type"));
            ui->mainTableView->setItemDelegate(new QSqlRelationalDelegate(ui->mainTableView));
            mainModel->select();

            // Hide columns
            ui->mainTableView->setColumnHidden(0, true);
            ui->mainTableView->setColumnHidden(3, true);

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
            }
            break;
        case TableForm::servers:
            mainModel = new QSqlRelationalTableModel(this);
            this->table = "servers";
            mainModel->setTable(this->table);

            mainModel->setSort(0, Qt::AscendingOrder);
            mainModel->select();
            ui->mainTableView->setModel(mainModel);

            // Hide columns
            ui->mainTableView->setColumnHidden(0, true);
            ui->mainTableView->setColumnHidden(4, true);

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
            }
            break;
        case TableForm::security_questions:
            mainModel = new QSqlRelationalTableModel(this);
            this->table = "security_question";
            mainModel->setTable(this->table);

            mainModel->setSort(0, Qt::AscendingOrder);
            mainModel->select();
            ui->mainTableView->setModel(mainModel);

            // Select question type from question table by id
            mainModel->setRelation(1, QSqlRelation("question", "id", "type"));
            ui->mainTableView->setItemDelegate(new QSqlRelationalDelegate(ui->mainTableView));
            mainModel->select();

            ui->mainTableView->setColumnHidden(0, true); // Hide column

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
            }
            break;
        case TableForm::custom_query:
            mainModel = new QSqlRelationalTableModel(this);
            this->table = "query";
            mainModel->setTable(this->table);

            mainModel->setSort(0, Qt::AscendingOrder);
            mainModel->select();
            ui->mainTableView->setModel(mainModel);

            // Hide columns
            ui->mainTableView->setColumnHidden(0, true);
            ui->mainTableView->setColumnHidden(2, true);
            ui->mainTableView->setColumnHidden(3, true);

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
            }
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

    QString searchStr = ui->searchParamBox->currentText();
    QString filterString = QString("%1 LIKE '%%2%'").arg(searchStr).arg(arg1);

    mainModel->setFilter(filterString);

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
