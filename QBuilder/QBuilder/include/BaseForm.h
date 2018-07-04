#ifndef BASEFORM_H
#define BASEFORM_H

#include <QWidget>
#include <QDataWidgetMapper>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>

class BaseForm : public QWidget
{
Q_OBJECT

public:
    explicit BaseForm(QWidget *parent = nullptr);

    virtual void setRowIndex(int rowIndex, int id);    // User chose to edit data from the table

    void initData(const QString &table);

    virtual void submitChanges();                   // Submit changes in database

    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;
    int currentId = -1;
    bool isEdit = false;

signals:
    void sygnalBack();                      // Skip changes
    void sygnalSubmit();                    // Save changes
};

#endif // BASEFORM_H
