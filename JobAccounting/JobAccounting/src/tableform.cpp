#include "tableform.h"
#include "ui_tableform.h"

#include "database.h"
#include <QSqlQuery>
#include <QDate>
#include <QTime>
#include <QScreen>
#include "mainwindow.h"
#include "combodelegate.h"
#include "noteditabledelegate.h"

#include <QDebug>

TableForm::TableForm(QWidget *parent, QString tableName) :
    QWidget(parent),
    ui(new Ui::TableForm)
{
    ui->setupUi(this);

    // Hide comboBox for order number
    ui->groupBox->setVisible(false);

    // Hide widgets for search
    ui->orderBox->setVisible(false);
    ui->workerBox->setVisible(false);
    ui->startDateEdit->setVisible(false);
    ui->endDateEdit->setVisible(false);

    this->currentTable = tableName;     // Save table name
    loadDataFromDB(tableName);          // Load data from database

    // region Connections

    // Search in database
    connect(ui->searchButton, &QToolButton::clicked, this, &TableForm::showSearchWidgets);
    connect(ui->orderBox, &QComboBox::currentTextChanged, this, &TableForm::searchInDB);
    connect(ui->workerBox, &QComboBox::currentTextChanged, this, &TableForm::searchInDB);
    connect(ui->startDateEdit, &QDateEdit::userDateChanged, this, &TableForm::searchInDB);
    connect(ui->endDateEdit, &QDateEdit::userDateChanged, this, &TableForm::searchInDB);

    connect(ui->createButton, &QToolButton::clicked, this, [this] {
        int lastRow = mainModel->rowCount();
        mainModel->insertRow(lastRow);
        if (mainModel->tableName() != PART_TABLE) {
            mainModel->setData(mainModel->index(lastRow, 4), QDate::currentDate());
        }
        else {
            int id = ui->orderCBox->itemData(ui->orderCBox->currentIndex(), Qt::UserRole).toInt();    // Get id form Qt::UserRole
            mainModel->setData(mainModel->index(lastRow, 1), id);
        }
        ui->mainTableView->selectRow(lastRow);
    });

    connect(ui->acceptBtn, &QToolButton::clicked, this, &TableForm::acceptData);

    connect(ui->deleteButton, &QToolButton::clicked, this, &TableForm::deleteDatafromDB); // A row was selected in the table

    connect(ui->refreshButton, &QToolButton::clicked, this, [this] { loadDataFromDB(this->currentTable); });

    // Data in tableView changed
    connect(ui->mainTableView->model(), &QAbstractItemModel::dataChanged, this, &TableForm::calculateTime);

    // Context menu
    connect(ui->mainTableView, &QTableView::customContextMenuRequested, this, &TableForm::customMenuRequested);

    // Sorting
    connect(ui->mainTableView->horizontalHeader(), &QHeaderView::sectionClicked, this, &TableForm::sortByColumn);
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
        mainModel->setSort(1, Qt::AscendingOrder);  // Sort by order number
        mainModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        ui->mainTableView->setSelectionMode(QAbstractItemView::SingleSelection);
        mainModel->select();
        ui->mainTableView->setModel(mainModel);
        ui->mainTableView->setSortingEnabled(true);     // Enable sorting
        ui->mainTableView->setColumnHidden(0, true);    // Hide column
    };

    initTable(table);

    QStringList headers;
    int hiddenColumns = 1;

    if (table == MAIN_TABLE) {
        // Select
        mainModel->setRelation(1, QSqlRelation(ORDER_TABLE, "id", ORDER_NAME));         // order number
        mainModel->setRelation(2, QSqlRelation(EQUIPMENT_TABLE, "id", EQUIPMENT_NAME)); // equipment
        mainModel->setRelation(3, QSqlRelation(WORKER_TABLE, "id", WORKER_NAME));       // worker
        mainModel->setRelation(5, QSqlRelation(PART_TABLE, "id", PART_NAME));           // part
        mainModel->select();

        // Delegate for order number
        auto *ordCb = new ComboBoxDelegate(ui->mainTableView, ORDER_NAME, ORDER_TABLE);
        ui->mainTableView->setItemDelegateForColumn(1, ordCb);

        // Delegate for equipment
        auto *eqCb = new ComboBoxDelegate(ui->mainTableView, EQUIPMENT_NAME, EQUIPMENT_TABLE);
        ui->mainTableView->setItemDelegateForColumn(2, eqCb);

        // Delegate for worker
        auto *wCb = new ComboBoxDelegate(ui->mainTableView, WORKER_NAME, WORKER_TABLE);
        ui->mainTableView->setItemDelegateForColumn(3, wCb);

        // Delegate for part
        QString ordText = mainModel->itemData(mainModel->index(mainModel->rowCount()-1, 1)).value(0).toString();
        auto *partCb = new ComboBoxDelegate(ui->mainTableView, PART_NAME, PART_TABLE);
        ui->mainTableView->setItemDelegateForColumn(5, partCb);
        // Also delegate for part reset in function calculateTime()

        headers << trUtf8("id") << trUtf8("Order number") << trUtf8("Equipment") << trUtf8("Worker") << trUtf8("Date")
                << trUtf8("Part") << trUtf8("Quantity") << trUtf8("OTK") << trUtf8("Description") << trUtf8("Start time")
                << trUtf8("End time") << trUtf8("Hours count") << trUtf8("Remark") << trUtf8("Notes")
                << trUtf8("Creator") << trUtf8("Creation date") << trUtf8("Editing date");

        // Hide column
        ui->mainTableView->setColumnHidden(14, true);
        ui->mainTableView->setColumnHidden(15, true);
        ui->mainTableView->setColumnHidden(16, true);
        hiddenColumns += 3;

        // Forbid edit hours count column
        ui->mainTableView->setItemDelegateForColumn(11, new NotEditableDelegate());
    }
    else if (table == WORKER_TABLE) {
        headers << trUtf8("id") << trUtf8("Worker name");
        ui->searchButton->setVisible(false);
    }
    else if (table == EQUIPMENT_TABLE) {
        // equipment table
        headers << trUtf8("id") << trUtf8("Equipment name");
        ui->searchButton->setVisible(false);
    }
    else if (table == ORDER_TABLE) {
        // order table
        headers << trUtf8("id") << trUtf8("Order number");
        ui->searchButton->setVisible(false);
    }
    else if (table == PART_TABLE) {
        // part table
        ui->mainTableView->setColumnHidden(1, true);    // Hide column

        headers << trUtf8("id") << trUtf8("Order number") << trUtf8("Part") << trUtf8("Count");
        hiddenColumns +=1;

        QSqlQuery query;
        query.prepare( QString( "SELECT %1.id, %2 FROM %1" ).arg(ORDER_TABLE).arg(ORDER_NAME) );
        query.exec();
        // query.value(1).toString() - text (data from visualColumn)
        // query.value(0) - userData (id from table)
        ui->orderCBox->addItem(trUtf8("(please select)"), "");
        while (query.next()) {
            // Write query.value(1).toString() as displayed text
            // and query.value(0) as userData (Qt::UserRole)
            ui->orderCBox->addItem(query.value(1).toString(), query.value(0));
        }
        // Show comboBox
        ui->groupBox->setVisible(true);
        connect(ui->orderCBox, &QComboBox::currentTextChanged, this, &TableForm::setFilterForOrder);
        ui->searchButton->setVisible(false);
    }

    // Columns size
    for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
        mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
    }

    // Resize columns width dependent on the screen width
    QRect rect = QApplication::screens().at(0)->geometry();
    ui->mainTableView->horizontalHeader()->setDefaultSectionSize(rect.width()/(ui->mainTableView->horizontalHeader()->count()-hiddenColumns) -2);
}

void TableForm::showSearchWidgets()
{
    // Show widgets for providing search
    ui->orderBox->setVisible(!ui->orderBox->isVisible());
    ui->workerBox->setVisible(!ui->workerBox->isVisible());
    ui->startDateEdit->setVisible(!ui->startDateEdit->isVisible());
    ui->endDateEdit->setVisible(!ui->endDateEdit->isVisible());
    ui->orderBox->clear();
    ui->workerBox->clear();
    ui->startDateEdit->setDate(QDate(2018, 01, 01));
    ui->endDateEdit->setDate(QDate::currentDate());

    // Order number
    if (ui->orderBox->isVisible()) {
        QSqlQuery query;
        query.prepare(QString("SELECT %1.id, %2 FROM %1").arg(ORDER_TABLE).arg(ORDER_NAME));
        query.exec();
        // query.value(1).toString() - text (data from visualColumn)
        // query.value(0) - userData (id from table)
        ui->orderBox->addItem(trUtf8("(please select)"), "");
        while (query.next()) {
            // Write query.value(1).toString() as displayed text
            // and query.value(0) as userData (Qt::UserRole)
            ui->orderBox->addItem(query.value(1).toString(), query.value(0));
        }
    }
    // Worker
    if (ui->workerBox->isVisible()) {
        QSqlQuery query;
        query.prepare(QString("SELECT %1.id, %2 FROM %1").arg(WORKER_TABLE).arg(WORKER_NAME));
        query.exec();
        // query.value(1).toString() - text (data from visualColumn)
        // query.value(0) - userData (id from table)
        ui->workerBox->addItem(trUtf8("(please select)"), "");
        while (query.next()) {
            // Write query.value(1).toString() as displayed text
            // and query.value(0) as userData (Qt::UserRole)
            ui->workerBox->addItem(query.value(1).toString(), query.value(0));
        }
    }
    // Clear filter
    mainModel->setFilter("");
    mainModel->select();
}

void TableForm::searchInDB()
{
    // Interactive search in current database table
    int orderId = ui->orderBox->itemData(ui->orderBox->currentIndex(), Qt::UserRole).toInt(); // Get id form Qt::UserRole
    int workerId = ui->workerBox->itemData(ui->workerBox->currentIndex(), Qt::UserRole).toInt(); // Get id form Qt::UserRole
    QString startDate = ui->startDateEdit->date().toString("yyyy-MM-dd");
    QString endDate = ui->endDateEdit->date().toString("yyyy-MM-dd");
    QString filterString = "";
    if (orderId == 0) {
        filterString = QString("%1 = %2 AND text(date) BETWEEN '%3' AND '%4'").arg(WORKER).arg(workerId).
            arg(startDate).arg(endDate);
    }
    else if (workerId == 0) {
        filterString = QString("%1 = %2 AND text(date) BETWEEN '%3' AND '%4'").arg(ORDER).arg(orderId).
            arg(startDate).arg(endDate);
    }
    else {
        filterString = QString("%1 = %2 AND %3 = %4 AND text(date) BETWEEN '%5' AND '%6'").arg(ORDER).arg(orderId).
            arg(WORKER).arg(workerId).arg(startDate).arg(endDate);;
    }
    qDebug() << filterString;
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

void TableForm::reloadView()
{
    // Reload table when language changed
    loadDataFromDB(this->currentTable);
}
void TableForm::calculateTime(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &/* roles */)
{
    if (mainModel->tableName() != PART_TABLE) {
        // Calculete time
        if (topLeft.column() == 9 || topLeft.column() == 10) {
            QTime startTime = mainModel->itemData(mainModel->index(topLeft.row(), 9)).value(0).toTime();
            QTime endTime = mainModel->itemData(mainModel->index(topLeft.row(), 10)).value(0).toTime();
            int result;

            // 11:30 - 12.00 - Dinner
            if (startTime < QTime(11, 30) && endTime > QTime(12, 00)) {
                result = endTime.msecsSinceStartOfDay() - startTime.msecsSinceStartOfDay()
                    - QTime(0, 30).msecsSinceStartOfDay();
            }
            else {
                result = endTime.msecsSinceStartOfDay() - startTime.msecsSinceStartOfDay();
            }
            mainModel->setData(mainModel->index(topLeft.row(), 11), QTime::fromMSecsSinceStartOfDay(result));
        }
        else if (topLeft.column() == 1) {   // When order number changed adjust parameters in delegate
            // Delegate for part
            QString ordText = mainModel->itemData(mainModel->index(topLeft.row(), 1)).value(0).toString();
            auto *partCb = new ComboBoxDelegate(ui->mainTableView, PART_NAME, PART_TABLE " WHERE " ORDER_ID " = "
                                        "(SELECT id FROM " ORDER_TABLE " WHERE " ORDER_NAME " = '" + ordText + "')");
            ui->mainTableView->setItemDelegateForColumn(5, partCb);
        }
    }
}

void TableForm::customMenuRequested(const QPoint &point)
{
    // Context menu for table
    QMenu *menu = new QMenu(this);
    menu->addActions(QList<QAction*>() << ui->actionRefresh << ui->actionCreate << ui->actionAccept << menu->addSeparator() << ui->actionDelete);
    menu->popup(ui->mainTableView->viewport()->mapToGlobal(point));
}

void TableForm::sortByColumn(int index)
{
    // Sorting in tableView
    mainModel->setSort(index, Qt::AscendingOrder);
}

void TableForm::setFilterForOrder()
{
    // Filter for order number for part table
    QString filterString;
    if (ui->orderCBox->currentIndex() > 0) {
        int id = ui->orderCBox->itemData(ui->orderCBox->currentIndex(), Qt::UserRole).toInt();    // Get id form Qt::UserRole
        filterString = QString("%1 = %2").arg(ORDER_ID).arg(id);
    }
    else {
        filterString = QString("text(%1) LIKE '%2%'").arg(ORDER_ID).arg("");
    }
    mainModel->setFilter(filterString);
    mainModel->select();
}
