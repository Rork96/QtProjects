#include "createdocfamilyform.h"
#include "ui_createdocfamilyform.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlRecord>

CreateDocFamilyForm::CreateDocFamilyForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateDocFamilyForm)
{
    ui->setupUi(this);

    ui->submitButton->setEnabled(false); // Family name

    initData(Table);

    // View data in lineEdit with mapper
    mapper->addMapping(ui->familyNameLine, 1);
    mapper->addMapping(ui->familyDescrText, 2);
    mapper->toLast();

    // region categories table
    categoryModel = new QSqlRelationalTableModel(this);
    categoryModel->setTable(Category);

    categoryModel->setSort(0, Qt::AscendingOrder);
    categoryModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    categoryModel->select();

    ui->categotyTableView->setModel(categoryModel);

    // Hide columns
    ui->categotyTableView->setColumnHidden(0, true);
    ui->categotyTableView->setColumnHidden(1, true);

    QStringList headers;
    headers << trUtf8("id") << trUtf8("") << trUtf8("Category") << trUtf8("Description") << trUtf8("K.P. 1") << trUtf8("K.P. 2")
            << trUtf8("K.P. 3") << trUtf8("K.P. 4") << trUtf8("K.P. 5") << trUtf8("Search text ");

    // Columns size
    for (int i = 0; i < ui->categotyTableView->horizontalHeader()->count(); i++) {
        ui->categotyTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        categoryModel->setHeaderData(i, Qt::Horizontal, headers.at(i));
    }

    ui->categotyTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->categotyTableView->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(categoryModel, &QSqlTableModel::dataChanged, this, [this] {
        categoryModel->submitAll();
        categoryModel->select();
        // Insert currentId into table (for filtering | see "setRowIndex()")
        QSqlQuery query;
        query.prepare( "UPDATE " + Category + " SET family = ? WHERE id = ?" );
        query.addBindValue(currentId);
        query.addBindValue(query.lastInsertId().toInt());
        query.exec();

        categoryModel->select();
        ui->categotyTableView->update();
    });
    // endregion categories table

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
        // Delete current data from database
        if (!isEdit) {
            QSqlQuery query;
            query.prepare("DELETE FROM " + Table + " WHERE id = ?");
            query.addBindValue(currentId);
            query.exec();
            // Delete linked data from CATEGORY
            query.prepare("DELETE FROM " + Category + " WHERE family = ?");
            query.addBindValue(currentId);
            query.exec();
        }

        emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateDocFamilyForm::submitChanges);

    connect(ui->addCategoryButton, &QToolButton::clicked, this, &CreateDocFamilyForm::addCategory);
    connect(ui->delCategoryButton, &QToolButton::clicked, this, &CreateDocFamilyForm::delCategory);

    // Family name
    connect(ui->familyNameLine, &QLineEdit::textChanged, this, [this] {
        ui->submitButton->setEnabled(!ui->familyNameLine->text().isEmpty());
    });
}

CreateDocFamilyForm::~CreateDocFamilyForm()
{
    delete ui;
}

void CreateDocFamilyForm::submitChanges()
{
    // Save changes to database

    QSqlQuery query;
    QString str = QString("SELECT EXISTS (SELECT " + Record + " FROM" + Table +
            " WHERE '" + Record + "' = '%1' AND id != %2 )").arg(ui->familyNameLine->text()).
            arg(model->data(model->index(mapper->currentIndex(), 0), Qt::DisplayRole).toInt());

    query.exec(str);
    query.next();

    // If exists
    if (query.value(0) != 0 && !isEdit) {
        QMessageBox::information(this, trUtf8("Error"), trUtf8("Family name is already exists"));
        return;
    }
    else {
        // Insert new data
        categoryModel->submitAll();
        categoryModel->select();
    }

    BaseForm::submitChanges();
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

void CreateDocFamilyForm::setRowIndex(int rowIndex, int id)
{
    // User chose to edit data from the table
    BaseForm::setRowIndex(rowIndex, id);

    QString filterString;

    if (currentId == -1) {
        // Create new item
        QSqlQuery query;
        query.exec( "INSERT INTO " + Table + " DEFAULT VALUES" );
        mapper->submit();
        model->submitAll();
        mapper->toLast();
        currentId = query.lastInsertId().toInt();
        filterString = QString("%1=%2").arg("family").arg(currentId);
        isEdit = false;
    }
    else {
        isEdit = true;
        filterString = QString("%1=%2").arg("family").arg(currentId);
    }

    // Set filter
    categoryModel->setFilter(filterString);
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