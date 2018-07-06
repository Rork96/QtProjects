#ifndef BASECOMBOMODEL_H
#define BASECOMBOMODEL_H

#include <QSqlQueryModel>

class BaseComboModel : public QSqlQueryModel
{
Q_OBJECT

    QVariant dataFromParent(QModelIndex index, int column) const;

public:
    explicit BaseComboModel( const QString &visualColumn, const QString &queryTail, QObject *parent,
                             const QString &baseTable, const QString &baseColumn, const QString &selTable );
    virtual QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;
    virtual int rowCount(const QModelIndex &parent) const;
    void saveToDB(int index, int id);
    int getIndex(int id);
    int getId(const QString &text);

private:
    QString mainTable;
    QString mainColumn;
    QString selectionTable;
    QString selectionColumn;
};

#endif // BASECOMBOMODEL_H
