#include "sum_widget.h"
#include "ui_sum_widget.h"

sum_widget::sum_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sum_widget)
{
    ui->setupUi(this);
}

sum_widget::~sum_widget()
{
    delete ui;
}

void sum_widget::on_callBtn_clicked()
{
    // Respond from lib
    Summery clib;
    ui->lineEdit->setText(QString::number(clib.answer()));
}

void sum_widget::on_exitBtn_clicked()
{
    // Exit
    close();
}
