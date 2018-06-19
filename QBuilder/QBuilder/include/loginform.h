#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>

#include "database.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

private:
    Ui::LoginForm *ui;

    DataBase *db;

    void checkLogin();

signals:
    void isLogin();
};

#endif // LOGINFORM_H
