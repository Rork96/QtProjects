#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();   // Zip file - Works

    void on_pushButton_2_clicked(); // Unzip file - Works

    void on_pushButton_5_clicked(); // Zip files - Works

    void on_pushButton_4_clicked(); // Unzip files - Works

    void on_pushButton_6_clicked(); // Zip folder - Works

    void on_pushButton_3_clicked(); // Unzip folder - Works

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
