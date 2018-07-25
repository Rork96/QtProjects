#include "editorform.h"
#include "ui_editorform.h"

#include "database.h"
#include <QSqlQuery>
#include <QSqlRecord>

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

    model = new QSqlRelationalTableModel(this);
    model->setTable(MAIN_TABLE);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0, Qt::AscendingOrder);

    // Set relation between tables
    int equipIndex = model->fieldIndex(EQUIPMENT);
    model->setRelation(equipIndex, QSqlRelation(EQUIPMENT_TABLE, "id", EQUIPMENT_NAME));

    // New relation model for equipment
    QSqlTableModel *equipRelModel = model->relationModel(equipIndex); // Relation index
    ui->equipComboBox->setModel(equipRelModel);
    ui->equipComboBox->setModelColumn(equipRelModel->fieldIndex(EQUIPMENT_NAME));

    // Set relation between tables
    int workerIndex = model->fieldIndex(WORKER);
    model->setRelation(workerIndex, QSqlRelation(WORKER_TABLE, "id", WORKER_NAME));

    // New relation model for worker
    QSqlTableModel *workerRelModel = model->relationModel(workerIndex); // Relation index
    ui->workComboBox->setModel(workerRelModel);
    ui->workComboBox->setModelColumn(workerRelModel->fieldIndex(WORKER_NAME));

    model->select();

    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    mapper->addMapping(ui->orderNumberSpin, 1);
    mapper->addMapping(ui->equipComboBox, equipIndex);
    mapper->addMapping(ui->workComboBox, workerIndex);
    mapper->addMapping(ui->dateEdit, 4);
    mapper->addMapping(ui->partCodeLine, 5);
    mapper->addMapping(ui->partNameLine, 6);
    mapper->addMapping(ui->quantitySpin, 7);
    mapper->addMapping(ui->partNumberSpin, 8);
    mapper->addMapping(ui->descriptionEdit, 9);
    mapper->addMapping(ui->startTimeEdit, 10);
    mapper->addMapping(ui->endTimeEdit, 11);
    mapper->addMapping(ui->hCountTimeEdit, 12);        // Calck
    mapper->addMapping(ui->remarkEdit, 13);
    mapper->addMapping(ui->notesEdit, 14);

    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();

    ui->submitButton->setEnabled(false); // Order number, part code, part name, worker and equipment cannot be blank

    clearAll(); // Clear all data

    // region Connections
    connect(ui->rejectButton, &QToolButton::clicked, this, &EditorForm::clearAll);

    connect(ui->submitButton, &QToolButton::clicked, this, &EditorForm::submitChanges); // Save data to database

    // Order number, part code, part name, worker and equipment cannot be blank
    connect(ui->partCodeLine, &QLineEdit::textChanged, this, [this] {
        ui->submitButton->setEnabled(!ui->partCodeLine->text().isEmpty() && !ui->partNameLine->text().isEmpty());
    });
    connect(ui->partNameLine, &QLineEdit::textChanged, ui->partCodeLine, &QLineEdit::textChanged);

    connect(ui->startTimeEdit, &QTimeEdit::userTimeChanged, this, &EditorForm::calckTime);
    connect(ui->endTimeEdit, &QTimeEdit::userTimeChanged, this, &EditorForm::calckTime);
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
    ui->orderNumberSpin->setValue(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->partCodeLine->clear();
    ui->partNameLine->clear();
    ui->quantitySpin->setValue(0);
    ui->partNumberSpin->setValue(0);
    ui->descriptionEdit->clear();
    ui->equipComboBox->setCurrentIndex(0);
    ui->workComboBox->setCurrentIndex(0);
    ui->startTimeEdit->setTime(QTime(0, 0));
    ui->endTimeEdit->setTime(QTime(0, 0));
    ui->hCountTimeEdit->setTime(QTime(0, 0));
    ui->notesEdit->clear();
    ui->remarkEdit->clear();
}
void EditorForm::submitChanges()
{
    // Save data to database
    mapper->submit();
    model->submitAll();

    model->select();
    mapper->toLast();

    // Clear all data
    clearAll();
}

void EditorForm::calckTime()
{
    // Calculate time
    int start = ui->startTimeEdit->time().msecsSinceStartOfDay();
    int end = ui->endTimeEdit->time().msecsSinceStartOfDay();
    int result;

    // 11:30 - 12.00 - Dinner
    if (ui->startTimeEdit->time() < QTime(11, 30) && ui->endTimeEdit->time() > QTime(12, 00)) {
        result = end - start - QTime(0, 30).msecsSinceStartOfDay();
    }
    else {
        result = end - start;
    }
    ui->hCountTimeEdit->setTime(QTime::fromMSecsSinceStartOfDay(result));   // Set
}
