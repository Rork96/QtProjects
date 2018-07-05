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
        auto id = mainModel->data(mainModel->index(ui->mainTableView->selectionModel()->selectedRows().at(0).row(), 0)); // id
        emit createData(this->viewType, ui->mainTableView->selectionModel()->selectedRows().at(0).row(), id.toInt());
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

    auto initTable = [this](const QString& tableName)
    {
        this->table = tableName;
        mainModel = new QSqlRelationalTableModel(this);
        mainModel->setTable(this->table);
        mainModel->setSort(0, Qt::AscendingOrder);
        mainModel->select();
        ui->mainTableView->setModel(mainModel);
        ui->mainTableView->setColumnHidden(0, true); // Hide
    };

    QStringList headers;

    switch (this->viewType) {
        case TableForm::groups:
            initTable("groups");

            headers << trUtf8("id") << trUtf8("Group name") << trUtf8("Group description");

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
            }
            break;
        case TableForm::users:
            /*initTable("users");

            headers << trUtf8("id") << trUtf8("User name") << trUtf8("Group area") << trUtf8("Email")
                    << trUtf8("Account type") << trUtf8("Active account") << trUtf8("Account name");

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
            }*/
            break;
        case TableForm::tenant:
            initTable("tenant");

            // Select
            mainModel->setRelation(5, QSqlRelation("location_country", "id", "country_name"));
            mainModel->setRelation(6, QSqlRelation("location_city", "id", "city_name"));
            ui->mainTableView->setItemDelegate(new QSqlRelationalDelegate(ui->mainTableView));
            mainModel->select();

            headers << trUtf8("id") << trUtf8("Tenant code") << trUtf8("Name") << trUtf8("Email") << trUtf8("Phone")
                    << trUtf8("Country") << trUtf8("City");

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                if (i <= 6) mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
                if (i > 6)
                    ui->mainTableView->setColumnHidden(i, true);    // Hide columns
            }
            break;
        case TableForm::logo:
            initTable("logo");

            ui->mainTableView->setColumnHidden(5, true); // Hide

            headers << trUtf8("id") << trUtf8("List name") << trUtf8("Entry name") << trUtf8("Description")
                    << trUtf8("Type") << trUtf8("");

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
            }
            break;
        case TableForm::security_filters:
            break;
        case TableForm::menu:
            initTable("menus");

            mainModel->setRelation(1, QSqlRelation("groups", "id", "name"));
            mainModel->select();

            ui->mainTableView->setColumnHidden(3, true); // Hide

            headers << trUtf8("id") << trUtf8("Group name") << trUtf8("Description") << trUtf8("") << trUtf8("Menu name")
                    << trUtf8("Weight");

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
            }
            break;
        case TableForm::group_screens:
            initTable("group_screen");

            // Select
            mainModel->setRelation(13, QSqlRelation("groups", "id", "name"));
            mainModel->setRelation(14, QSqlRelation("menus", "id", "text"));
            ui->mainTableView->setItemDelegate(new QSqlRelationalDelegate(ui->mainTableView));
            mainModel->select();

            headers << trUtf8("id") << trUtf8("Add") << trUtf8("Delete") << trUtf8("Edit") << trUtf8("Copy")
                    << trUtf8("Inquire") << trUtf8("Execute") << trUtf8("") << trUtf8("") << trUtf8("") << trUtf8("")
                    << trUtf8("") << trUtf8("") << trUtf8("Group name") << trUtf8("Menu name") << trUtf8("Screen text")
                    << trUtf8("Weight");

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
                if (i > 6 && i < 13)
                    ui->mainTableView->setColumnHidden(i, true);    // Hide columns
            };
            break;
        case TableForm::screens:
            initTable("screens");

            // Select
            mainModel->setRelation(1, QSqlRelation("menus", "id", "text"));
            mainModel->setRelation(2, QSqlRelation("group_screen", "id", "s_text"));
            mainModel->setRelation(3, QSqlRelation("libraries", "id", "lib_name"));
            ui->mainTableView->setItemDelegate(new QSqlRelationalDelegate(ui->mainTableView));
            mainModel->select();

            ui->mainTableView->setColumnHidden(7, true);    // Hide

            headers << trUtf8("id") << trUtf8("Menu name") << trUtf8("Screen name") << trUtf8("Library")
                    << trUtf8("Tab text") << trUtf8("Description") << trUtf8("Tab weight") << trUtf8("")
                    << trUtf8("Desctop") << trUtf8("Mobile") << trUtf8("Web");

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
            };
            break;
        case TableForm::document_family:
            initTable("document_family");

            headers << trUtf8("id") << trUtf8("Family Name") << trUtf8("Family Description");

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
            }
            break;
        case TableForm::document_groups:
            initTable("document_group");

            headers << trUtf8("id") << trUtf8("Group Name") << trUtf8("Group Description") << trUtf8("") << trUtf8("");

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
                if (i > 2)
                    ui->mainTableView->setColumnHidden(i, true);    // Hide columns
            }
            break;
        case TableForm::lists:
            initTable("lists");

            headers << trUtf8("id") << trUtf8("List name") << trUtf8("Description") << trUtf8("Entry name") << trUtf8("")
                    << trUtf8("") << trUtf8("") << trUtf8("");

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
                if (i > 3)
                    ui->mainTableView->setColumnHidden(i, true);    // Hide columns
            }
            break;
        case TableForm::templates:
            initTable("templates");

            headers << trUtf8("id") << trUtf8("Library name") << trUtf8("Function") << trUtf8("Table name")
                    << trUtf8("Table column") << trUtf8("Column type") << trUtf8("");

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
                if (i > 5)
                    ui->mainTableView->setColumnHidden(i, true);    // Hide columns
            }
            break;
        case TableForm::custom_data_sources:
            initTable("data_sources");

            // Select
            mainModel->setRelation(4, QSqlRelation("function_type", "id", "func_type"));
            mainModel->setRelation(5, QSqlRelation("direction_type", "id", "direct_type"));
            ui->mainTableView->setItemDelegate(new QSqlRelationalDelegate(ui->mainTableView));
            mainModel->select();

            ui->mainTableView->setColumnHidden(3, true);    // Hide

            headers << trUtf8("id") << trUtf8("Name") << trUtf8("Function type") << trUtf8("")
                    << trUtf8("Table") << trUtf8("Direction type") << trUtf8("") << trUtf8("") << trUtf8("");

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
                if (i > 5)
                    ui->mainTableView->setColumnHidden(i, true);    // Hide columns
            }
            break;
        case TableForm::extension_functions:
            initTable("extension_functions");

            // Select
            mainModel->setRelation(6, QSqlRelation("extension_type", "id", "type"));
            ui->mainTableView->setItemDelegate(new QSqlRelationalDelegate(ui->mainTableView));
            mainModel->select();

            ui->mainTableView->setColumnHidden(3, true);    // Hide

            headers << trUtf8("id") << trUtf8("Data source library") << trUtf8("Data source function") << trUtf8("")
                    << trUtf8("Extension function") << trUtf8("Extension free memory function") << trUtf8("Extension type");

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
            }
            break;
        case TableForm::servers:
            initTable("servers");

            ui->mainTableView->setColumnHidden(4, true); // Hide

            headers << trUtf8("id") << trUtf8("IP Address") << trUtf8("Port") << trUtf8("Description") << trUtf8("");

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
            }
            break;
        case TableForm::security_questions:
            initTable("security_question");

            // Select question type from question table by id
            mainModel->setRelation(1, QSqlRelation("question", "id", "type"));
            ui->mainTableView->setItemDelegate(new QSqlRelationalDelegate(ui->mainTableView));
            mainModel->select();

            headers << trUtf8("id") << trUtf8("Question") << trUtf8("Answer") << trUtf8("");

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
            }
            break;
        case TableForm::custom_query:
            initTable("query");

            // Hide columns
            ui->mainTableView->setColumnHidden(2, true);
            ui->mainTableView->setColumnHidden(3, true);

            headers << trUtf8("id") << trUtf8("Query name") << trUtf8("") << trUtf8("") << trUtf8("Description");

            // Columns size
            for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
                ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
                mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
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
