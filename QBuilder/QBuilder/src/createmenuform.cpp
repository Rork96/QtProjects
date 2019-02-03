#include "createmenuform.h"
#include "ui_createmenuform.h"

#include <QMessageBox>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>

CreateMenuForm::CreateMenuForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateMenuForm)
{
    ui->setupUi(this);

    ui->submitButton->setEnabled(false); // Menu name

    /* * * Images for menu iconBox and database * * */

    initData(Table);

    // Set relation between tables
    int groupIndex = model->fieldIndex("group_name");
    model->setRelation(groupIndex, QSqlRelation("groups", "id", "name"));

    model->select();

    // New relation model for fTypeBox
    QSqlTableModel *relModel = model->relationModel(groupIndex); // Relation index
    ui->groupNameBox->setModel(relModel);
    ui->groupNameBox->setModelColumn(relModel->fieldIndex("name"));

    // View data with mapper
    mapper->addMapping(ui->groupNameBox, groupIndex);   // Relation by index
    mapper->addMapping(ui->menuTextLine, 2);
    // 3 - icons
    mapper->addMapping(ui->descriptionEdit, 4);
    mapper->addMapping(ui->weightSpinBox, 5);

    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateMenuForm::submitChanges);

    // Menu name, description
    connect(ui->menuTextLine, &QLineEdit::textChanged, this, [this] {
        ui->submitButton->setEnabled(!ui->menuTextLine->text().isEmpty());
    });
}

CreateMenuForm::~CreateMenuForm()
{
    delete ui;
}
