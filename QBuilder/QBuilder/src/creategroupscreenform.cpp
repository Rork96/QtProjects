#include "creategroupscreenform.h"
#include "ui_creategroupscreenform.h"

#include <QMessageBox>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>
#include "basecombomodel.h"

CreateGroupScreenForm::CreateGroupScreenForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateGroupScreenForm)
{
    ui->setupUi(this);

    initData(Table);

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
    mapper->addMapping(ui->screenTextLine, 15);
    mapper->addMapping(ui->weightLine, 16);

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

    mapper->submit();
    model->submitAll();

    BaseComboModel *groupCModel = new BaseComboModel("name", "groups", this, Table, "group_name");
    BaseComboModel *menuCModel = new BaseComboModel("text", "menus", this, Table, "menu_name");

    int id = -1;
    if (isEdit) {
        id = model->record(mapper->currentIndex()).value("id").toInt();
    }
    groupCModel->saveToDB(ui->groupNameBox->currentIndex(), id);
    menuCModel->saveToDB(ui->menuNameBox->currentIndex(), id);

    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateGroupScreenForm::setRowIndex(int rowIndex, int id)
{
    // User chose to edit data from the table
    BaseForm::setRowIndex(rowIndex, id);

    BaseComboModel *groupCModel = new BaseComboModel("name", "groups", this, Table, "group_name");
    ui->groupNameBox->setModel(groupCModel);
    ui->groupNameBox->setCurrentIndex(groupCModel->getIndex(id));

    BaseComboModel *menuCModel = new BaseComboModel("text", "menus", this, Table, "menu_name");
    ui->menuNameBox->setModel(menuCModel);
    ui->menuNameBox->setCurrentIndex(menuCModel->getIndex(id));
}
