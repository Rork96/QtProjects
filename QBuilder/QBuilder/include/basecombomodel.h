#ifndef BASECOMBOMODEL_H
#define BASECOMBOMODEL_H

#include <QSqlQueryModel>

class BaseComboModel : public QSqlQueryModel
{
Q_OBJECT

    QVariant dataFromParent(QModelIndex index, int column) const;

public:
    explicit BaseComboModel( const QString& visualColumn, const QString& queryTail, QObject *parent,
                             QString baseTable, QString baseColumn );
    virtual QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;
    virtual int rowCount(const QModelIndex &parent) const;
    void saveToDB(int index, int id);
    int getIndex(int id);

private:
    QString mainTable;
    QString mainColumn;
    QString selectTable;
    QString selectColumn;
};

#endif // BASECOMBOMODEL_H
