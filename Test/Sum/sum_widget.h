#ifndef SUM_WIDGET_H
#define SUM_WIDGET_H

#include <QWidget>

#include "summery.h"

namespace Ui {
class sum_widget;
}

class sum_widget : public QWidget
{
    Q_OBJECT

public:
    explicit sum_widget(QWidget *parent = 0);
    ~sum_widget();

private slots:
    void on_callBtn_clicked();

    void on_exitBtn_clicked();

private:
    Ui::sum_widget *ui;
};

#endif // SUM_WIDGET_H
