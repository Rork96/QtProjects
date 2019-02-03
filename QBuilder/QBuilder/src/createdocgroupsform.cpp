#include "createdocgroupsform.h"
#include "ui_createdocgroupsform.h"

#include <QMessageBox>
#include <QSqlRelationalDelegate>
#include <QSqlQuery>

CreateDocGroupsForm::CreateDocGroupsForm(QWidget *parent) :
    BaseForm(parent),
    ui(new Ui::CreateDocGroupsForm)
{
    ui->setupUi(this);

    ui->submitButton->setEnabled(false); // Group name

    initData(Table);

    // Set relation between tables
    int docFamilyIndex = model->fieldIndex("doc_family");
    model->setRelation(docFamilyIndex, QSqlRelation("document_family", "id", "family_name"));

    model->select();

    // New relation model for groupNameBox
    QSqlTableModel *relModel = model->relationModel(docFamilyIndex); // Relation index
    ui->docFamilyBox->setModel(relModel);
    ui->docFamilyBox->setModelColumn(relModel->fieldIndex("family_name"));

    // View data with mapper
    // First not displayed
    mapper->addMapping(ui->groupNameline, 1);
    mapper->addMapping(ui->groupDescrEdit, 2);
    mapper->addMapping(ui->docFamilyBox, docFamilyIndex);

    model->insertRow(model->rowCount(QModelIndex()));
    mapper->toLast();

    connect(ui->backButton, &QToolButton::clicked, this, [this] {
       emit sygnalBack();
    });

    connect(ui->submitButton, &QToolButton::clicked, this, &CreateDocGroupsForm::submitChanges);

    // Group name
    connect(ui->groupNameline, &QLineEdit::textChanged, this, [this] {
        ui->submitButton->setEnabled(!ui->groupNameline->text().isEmpty());
    });
}

CreateDocGroupsForm::~CreateDocGroupsForm()
{
    delete ui;
}

void CreateDocGroupsForm::submitChanges()
{
    // Save changes to database

    QSqlQuery query;
    QString str = QString("SELECT EXISTS (SELECT " + Record + " FROM" + Table +
            " WHERE '" + Record + "' = '%1' AND id != %2 )").arg(ui->groupNameline->text()).
            arg(model->data(model->index(mapper->currentIndex(), 0), Qt::DisplayRole).toInt());

    query.exec(str);
    query.next();

    // If exists
    if (query.value(0) != 0 && !edit) {
        QMessageBox::information(this, trUtf8("Error"), trUtf8("Group name is already exists"));
        return;
    }
    else {
        // Insert new data
        mapper->submit();
        model->submitAll();

        // Write access type
        int value;
        if (ui->fullAccessButton->isChecked()) value = 1;
        else if (ui->readOnlyButton->isChecked()) value = 2;
        else value = 3;

        query.prepare("UPDATE " + Table + " SET access = ?");
        query.addBindValue(value);
        query.exec();
    }
    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void CreateDocGroupsForm::setRowIndex(int rowIndex, int id)
{
    // User chose to edit data from the table
    mapper->setCurrentIndex(rowIndex);

    if (id != -1) edit = true;  // New record

    // Connect radioButtons
    QSqlQuery query;
    query.prepare( "SELECT access FROM " + Table + " WHERE " + Record + " = '" + ui->groupNameline->text() + "'" );
    query.exec();

    while (query.next()) {
        int result = query.value(0).toInt();
        switch (result) {
        case 1:
            ui->fullAccessButton->setChecked(true);
            break;
        case 2:
            ui->readOnlyButton->setChecked(true);
            break;
        default:
            ui->accessDeniedButton->setChecked(true);
            break;
        }
    }
}

void CreateDocGroupsForm::on_docFamilyBox_currentIndexChanged(const QString &arg1)
{
    // Add items to litsView
    QSqlQuery query;
    query.exec( "SELECT cat_name FROM categories WHERE family = (SELECT id FROM document_family WHERE family_name = '" + arg1 + "')" );

    QSqlQueryModel *catmodel = new QSqlQueryModel(this);
    catmodel->setQuery(query);

    ui->docCategoryListView->setModel(catmodel);
}
