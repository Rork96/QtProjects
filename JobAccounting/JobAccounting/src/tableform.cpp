#include "tableform.h"
#include "ui_tableform.h"

#include "database.h"
#include <QScreen>
#include <QSqlQuery>

#include <QDebug>

TableForm::TableForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableForm)
{
    ui->setupUi(this);

    // Hide widgets for search
    ui->searchLine->setVisible(false);
    ui->searchParamBox->setVisible(false);

    // For search
    listView = new QListView(ui->searchParamBox);
    ui->searchParamBox->setView(listView);

    loadDataFromDB();   // Load data from database

    connect(ui->searchButton, &QToolButton::clicked, this, &TableForm::showSearchWidgets);

    connect(ui->searchLine, &QLineEdit::textChanged, this, &TableForm::searchInDB); // Interactive search in database

    connect(ui->createButton, &QToolButton::clicked, this, [this] {
        mainModel->insertRow(mainModel->rowCount(QModelIndex()));
    });

    connect(ui->acceptBtn, &QToolButton::clicked, this, &TableForm::acceptData);

    connect(ui->deleteButton, &QToolButton::clicked, this, &TableForm::deleteDatafromDB); // A row was selected in the table
}

TableForm::~TableForm()
{
    delete ui;
}

void TableForm::loadDataFromDB()
{
    // Load data
    mainModel = new QSqlRelationalTableModel(this);
    mainModel->setTable("main_table");
    mainModel->setSort(0, Qt::AscendingOrder);
    mainModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->mainTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->mainTableView->setModel(mainModel);

    if (mainModel->select()) {
        // Select
        mainModel->setRelation(2, QSqlRelation("equipment_table", "id", "equipment_name"));
        mainModel->setRelation(3, QSqlRelation("worker_table", "id", "worker_name"));
        mainModel->select();
    }
    else {
        mod = new QSqlQueryModel();
        QSqlQuery query;
//        query.exec( "SELECT id, order_number, (SELECT equipment_name FROM equipment_table WHERE id = equipment), "
//                    "(SELECT worker_name FROM worker_table WHERE id = worker), "
//                    "date, part_code, part_name, quantity, part_number, description, start_time, end_time, "
//                    "hours_count, remark, notes "
//                    "FROM main_table" );
        query.exec( "SELECT * FROM main_table" );
        mod->setQuery(query);
        ui->mainTableView->setModel(mod);
    }

    // Hide columns
    ui->mainTableView->setColumnHidden(0, true);

    QStringList headers;
    ui->searchParamBox->clear();

    headers << trUtf8("id") << trUtf8("Order number") << trUtf8("Equipment") << trUtf8("Worker") << trUtf8("Date")
            << trUtf8("Part code") << trUtf8("Part name") << trUtf8("Quantity") << trUtf8("Part number")
            << trUtf8("Description") << trUtf8("Start time") << trUtf8("End time") << trUtf8("Hours count")
            << trUtf8("Remark") << trUtf8("Notes");
    ui->searchParamBox->addItems(headers);

    // Columns size
    for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
        ui->mainTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
    }
}

void TableForm::showSearchWidgets()
{
    // Show widgets for providing search
    ui->searchLine->setVisible(!ui->searchLine->isVisible());
    ui->searchParamBox->setVisible(!ui->searchParamBox->isVisible());
    ui->searchLine->clear();
}

void TableForm::searchInDB(const QString &arg1)
{
    // Interactive search in current database table
}

void TableForm::deleteDatafromDB()
{
    int row = ui->mainTableView->selectionModel()->currentIndex().row();
    if (row == 0) return;

    // Delete current data from database
    mainModel->removeRow(row);
    mainModel->submitAll();
    mainModel->select();
    ui->mainTableView->selectRow(row);
}

void TableForm::setRights(const QString user, int rights)
{
    // User rights: read or read and edit mode
    this->user = user;
    if (rights == 3) {
        // Read only mode
        ui->createButton->setVisible(false);
        ui->acceptBtn->setVisible(false);
        ui->deleteButton->setVisible(false);
        ui->mainTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        mainModel->select();
    }
}
void TableForm::acceptData()
{
    // Write data into database
    mainModel->submitAll();
    mainModel->select();
}
