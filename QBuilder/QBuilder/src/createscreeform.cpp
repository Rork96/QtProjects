#include "createscreeform.h"
#include "ui_createscreeform.h"

#include <QMessageBox>
#include <QSqlRelationalDelegate>

CreateScreeForm::CreateScreeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateScreeForm)
{
    ui->setupUi(this);

    model = new QSqlRelationalTableModel(this);
    model->setTable(TABLE);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0, Qt::AscendingOrder);

    // Set relation between tables
    int scrIndex = model->fieldIndex("Screen name");
    model->setRelation(scrIndex, QSqlRelation("group_screen", "id", "scr_name"));
    int libIndex = model->fieldIndex("library");
    model->setRelation(libIndex, QSqlRelation("libraries", "id", "lib_name"));

    model->select();

    // New relation model for groupNameBox
    QSqlTableModel *relModel = model->relationModel(scrIndex); // Relation index
    ui->scrNameBox->setModel(relModel);
    ui->scrNameBox->setModelColumn(relModel->fieldIndex("scr_name"));

    // New relation model for menuNameBox
    QSqlTableModel *rModel = model->relationModel(libIndex); // Relation index
    ui->libraryBox->setModel(rModel);
    ui->libraryBox->setModelColumn(rModel->fieldIndex("lib_name"));

    // Mapper
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    // View data with mapper
    // First not displayed
    mapper->addMapping(ui->scrNameBox, scrIndex);
    mapper->addMapping(ui->libraryBox, libIndex);
    mapper->addMapping(ui->tabTextLine, 4);
    mapper->addMapping(ui->descriptionEdit, 5);
    mapper->addMapping(ui->tabWeightSpinBox, 6);
    mapper->addMapping(ui->templateEdit, 7);
    mapper->addMapping(ui->desctopBox, 8);
    mapper->addMapping(ui->mobileBox, 9);
    mapper->addMapping(ui->webBox, 10);

    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateScreeForm::submitChanges);
}

CreateScreeForm::~CreateScreeForm()
{
    delete ui;
}

void CreateScreeForm::submitChanges()
{
    // Save changes to database

    // Add n_name saving dependent of what kind of scr_name user choose
    // n_name (integer) from group_screen table
    // scr_name (text) from group_screen table

    //select 'n_name' from 'group_screen' where 'scr_name'=" + ui->scrNameBox.text()

    mapper->submit();
    model->submitAll();

    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateScreeForm::setRowIndex(int rowIndex)
{
    // User chose to edit data from the table
    mapper->setCurrentIndex(rowIndex);
}
