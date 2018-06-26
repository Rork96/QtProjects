#include "createmenuform.h"
#include "ui_createmenuform.h"

#include <QMessageBox>
#include <QSqlRelationalDelegate>

CreateMenuForm::CreateMenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateMenuForm)
{
    ui->setupUi(this);

    /*
     *
     *
     * Save new data but doesn't edit existing
     *
     *
     *
     */

    model = new QSqlRelationalTableModel(this);
    model->setTable(TABLE);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0, Qt::AscendingOrder);

    // Set relation between tables
    int groupTypeIndex = model->fieldIndex("Group name");
    model->setRelation(groupTypeIndex, QSqlRelation("groups", "id", "name"));
    int iconTypeIndex = model->fieldIndex("Menu icon");
    model->setRelation(iconTypeIndex, QSqlRelation("ico", "id", "icon"));

    model->select();

    // New relation model for fTypeBox
    QSqlTableModel *relModel = model->relationModel(groupTypeIndex); // Relation index
    ui->groupNameBox->setModel(relModel);
    ui->groupNameBox->setModelColumn(relModel->fieldIndex("name"));

    // New relation model for dTypeBox
    QSqlTableModel *rModel = model->relationModel(iconTypeIndex); // Relation index
    ui->menuIconBox->setModel(rModel);
    ui->menuIconBox->setModelColumn(rModel->fieldIndex("icon"));

    // Mapper
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    // View data with mapper
    mapper->addMapping(ui->groupNameBox, groupTypeIndex);   // Relation by index
    mapper->addMapping(ui->menuTextLine, 2);
    mapper->addMapping(ui->menuIconBox, iconTypeIndex);     // Relation by index
    mapper->addMapping(ui->descriptionEdit, 4);
    mapper->addMapping(ui->weightSpinBox, 5);

    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateMenuForm::submitChanges);
}

CreateMenuForm::~CreateMenuForm()
{
    delete ui;
}

void CreateMenuForm::submitChanges()
{
    // Save changes to database

    mapper->submit();
    model->submitAll();

    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateMenuForm::setRowIndex(int rowIndex)
{
    // User chose to edit data from the table
    mapper->setCurrentIndex(rowIndex);
}

