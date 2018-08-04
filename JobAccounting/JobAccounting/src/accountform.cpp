#include "accountform.h"
#include "ui_accountform.h"

#include "database.h"
#include <QSqlQuery>
#include <QTime>
#include <QScreen>
#include "mainwindow.h"
#include "noteditabledelegate.h"

AccountForm::AccountForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountForm)
{
    ui->setupUi(this);

    // Hide widgets for search
    ui->orderBox->setVisible(false);
    ui->equipBox->setVisible(false);

    loadDataFromDB();          // Load data from database

    // region Connections

    // Search in database
    connect(ui->searchButton, &QToolButton::clicked, this, &AccountForm::showSearchWidgets);
    connect(ui->orderBox, &QComboBox::currentTextChanged, this, &AccountForm::searchInDB);
    connect(ui->equipBox, &QComboBox::currentTextChanged, this, &AccountForm::searchInDB);

    connect(ui->acceptBtn, &QToolButton::clicked, this, &AccountForm::acceptData);

    connect(ui->refreshButton, &QToolButton::clicked, this, [this] { loadDataFromDB(); });

    // Data in tableView changed
    connect(ui->mainTableView->model(), &QAbstractItemModel::dataChanged, this, &AccountForm::calculateData);

    // Sorting
    connect(ui->mainTableView->horizontalHeader(), &QHeaderView::sectionClicked, this, &AccountForm::sortByColumn);
    // endregion
}

AccountForm::~AccountForm()
{
    delete ui;
}

void AccountForm::loadDataFromDB()
{
    // Load data

    //mainModel = new QSqlRelationalTableModel(this);
    mainModel = new TableModel(this);
    mainModel->setTable(ACCOUNT_TABLE);
    mainModel->setSort(1, Qt::AscendingOrder);  // Sort by order number
    mainModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->mainTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    mainModel->select();
    ui->mainTableView->setModel(mainModel);
    ui->mainTableView->setSortingEnabled(true);     // Enable sorting
    ui->mainTableView->setColumnHidden(0, true);    // Hide column

    QStringList headers;

    // Select
    mainModel->setRelation(1, QSqlRelation(ORDER_TABLE, "id", ORDER_NAME));         // order number
    mainModel->setRelation(2, QSqlRelation(EQUIPMENT_TABLE, "id", EQUIPMENT_NAME)); // equipment
    mainModel->setRelation(3, QSqlRelation(PART_TABLE, "id", PART_NAME));           // part
    mainModel->select();

    headers << trUtf8("id") << trUtf8("Order number") << trUtf8("Equipment") << trUtf8("Part") << trUtf8("OTK accepted")
            << trUtf8("Time spended") << trUtf8("Part count") << trUtf8("Written off") << trUtf8("Remainder");

    // Forbid edit columns
    for (int i = 1; i < 6; i++) {
        ui->mainTableView->setItemDelegateForColumn(i, new NotEditableDelegate());
    }
    ui->mainTableView->setItemDelegateForColumn(7, new NotEditableDelegate());
    ui->mainTableView->setItemDelegateForColumn(8, new NotEditableDelegate());

    // Set headers
    for (int i = 0; i < ui->mainTableView->horizontalHeader()->count(); i++) {
        mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
    }

    // Resize columns width dependent on the screen width
    QRect rect = QApplication::screens().at(0)->geometry();
    ui->mainTableView->horizontalHeader()->setDefaultSectionSize(rect.width()/(ui->mainTableView->horizontalHeader()->count()-1) -5);
}

void AccountForm::showSearchWidgets()
{
    // Show widgets for providing search
    ui->orderBox->setVisible(!ui->orderBox->isVisible());
    ui->equipBox->setVisible(!ui->equipBox->isVisible());
    ui->orderBox->clear();
    ui->equipBox->clear();

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
    if (ui->equipBox->isVisible()) {
        QSqlQuery query;
        query.prepare(QString("SELECT %1.id, %2 FROM %1").arg(EQUIPMENT_TABLE).arg(EQUIPMENT_NAME));
        query.exec();
        // query.value(1).toString() - text (data from visualColumn)
        // query.value(0) - userData (id from table)
        ui->equipBox->addItem(trUtf8("(please select)"), "");
        while (query.next()) {
            // Write query.value(1).toString() as displayed text
            // and query.value(0) as userData (Qt::UserRole)
            ui->equipBox->addItem(query.value(1).toString(), query.value(0));
        }
    }
    // Clear filter
    mainModel->setFilter("");
    mainModel->select();
}

void AccountForm::searchInDB()
{
    // Interactive search in current database table
    int orderId = ui->orderBox->itemData(ui->orderBox->currentIndex(), Qt::UserRole).toInt(); // Get id form Qt::UserRole
    int equipId = ui->equipBox->itemData(ui->equipBox->currentIndex(), Qt::UserRole).toInt(); // Get id form Qt::UserRole
    QString filterString = "";
    if (orderId == 0) {
        filterString = QString("%1 = %2").arg(WORKER).arg(equipId);
    }
    else if (equipId == 0) {
        filterString = QString("%1 = %2").arg(ORDER).arg(orderId);
    }
    else {
        filterString = QString("%1 = %2 AND %3 = %4").arg(ORDER).arg(orderId);
    }
    mainModel->setFilter(filterString);
    mainModel->select();
}

void AccountForm::acceptData()
{
    // Write data into database
    mainModel->submitAll();
    mainModel->select();
}

void AccountForm::reloadView()
{
    // Reload table when language changed
    loadDataFromDB();
}

void AccountForm::calculateData(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &/* roles */)
{
    // Calculete data
    if (topLeft.column() == 6) {
        int acceptedOtk = mainModel->itemData(mainModel->index(topLeft.row(), 4)).value(0).toInt();
        QTime spendedTime = mainModel->itemData(mainModel->index(topLeft.row(), 5)).value(0).toTime();
        int param = mainModel->itemData(mainModel->index(topLeft.row(), 6)).value(0).toInt();
        int written = (spendedTime.msecsSinceStartOfDay()/acceptedOtk)*param;
        int remTime = spendedTime.msecsSinceStartOfDay() - written;
        mainModel->setData(mainModel->index(topLeft.row(), 7), QTime::fromMSecsSinceStartOfDay(written));
        mainModel->setData(mainModel->index(topLeft.row(), 8), QTime::fromMSecsSinceStartOfDay(remTime));
    }
}

void AccountForm::sortByColumn(int index)
{
    // Sorting in tableView
    mainModel->setSort(index, Qt::AscendingOrder);
}
