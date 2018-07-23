#include "tableform.h"
#include "ui_tableform.h"

#include "database.h"
#include <QScreen>
#include <QSqlQuery>
#include <QtWidgets/QTableWidgetItem>
#include <QtCore/QTime>

#include "combodelegate.h"

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

    loadDataFromDB(tableName);   // Load data from database

    // region Connections
    connect(ui->searchButton, &QToolButton::clicked, this, &TableForm::showSearchWidgets);

    connect(ui->searchLine, &QLineEdit::textChanged, this, &TableForm::searchInDB); // Interactive search in database
    connect(ui->searchParamBox, &QComboBox::currentTextChanged, this, &TableForm::adjustSearchForComboBox);

    connect(ui->searchBox, &QComboBox::currentTextChanged, this, &TableForm::searchForComboBox);

    connect(ui->createButton, &QToolButton::clicked, this, [this] {
        mainModel->insertRow(mainModel->rowCount(QModelIndex()));
        int column = mainModel->fieldIndex("data");
        mainModel->setData(mainModel->index(mainModel->rowCount(), 4), QTime::currentTime().toString());

//        if (column != -1) {
//            mainModel->setData(mainModel->index(0, column), QTime::currentTime().toString());
//        }
    });

    connect(ui->acceptBtn, &QToolButton::clicked, this, &TableForm::acceptData);

    connect(ui->deleteButton, &QToolButton::clicked, this, &TableForm::deleteDatafromDB); // A row was selected in the table
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

    if (table == Main_Table) {
        // Select
        mainModel->setRelation(2, QSqlRelation(Equipment_Table, "id", Equipment_Name));
        mainModel->setRelation(3, QSqlRelation(Worker_Table, "id", Worker_Name));
        mainModel->select();

        ComboBoxDelegate *equipdelegate = new ComboBoxDelegate();
        equipdelegate->setEditorData(new QComboBox(), QModelIndex(), Equipment_Name, Equipment_Table, Main_Table, "equipment");
        ui->mainTableView->setItemDelegateForColumn(2, equipdelegate);

        headers << trUtf8("id") << trUtf8("Order number") << trUtf8("Equipment") << trUtf8("Worker") << trUtf8("Date")
                << trUtf8("Part code") << trUtf8("Part name") << trUtf8("Quantity") << trUtf8("Part number")
                << trUtf8("Description") << trUtf8("Start time") << trUtf8("End time") << trUtf8("Hours count")
                << trUtf8("Remark") << trUtf8("Notes");
    }
    else if (table == Worker_Table) {
        headers << trUtf8("id") << trUtf8("Worker name");
    }
    else if (table == Equipment_Table) {
        // equipment_table
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
    QString filterString = QString("text(%1) LIKE '%2%'").arg(Order_Column).arg(arg1);
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

void TableForm::setRights(QString user, int &rights)
{
    // User rights: read or read and edit mode
    this->user = user;
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
    if (ui->searchBox->currentIndex() > 0) {
        int index = ui->searchBox->itemData(ui->searchBox->currentIndex(), Qt::UserRole).toInt();
        QString filterString = QString("%1 = %2").arg(Worker_Column).arg(index);
        mainModel->setFilter(filterString);
        mainModel->select();
    }
}
void TableForm::adjustSearchForComboBox()
{
    if (ui->searchParamBox->currentIndex() == 1) {
        ui->searchLine->setVisible(false);
        ui->searchBox->setVisible(ui->searchParamBox->isVisible());
        // Search parameters for worker
        cmodel = new BaseComboModel(Worker_Name, Worker_Table, this, "", "");
        ui->searchBox->setModel(cmodel);
    }
    else {
        ui->searchBox->setVisible(false);
        ui->searchLine->setVisible(ui->searchParamBox->isVisible());
        ui->searchLine->clear();
        QString filterString = QString("text(%1) LIKE '%2%'").arg(Order_Column).arg("");
        mainModel->setFilter(filterString);
        mainModel->select();
    }
}
