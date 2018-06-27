#include "createdocfamilyform.h"
#include "ui_createdocfamilyform.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlField>

CreateDocFamilyForm::CreateDocFamilyForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateDocFamilyForm)
{
    ui->setupUi(this);

    // region document_family table
    model = new QSqlTableModel(this);
    model->setTable(TABLE);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0, Qt::AscendingOrder);
    model->select();

    // View data in lineEdit with mapper
    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->addMapping(ui->familyNameLine, 1);
    mapper->addMapping(ui->familyDescrText, 2);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();
    // endregion document_family table

    // region categories table
    categoryModel = new QSqlRelationalTableModel(this);
    categoryModel->setTable(CATEGORY);

    categoryModel->setSort(0, Qt::AscendingOrder);
    categoryModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    categoryModel->select();

    // Filter data - doesn't work
    //categoryModel->setFilter("family=" + model->record().value("id").toInt());
    int familyIndex = categoryModel->fieldIndex("family");
    categoryModel->setRelation(familyIndex, QSqlRelation(TABLE, "id", "id"));
    categoryModel->select();

    // Select data from table (selection by family field=id from TABLE table)
    //categoryModel->setQuery("SELECT * FROM " CATEGORY);// "WHERE family = " + model->record().value("id").toInt());
    ui->categotyTableView->setModel(categoryModel);

    // Hide columns
    ui->categotyTableView->setColumnHidden(0, true);
    ui->categotyTableView->setColumnHidden(1, true);

    // Columns size
    for (int i = 0; i < ui->categotyTableView->horizontalHeader()->count(); i++) {
        ui->categotyTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    ui->categotyTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->categotyTableView->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(categoryModel, &QSqlTableModel::dataChanged, this, [this] {
        categoryModel->submitAll();
        categoryModel->select();
        QSqlQuery query;
        query.prepare( "UPDATE " CATEGORY " SET family = ? WHERE id = ?");
        query.addBindValue(query.lastInsertId().toInt());   // id - doesn't work
        query.exec();
        ui->categotyTableView->update();
    });
    // endregion categories table

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateDocFamilyForm::submitChanges);

    connect(ui->addCategoryButton, &QToolButton::clicked, this, &CreateDocFamilyForm::addCategory);
    connect(ui->delCategoryButton, &QToolButton::clicked, this, &CreateDocFamilyForm::delCategory);
}

CreateDocFamilyForm::~CreateDocFamilyForm()
{
    delete ui;
}

void CreateDocFamilyForm::submitChanges()
{
    // Save changes to database

    mapper->submit();
    model->submitAll();

    model->select();
    mapper->toLast();

    categoryModel->submitAll();
    categoryModel->select();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateDocFamilyForm::addCategory()
{
    // Add new category
    categoryModel->insertRow(categoryModel->rowCount(QModelIndex()));
}

void CreateDocFamilyForm::delCategory()
{
    // Delete category
    int row = ui->categotyTableView->selectionModel()->selectedRows().at(0).row();
    categoryModel->removeRow(row);
    categoryModel->submitAll();
    categoryModel->select();
    ui->categotyTableView->selectRow(row);
}

void CreateDocFamilyForm::setRowIndex(int rowIndex)
{
    // User chose to edit data from the table
    mapper->setCurrentIndex(rowIndex);
}

/*
void CreateDocFamilyForm::addCategory()
{
    // Add new category

    catL.append(new QLineEdit(ui->categoryLine));
    descrL.append(new QLineEdit(ui->descriptionLine));
    kp_1_L.append(new QLineEdit(ui->kp_1_Line));
    kp_2_L.append(new QLineEdit(ui->kp_2_Line));
    kp_3_L.append(new QLineEdit(ui->kp_3_Line));
    kp_4_L.append(new QLineEdit(ui->kp_4_Line));
    kp_5_L.append(new QLineEdit(ui->kp_5_Line));
    searchL.append(new QLineEdit(ui->searchTextLine));
    delBtn.append(new QToolButton());

    delBtn.last()->setVisible(true);
    delBtn.last()->setIcon(QIcon(":/res/clear.png"));

    connect(delBtn.last(), &QToolButton::clicked, this, &CreateDocFamilyForm::delCategory);

    ui->verticalLayout->addWidget(catL.last());
    ui->verticalLayout_2->addWidget(descrL.last());
    ui->verticalLayout_3->addWidget(kp_1_L.last());
    ui->verticalLayout_4->addWidget(kp_2_L.last());
    ui->verticalLayout_5->addWidget(kp_3_L.last());
    ui->verticalLayout_6->addWidget(kp_4_L.last());
    ui->verticalLayout_7->addWidget(kp_5_L.last());
    ui->verticalLayout_8->addWidget(searchL.last());
    ui->verticalLayout_9->addWidget(delBtn.last());
}

void CreateDocFamilyForm::delCategory()
{
    // Delete category

    int number = delBtn.indexOf((QToolButton *)sender());

    catL.at(number)->deleteLater();         catL.remove(number);
    descrL.at(number)->deleteLater();       descrL.remove(number);
    kp_1_L.at(number)->deleteLater();       kp_1_L.remove(number);
    kp_2_L.at(number)->deleteLater();       kp_2_L.remove(number);
    kp_3_L.at(number)->deleteLater();       kp_3_L.remove(number);
    kp_4_L.at(number)->deleteLater();       kp_4_L.remove(number);
    kp_5_L.at(number)->deleteLater();       kp_5_L.remove(number);
    searchL.at(number)->deleteLater();      searchL.remove(number);
    delBtn.at(number)->deleteLater();       delBtn.remove(number);
}
*/