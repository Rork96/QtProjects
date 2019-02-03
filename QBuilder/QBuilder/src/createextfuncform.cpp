#include "createextfuncform.h"
#include "ui_createextfuncform.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>
#include "basecombomodel.h"

CreateExtFuncForm::CreateExtFuncForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateExtFuncForm)
{
    ui->setupUi(this);

    ui->submitButton->setEnabled(false); // All columns cannot be blank

    initData(Table);

    // Set relation between tables
    int typeIndex = model->fieldIndex("extension_type");
    model->setRelation(typeIndex, QSqlRelation("extension_type", "id", "type"));
    model->select();

    // New relation model for combobox
    QSqlTableModel *relModel = model->relationModel(typeIndex); // Relation index
    ui->extTypeBox->setModel(relModel);
    ui->extTypeBox->setModelColumn(relModel->fieldIndex("type"));

    // View data with mapper
    mapper->addMapping(ui->dataLibLine, 1);
    mapper->addMapping(ui->dataFuncLine, 2);
    mapper->addMapping(ui->extLibLine, 3);
    mapper->addMapping(ui->extFuncLine, 4);
    mapper->addMapping(ui->extFreeMemline, 5);
    mapper->addMapping(ui->extTypeBox, typeIndex);    // Relation by index

    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();

    extTypeCModel = new BaseComboModel("type", "extension_type", this, Table, "extension_type");
    ui->extTypeBox->setModel(extTypeCModel);

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateExtFuncForm::submitChanges);

    // All columns cannot be blank
    connect(ui->dataLibLine, &QLineEdit::textChanged, this, [this] {
        ui->submitButton->setEnabled(!ui->dataLibLine->text().isEmpty() && !ui->dataFuncLine->text().isEmpty() &&
        !ui->extLibLine->text().isEmpty() && !ui->extFuncLine->text().isEmpty() && !ui->extFreeMemline->text().isEmpty() &&
        ui->extTypeBox->currentIndex() > 0);
    });
    connect(ui->dataFuncLine, &QLineEdit::textChanged, ui->dataLibLine, &QLineEdit::textChanged);
    connect(ui->extLibLine, &QLineEdit::textChanged, ui->dataLibLine, &QLineEdit::textChanged);
    connect(ui->extFuncLine, &QLineEdit::textChanged, ui->dataLibLine, &QLineEdit::textChanged);
    connect(ui->extFreeMemline, &QLineEdit::textChanged, ui->dataLibLine, &QLineEdit::textChanged);
    connect(ui->extTypeBox, &QComboBox::currentTextChanged, ui->dataLibLine, &QLineEdit::textChanged);
}

CreateExtFuncForm::~CreateExtFuncForm()
{
    delete ui;
}

void CreateExtFuncForm::submitChanges()
{
    // Save changes to database
    mapper->submit();
    model->submitAll();

    int id = -1;
    if (isEdit) {
        id = model->record(mapper->currentIndex()).value("id").toInt();
    }
    extTypeCModel->saveToDB(ui->extTypeBox->itemData(ui->extTypeBox->currentIndex(), Qt::UserRole).toInt(), id);

    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateExtFuncForm::setRowIndex(int rowIndex, int id)
{
    // User chose to edit data from the table
    BaseForm::setRowIndex(rowIndex, id);

    ui->extTypeBox->setCurrentIndex(ui->extTypeBox->findText(extTypeCModel->getTextValue(id)));
}
