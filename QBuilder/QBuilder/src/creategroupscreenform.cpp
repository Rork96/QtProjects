#include "creategroupscreenform.h"
#include "ui_creategroupscreenform.h"

#include <QMessageBox>
#include <QSqlRelationalDelegate>

CreateGroupScreenForm::CreateGroupScreenForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateGroupScreenForm)
{
    ui->setupUi(this);

    model = new QSqlRelationalTableModel(this);
    model->setTable(TABLE);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0, Qt::AscendingOrder);

    // Set relation between tables
    int groupIndex = model->fieldIndex("Group name");
    model->setRelation(groupIndex, QSqlRelation("groups", "id", "name"));
    int menuIndex = model->fieldIndex("menu_name");
    model->setRelation(menuIndex, QSqlRelation("menus", "id", "text"));

    model->select();

    // New relation model for groupNameBox
    QSqlTableModel *relModel = model->relationModel(groupIndex); // Relation index
    ui->groupNameBox->setModel(relModel);
    ui->groupNameBox->setModelColumn(relModel->fieldIndex("name"));

    // New relation model for menuNameBox
    QSqlTableModel *rModel = model->relationModel(menuIndex); // Relation index
    ui->menuNameBox->setModel(rModel);
    ui->menuNameBox->setModelColumn(rModel->fieldIndex("text"));

    // Mapper
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    // View data with mapper
    mapper->addMapping(ui->addCheckBox, 1);
    mapper->addMapping(ui->deleteCheckBox, 2);
    mapper->addMapping(ui->editCheckBox, 3);
    mapper->addMapping(ui->copyCheckBox, 4);
    mapper->addMapping(ui->inquiryCheckBox, 5);
    mapper->addMapping(ui->executeCheckBox, 6);
    mapper->addMapping(ui->showAddBox, 7);
    mapper->addMapping(ui->showDelBox, 8);
    mapper->addMapping(ui->showEditBox, 9);
    mapper->addMapping(ui->showCopyBox, 10);
    mapper->addMapping(ui->showInquireBox, 11);
    mapper->addMapping(ui->showExecuteBox, 12);
    mapper->addMapping(ui->groupNameBox, groupIndex);   // Relation by index
    mapper->addMapping(ui->menuNameBox, menuIndex);     // Relation by index
    mapper->addMapping(ui->screenTextLine, 15);
    mapper->addMapping(ui->weightLine, 16);

    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateGroupScreenForm::submitChanges);
}

CreateGroupScreenForm::~CreateGroupScreenForm()
{
    delete ui;
}

void CreateGroupScreenForm::submitChanges()
{
    // Save changes to database

    model->select();
    mapper->toLast();

    mapper->submit();
    model->submitAll();

    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateGroupScreenForm::setRowIndex(int rowIndex)
{
    // User chose to edit data from the table
    mapper->setCurrentIndex(rowIndex);
}
