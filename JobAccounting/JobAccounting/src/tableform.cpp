#include "tableform.h"
#include "ui_tableform.h"

#include "database.h"
#include <QSqlQuery>
#include <QDate>
#include <QTime>
#include "mainwindow.h"
#include "combodelegate.h"

#include <QDebug>

TableForm::TableForm(QWidget *parent, QString tableName) :
    QWidget(parent),
    ui(new Ui::TableForm)
{
    ui->setupUi(this);

    // Hide widgets for search
    ui->searchLine->setVisible(false);
    ui->searchParamBox->setVisible(false);
    ui->searchBox->setVisible(false);

    // For search
    listView = new QListView(ui->searchParamBox);
    ui->searchParamBox->setView(listView);

    this->currentTable = tableName;     // Save table name
    loadDataFromDB(tableName);          // Load data from database

    // region Connections
    connect(ui->searchButton, &QToolButton::clicked, this, &TableForm::showSearchWidgets);

    connect(ui->searchLine, &QLineEdit::textChanged, this, &TableForm::searchInDB); // Interactive search in database
    connect(ui->searchParamBox, &QComboBox::currentTextChanged, this, &TableForm::adjustSearchForComboBox);

    connect(ui->searchBox, &QComboBox::currentTextChanged, this, &TableForm::searchForComboBox);

    connect(ui->createButton, &QToolButton::clicked, this, [this] {
        int lastRow = mainModel->rowCount();
        mainModel->insertRow(lastRow);
        mainModel->setData(mainModel->index(lastRow, 4), QDate::currentDate());
        ui->mainTableView->selectRow(lastRow);
    });

    connect(ui->acceptBtn, &QToolButton::clicked, this, &TableForm::acceptData);

    connect(ui->deleteButton, &QToolButton::clicked, this, &TableForm::deleteDatafromDB); // A row was selected in the table

    connect(ui->refreshButton, &QToolButton::clicked, this, [this] { loadDataFromDB(this->currentTable); });

    // Data in tableView changed
    connect(ui->mainTableView->model(), &QAbstractItemModel::dataChanged, this, &TableForm::calculateTime);
    // endregion
}

TableForm::~TableForm()
{
    delete ui;
}

void TableForm::loadDataFromDB(const QString &table)
{
    // Load data

    auto initTable = [this](const QString& tableName)
    {
        mainModel = new QSqlRelationalTableModel(this);
        mainModel->setTable(tableName);
        mainModel->setSort(0, Qt::AscendingOrder);
        mainModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        ui->mainTableView->setSelectionMode(QAbstractItemView::SingleSelection);
        mainModel->select();
        ui->mainTableView->setModel(mainModel);
        ui->mainTableView->setColumnHidden(0, true); // Hide
    };

    initTable(table);

    QStringList headers;

    if (table == MAIN_TABLE) {
        // Select
        mainModel->setRelation(2, QSqlRelation(EQUIPMENT_TABLE, "id", EQUIPMENT_NAME)); // equipment
        mainModel->setRelation(3, QSqlRelation(WORKER_TABLE, "id", WORKER_NAME));       // worker
        mainModel->select();

        // Delegate for equipment
        auto *eqCb = new ComboBoxDelegate(ui->mainTableView, EQUIPMENT_NAME, EQUIPMENT_TABLE);
        ui->mainTableView->setItemDelegateForColumn(2, eqCb);

        // Delegate for worker
        auto *wCb = new ComboBoxDelegate(ui->mainTableView, WORKER_NAME, WORKER_TABLE);
        ui->mainTableView->setItemDelegateForColumn(3, wCb);

        headers << trUtf8("id") << trUtf8("Order number") << trUtf8("Equipment") << trUtf8("Worker") << trUtf8("Date")
                << trUtf8("Part code") << trUtf8("Part name") << trUtf8("Quantity") << trUtf8("Part number")
                << trUtf8("Description") << trUtf8("Start time") << trUtf8("End time") << trUtf8("Hours count")
                << trUtf8("Remark") << trUtf8("Notes");
    }
    else if (table == WORKER_TABLE) {
        headers << trUtf8("id") << trUtf8("Worker name");
    }
    else if (table == EQUIPMENT_TABLE) {
        // equipment table
        headers << trUtf8("id") << trUtf8("Equipment name");
    }

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
    ui->searchBox->setVisible(!ui->searchBox->isVisible());
    ui->searchLine->clear();
    ui->searchParamBox->clear();

    // Add items into searchParamBox
    ui->searchParamBox->addItem("Order number");
    ui->searchParamBox->addItem("Worker");
    ui->searchParamBox->setCurrentIndex(0);
}

void TableForm::searchInDB(const QString &arg1)
{
    // Interactive search in current database table
    QString filterString = QString("text(%1) LIKE '%2%'").arg(ORDER).arg(arg1);
    mainModel->setFilter(filterString);
    mainModel->select();
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

void TableForm::setRights(int &rights)
{
    // User rights: read or read and edit mode
    if (rights == 1) {
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
void TableForm::searchForComboBox()
{
    // Search data
    QString filterString;
    if (ui->searchBox->currentIndex() > 0) {
        int id = ui->searchBox->itemData(ui->searchBox->currentIndex(), Qt::UserRole).toInt();    // Get id form Qt::UserRole
        filterString = QString("%1 = %2").arg(WORKER).arg(id);
    }
    else {
        filterString = QString("text(%1) LIKE '%2%'").arg(ORDER).arg("");
    }
    mainModel->setFilter(filterString);
    mainModel->select();
}
void TableForm::adjustSearchForComboBox()
{
    if (ui->searchParamBox->currentIndex() == 1) {
        ui->searchLine->setVisible(false);
        ui->searchBox->setVisible(ui->searchParamBox->isVisible());
        // Search parameters for worker
        QSqlQuery query;
        query.prepare( QString( "SELECT %1.id, %2 FROM %1" ).arg(WORKER_TABLE).arg(WORKER_NAME) );
        query.exec();
        // query.value(1).toString() - text (data from visualColumn)
        // query.value(0) - userData (id from table)
        ui->searchBox->addItem("(please select)", "");
        while (query.next()) {
            // Write query.value(1).toString() as displayed text
            // and query.value(0) as userData (Qt::UserRole)
            ui->searchBox->addItem(query.value(1).toString(), query.value(0));
        }
    }
    else {
        ui->searchBox->setVisible(false);
        ui->searchLine->setVisible(ui->searchParamBox->isVisible());
        ui->searchLine->clear();
        QString filterString = QString("text(%1) LIKE '%2%'").arg(ORDER).arg("");
        mainModel->setFilter(filterString);
        mainModel->select();
    }
}
void TableForm::reloadView()
{
    // Reload table when language changed
    loadDataFromDB(this->currentTable);
}
void TableForm::calculateTime(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &/* roles */)
{
    // Calculete time
    if (topLeft.column() == 10 || topLeft.column() == 11) {
        QTime startTime = mainModel->itemData(mainModel->index(topLeft.row(), 10)).value(0).toTime();
        QTime endTime = mainModel->itemData(mainModel->index(topLeft.row(), 11)).value(0).toTime();
        int result;

        // 11:30 - 12.00 - Dinner
        if (startTime < QTime(11, 30) && endTime > QTime(12, 00)) {
            result = endTime.msecsSinceStartOfDay() - startTime.msecsSinceStartOfDay() - QTime(0, 30).msecsSinceStartOfDay();
        }
        else {
            result = endTime.msecsSinceStartOfDay() - startTime.msecsSinceStartOfDay();
        }
        mainModel->setData(mainModel->index(topLeft.row(), 12), QTime::fromMSecsSinceStartOfDay(result));
    }
}
