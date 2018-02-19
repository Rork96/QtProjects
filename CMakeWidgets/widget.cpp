#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    // Hide
    ui->lblRes->setVisible(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_BtnExit_clicked()
{
    // Exit
    close();
}

void Widget::on_BtnCalck_clicked()
{
    // Number of symbols
    QString str = ui->textEdt->toPlainText();
    // Delete symbols \n, \s, \r, \t
    str.replace(QRegExp("\\s"), "");
    double strLength = str.length();
    ui->lblRes->setText( "Количество символов в строке: " + QString::number(strLength) );
    // Show
    ui->lblRes->setVisible(true);
}
