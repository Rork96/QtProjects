#include "infodialog.h"
#include "ui_infodialog.h"

#include <QSqlQuery>

InfoDialog::InfoDialog(QWidget *parent, int id):
    QDialog(parent),
    ui(new Ui::InfoDialog)
{
    ui->setupUi(this);

    QSqlQuery query;
    QString str = QString("SELECT creator, create_date, edit_date FROM main_table WHERE id = %1").arg(id);
    query.exec(str);
    while (query.next()) {
        ui->ownerLabel->setText(query.value(0).toString());
        ui->createTimeLabel->setText(query.value(1).toString());
        ui->editTimeLabel->setText(query.value(2).toString());
    }
}

InfoDialog::~InfoDialog()
{
    delete ui;
}
