#ifndef BASEFORM_H
#define BASEFORM_H

#include <QWidget>

class BaseForm : public QWidget
{
Q_OBJECT

public:
    explicit BaseForm(QWidget *parent = nullptr);

    virtual void setRowIndex(int rowIndex, int) = 0;    // User chose to edit data from the table

    virtual void submitChanges() = 0;                   // Submit changes in database

signals:
    void sygnalBack();                      // Skip changes
    void sygnalSubmit();                    // Save changes
};

#endif // BASEFORM_H
