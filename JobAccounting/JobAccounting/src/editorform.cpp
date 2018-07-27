#include "editorform.h"
#include "ui_editorform.h"

#include "database.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QScreen>
#include "combodelegate.h"
#include "noteditabledelegate.h"

#include <QDebug>

EditorForm::EditorForm(QWidget *parent):
    QWidget(parent),
    ui(new Ui::EditorForm)
{
    // Program settings (ini in current program directorry)
    set = new QSettings("settings.ini", QSettings::IniFormat, this);

    // Load translations
    QString lang = set->value("JobAccounting/lang", "ru").toString();
    qtLanguageTranslator.load(QString("translations/") + lang);
    qApp->installTranslator(&qtLanguageTranslator);

    ui->setupUi(this);

    // Set flag into toolButton
    if (lang == "en")
        ui->languageButton->setIcon(QIcon(":/english.png"));
    else if (lang == "ru")
        ui->languageButton->setIcon(QIcon(":/russian.png"));
    else
        ui->languageButton->setIcon(QIcon(":/ukrainian.png"));

    // Add language actions toolButton
    languageMenu = new QMenu(this);
    languageMenu->addActions(QList<QAction *>() << ui->actionEnglish << ui->actionRussian << ui->actionUkrainian);
    ui->languageButton->setMenu(languageMenu);
    ui->languageButton->setPopupMode(QToolButton::InstantPopup);

    loadData(); /// Load data from database
    setFilter();

    // region Connections
    connect(ui->rejectButton, &QToolButton::clicked, this, &EditorForm::clearAll);

    // Set filter to model in table
    connect(ui->workComboBox, &QComboBox::currentTextChanged, this, &EditorForm::setFilter);
    connect(ui->equipComboBox, &QComboBox::currentTextChanged, this, &EditorForm::setFilter);
    connect(ui->dateEdit, &QDateEdit::userDateChanged, this, &EditorForm::setFilter);

    connect(ui->submitButton, &QToolButton::clicked, this, &EditorForm::submitChanges); // Save data to database

    connect(ui->addButton, &QToolButton::clicked, this, [this] {
        int lastRow = mainModel->rowCount();
        qDebug() << lastRow;
        mainModel->insertRow(lastRow);
        int equipId = ui->equipComboBox->itemData(ui->equipComboBox->currentIndex(), Qt::UserRole).toInt();
        int workerId = ui->workComboBox->itemData(ui->workComboBox->currentIndex(), Qt::UserRole).toInt();
        mainModel->setData(mainModel->index(lastRow, 2), equipId);
        mainModel->setData(mainModel->index(lastRow, 3), workerId);
        mainModel->setData(mainModel->index(lastRow, 4), ui->dateEdit->date());
    });

    // Data in tableView changed
    connect(ui->tableView->model(), &QAbstractItemModel::dataChanged, this, &EditorForm::calckTime);

    connect(ui->updateButton, &QToolButton::clicked, this, [this] { loadData(); });
    // endregion

    // region Translations
    connect(ui->actionEnglish, &QAction::triggered, this, [this] {
        ui->languageButton->setIcon(QIcon(":/english.png"));
        translate("en");
    });
    connect(ui->actionRussian, &QAction::triggered, this, [this] {
        ui->languageButton->setIcon(QIcon(":/russian.png"));
        translate("ru");
    });
    connect(ui->actionUkrainian, &QAction::triggered, this, [this] {
        ui->languageButton->setIcon(QIcon(":/ukrainian.pngg"));
        translate("uk");
    });
    // endregion Translations
}

EditorForm::~EditorForm()
{
    delete ui;
}

void EditorForm::loadData()
{
    // Load data from database

    // Parameters for equipment
    QSqlQuery query;
    query.prepare( QString( "SELECT %1.id, %2 FROM %1" ).arg(EQUIPMENT_TABLE).arg(EQUIPMENT_NAME) );
    query.exec();
    // query.value(1).toString() - text (data from visualColumn)
    // query.value(0) - userData (id from table)
    ui->equipComboBox->addItem("(please select)", "");
    while (query.next()) {
        // Write query.value(1).toString() as displayed text
        // and query.value(0) as userData (Qt::UserRole)
        ui->equipComboBox->addItem(query.value(1).toString(), query.value(0));
    }

    // Parameters for worker
    query.prepare( QString( "SELECT %1.id, %2 FROM %1" ).arg(WORKER_TABLE).arg(WORKER_NAME) );
    query.exec();
    // query.value(1).toString() - text (data from visualColumn)
    // query.value(0) - userData (id from table)
    ui->workComboBox->addItem("(please select)", "");
    while (query.next()) {
        // Write query.value(1).toString() as displayed text
        // and query.value(0) as userData (Qt::UserRole)
        ui->workComboBox->addItem(query.value(1).toString(), query.value(0));
    }

    // Model for table
    mainModel = new QSqlRelationalTableModel(this);
    mainModel->setTable(MAIN_TABLE);
    mainModel->setSort(1, Qt::AscendingOrder);  // Sort by order number
    mainModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    mainModel->select();
    ui->tableView->setModel(mainModel);
    ui->tableView->setSortingEnabled(true);     // Enable sorting
    // Hide columns
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setColumnHidden(2, true);
    ui->tableView->setColumnHidden(3, true);
    ui->tableView->setColumnHidden(4, true);
    ui->tableView->setColumnHidden(14, true);
    ui->tableView->setColumnHidden(15, true);
    ui->tableView->setColumnHidden(16, true);

    QStringList headers = QStringList() << trUtf8("id") << trUtf8("Order number") << trUtf8("Equipment")
        << trUtf8("Worker") << trUtf8("Date") << trUtf8("Part") << trUtf8("Quantity") << trUtf8("OTK")
        << trUtf8("Description") << trUtf8("Start time") << trUtf8("End time") << trUtf8("Hours count")
        << trUtf8("Remark") << trUtf8("Notes") << trUtf8("Creator") << trUtf8("Creation date") << trUtf8("Editing date");

    // Columns size
    for (int i = 0; i < ui->tableView->horizontalHeader()->count(); i++) {
        mainModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
    }
    // Resize columns width dependent on the screen width
    QRect rect = QApplication::screens().at(0)->geometry();
    ui->tableView->horizontalHeader()->setDefaultSectionSize(rect.width()/(ui->tableView->horizontalHeader()->count()-7) -7);

    // Select
    mainModel->setRelation(1, QSqlRelation(ORDER_TABLE, "id", ORDER_NAME));         // order number
    mainModel->setRelation(5, QSqlRelation(PART_TABLE, "id", PART_NAME));           // part
    mainModel->select();

    // Delegate for order number
    auto *ordCb = new ComboBoxDelegate(ui->tableView, ORDER_NAME, ORDER_TABLE);
    ui->tableView->setItemDelegateForColumn(1, ordCb);

    // Delegate for part
    QString ordText = mainModel->itemData(mainModel->index(mainModel->rowCount()-1, 1)).value(0).toString();
    auto *partCb = new ComboBoxDelegate(ui->tableView, PART_NAME, PART_TABLE);
    ui->tableView->setItemDelegateForColumn(5, partCb);
    // Also delegate for part reset in function calckTime()

    // Forbid edit hours count column
    ui->tableView->setItemDelegateForColumn(11, new NotEditableDelegate());

    clearAll(); // Clear all data
}

void EditorForm::changeEvent(QEvent *event)
{
    // Change language
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

void EditorForm::translate(QString language)
{
    qtLanguageTranslator.load("translations/" + language, ".");
    qApp->installTranslator(&qtLanguageTranslator);
    set->setValue("JobAccounting/lang", language);
}

void EditorForm::clearAll()
{
    // Clear all data
    //ui->dateEdit->setDate(QDate::currentDate());
    //ui->equipComboBox->setCurrentIndex(0);
    //ui->workComboBox->setCurrentIndex(0);
}
void EditorForm::submitChanges()
{
    // Save data to database
    mainModel->submitAll();
    mainModel->select();

    // Clear all data
    clearAll();
}

void EditorForm::calckTime(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &/* roles */)
{
    // Calculate time
    if (topLeft.column() == 9 || topLeft.column() == 10) {
        QTime startTime = mainModel->itemData(mainModel->index(topLeft.row(), 9)).value(0).toTime();
        QTime endTime = mainModel->itemData(mainModel->index(topLeft.row(), 10)).value(0).toTime();
        int result;

        // 11:30 - 12.00 - Dinner
        if (startTime < QTime(11, 30) && endTime > QTime(12, 00)) {
            result = endTime.msecsSinceStartOfDay() - startTime.msecsSinceStartOfDay() - QTime(0, 30).msecsSinceStartOfDay();
        }
        else {
            result = endTime.msecsSinceStartOfDay() - startTime.msecsSinceStartOfDay();
        }
        mainModel->setData(mainModel->index(topLeft.row(), 11), QTime::fromMSecsSinceStartOfDay(result));
    }
    else if (topLeft.column() == 1) {   // When order number changed adjust parameters in delegate
        // Delegate for part
        QString ordText = mainModel->itemData(mainModel->index(topLeft.row(), 1)).value(0).toString();
        auto *partCb = new ComboBoxDelegate(ui->tableView, PART_NAME, PART_TABLE " WHERE " ORDER_ID " = "
                                            "(SELECT id FROM " ORDER_TABLE " WHERE " ORDER_NAME " = '" + ordText + "')");
        ui->tableView->setItemDelegateForColumn(5, partCb);
    }
}

void EditorForm::setFilter()
{
    // Set filter to model in table
    QString filterString;
    int equipId = ui->equipComboBox->itemData(ui->equipComboBox->currentIndex(), Qt::UserRole).toInt();
    int workerId = ui->workComboBox->itemData(ui->workComboBox->currentIndex(), Qt::UserRole).toInt();

    filterString = QString("%1 = %2 AND %3 = '%4' AND text(%5) = '%6'").arg(EQUIPMENT).arg(equipId).
        arg(WORKER).arg(workerId).
        arg(DATE).arg(ui->dateEdit->date().toString("yyyy-MM-dd"));
    qDebug() << filterString;
    mainModel->setFilter(filterString);
    mainModel->select();
}
