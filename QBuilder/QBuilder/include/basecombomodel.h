#ifndef BASECOMBOMODEL_H
#define BASECOMBOMODEL_H

#include <QSqlQueryModel>

class BaseComboModel : public QSqlQueryModel
{
Q_OBJECT

    QVariant dataFromParent(QModelIndex index, int column) const;

public:
    explicit BaseComboModel( const QString &visualColumn, const QString &queryTail, QObject *parent,
                             const QString &baseTable, const QString &baseColumn );
    virtual QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;
    virtual int rowCount(const QModelIndex &parent) const;

    // Save data to databese
    void saveToDB(const int &comboId, const int &tableId);

    // Get text value from database to get correct index in comboBox
    QString getTextValue(const int &tableId);

private:
    QString mainTable;              // main table name
    QString mainColumn;             // column name from main table
    QString selectionTable;         // table from which data loaded to comboBox
    QString selectionColumn;        // column from table from which data loaded to comboBox
};

#endif // BASECOMBOMODEL_H
