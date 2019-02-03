#include "BaseForm.h"

BaseForm::BaseForm(QWidget *parent) : QWidget(parent)
{

}

void BaseForm::initData(const QString &table)
{
    // Init model and mapper
    model = new QSqlRelationalTableModel(this);
    model->setTable(table);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0, Qt::AscendingOrder);
    model->select();

    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
}

void BaseForm::submitChanges()
{
    // Save changes to database

    mapper->submit();
    model->submitAll();

    model->select();
    mapper->toLast();

    // Send sygnal
    emit sygnalSubmit();
}

void BaseForm::setRowIndex(int rowIndex, int id)
{
    // User chose to edit data from the table
    mapper->setCurrentIndex(rowIndex);
    currentId = id;
    if (id > 0) isEdit = true;
}
