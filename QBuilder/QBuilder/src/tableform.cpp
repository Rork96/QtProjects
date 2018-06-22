#include "tableform.h"
#include "ui_tableform.h"

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

    connect(ui->searchButton, &QToolButton::clicked, this, &TableForm::searchInDB); // Search

    connect(ui->createButton, &QToolButton::clicked, this, [this] {
        emit createData(this->viewType); // Create new data
    });

    connect(ui->deleteButton, &QToolButton::clicked, this, &TableForm::deleteDatafromDB); // Selected row in table
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
            mainModel->setTable("admin_groups");

            mainModel->setSort(0, Qt::AscendingOrder);
            mainModel->select();
            ui->mainTableView->setModel(mainModel);
            ui->mainTableView->setColumnHidden(0, true);
            ui->mainTableView->horizontalHeader()->setStretchLastSection(true);
            ui->mainTableView->setColumnWidth(1, static_cast<int>(QApplication::primaryScreen()->size().width() / 3));
            break;
        case TableForm::users:
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
            break;
        case TableForm::templates:
            break;
        case TableForm::custom_data_sources:
            break;
        case TableForm::extension_functions:
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

void TableForm::searchInDB()
{
    // Show widgets for search
    ui->searchLine->setVisible(!ui->searchLine->isVisible());
    ui->searchParamBox->setVisible(!ui->searchParamBox->isVisible());
    ui->searchLine->clear();
    ui->searchParamBox->clear();

    // Interactive search in current database table
}

void TableForm::setViewType(Type type)
{
    this->viewType = type;

    if (type == Type::screens || type == Type::custom_query) {
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
