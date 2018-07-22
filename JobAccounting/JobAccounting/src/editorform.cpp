#include "editorform.h"
#include "ui_editorform.h"

#include <QSqlQuery>
#include <QSqlRecord>

EditorForm::EditorForm(QWidget *parent):
    QWidget(parent),
    ui(new Ui::EditorForm)
{
    ui->setupUi(this);

    model = new QSqlRelationalTableModel(this);
    model->setTable(Main_Table);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0, Qt::AscendingOrder);
    model->select();

    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    mapper->addMapping(ui->orderNumberSpin, 1);
    // 2 - equipmentBox
    // 3 - workerBox
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

    // Equipment comboBox
    equipModel = new BaseComboModel(Equipment_Name, Equipment_Table, this, "", "");
    ui->equipmentBox->setModel(equipModel);

    // Worker comboBox
    workerModel = new BaseComboModel(Worker_Name, Worker_Table, this, "", "");
    ui->workerBox->setModel(workerModel);

    clearAll(); // Clear all data

    // region Connections
    connect(ui->rejectButton, &QToolButton::clicked, this, &EditorForm::clearAll);

    connect(ui->submitButton, &QToolButton::clicked, this, &EditorForm::submitChanges); // Save data to database

    // Order number, part code, part name, worker and equipment cannot be blank
    connect(ui->partCodeLine, &QLineEdit::textChanged, this, [this] {
        ui->submitButton->setEnabled(!ui->partCodeLine->text().isEmpty() && !ui->partNameLine->text().isEmpty() &&
            ui->workerBox->currentIndex() > 0 && ui->equipmentBox->currentIndex() > 0);
    });
    connect(ui->partNameLine, &QLineEdit::textChanged, ui->partCodeLine, &QLineEdit::textChanged);
    connect(ui->workerBox, &QComboBox::currentTextChanged, ui->partCodeLine, &QLineEdit::textChanged);
    connect(ui->equipmentBox, &QComboBox::currentTextChanged, ui->partCodeLine, &QLineEdit::textChanged);

    connect(ui->startTimeEdit, &QTimeEdit::userTimeChanged, this, &EditorForm::calckTime);
    connect(ui->endTimeEdit, &QTimeEdit::userTimeChanged, this, &EditorForm::calckTime);
    // endregion
}

EditorForm::~EditorForm()
{
    delete ui;
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
    ui->equipmentBox->setCurrentIndex(0);
    ui->workerBox->setCurrentIndex(0);
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

    int id = model->record(mapper->currentIndex()).value("id").toInt(); // Correct id needed

    QString str = QString( "UPDATE %1 SET equipment = %2, worker = %3 WHERE id = %4" ).arg(Main_Table).
        arg(ui->equipmentBox->itemData(ui->equipmentBox->currentIndex(), Qt::UserRole).toInt()).
        arg(ui->workerBox->itemData(ui->workerBox->currentIndex(), Qt::UserRole).toInt()).
        arg(id);

    QSqlQuery query;
    query.exec(str);

    model->select();
    mapper->toLast();

    // Clear all data
    clearAll();
}
void EditorForm::calckTime()
{
    // Calculate time
    QTime time = QTime(ui->endTimeEdit->time().hour() - ui->startTimeEdit->time().hour(),
        ui->endTimeEdit->time().minute() - ui->startTimeEdit->time().minute());
    ui->hCountTimeEdit->setTime(time);
}
