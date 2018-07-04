#include "basecombomodel.h"
#include <QSqlQuery>

namespace
{
    enum Columns // Depends with 'query.prepare( QString( "SELECT ... '
    {
        Id,
        Data,
    };
}

BaseComboModel::BaseComboModel( const QString& visualColumn, const QString& queryTail, QObject *parent,
        QString baseTable, QString baseColumn ) :
        QSqlQueryModel( parent ),
        mainTable(baseTable), mainColumn(baseColumn), selectTable(queryTail), selectColumn(visualColumn)
{
    QSqlQuery query;
    query.prepare( QString( "SELECT %1.id, %2 FROM %3" ).arg( queryTail.split( ' ' ).first() ).arg( visualColumn ).arg( queryTail ) );
    // I.e. query.prepare( "SELECT country.id, countryname || ' - ' || countrycode  FROM country" );
    query.exec();
    QSqlQueryModel::setQuery( query );
}

QVariant BaseComboModel::dataFromParent( QModelIndex index, int column ) const
{
    return QSqlQueryModel::data( QSqlQueryModel::index( index.row() - 1 // "- 1" because make first row empty
            , column ) );
}

int BaseComboModel::rowCount(const QModelIndex &parent) const
{
    return QSqlQueryModel::rowCount( parent ) + 1; // Add info about first empty row
}

QVariant BaseComboModel::data(const QModelIndex & item, int role /* = Qt::DisplayRole */) const
{
    QVariant result;

    if( item.row() == 0 ) // Make first row empty
    {
        switch( role )
        {
            case Qt::UserRole:
                result = 0;
                break;
            case Qt::DisplayRole:
                result = "(please select)";
                break;
            default:
                break;
        }
    }
    else
    {
        switch( role )
        {
            case Qt::UserRole:
                result = dataFromParent( item, Id );
                break;
            case Qt::DisplayRole:
                result = dataFromParent( item, Data );
                break;
            default:
                break;
        }
    }

    return result;
}

void BaseComboModel::saveToDB(int index, int id)
{
    QSqlQuery query;
    query.prepare( "UPDATE " + mainTable + " SET " + mainColumn + " = ? WHERE id = ?" );
    query.addBindValue(index);
    if (id == -1) {
        query.addBindValue(query.lastInsertId().toInt());
    }
    else {
        query.addBindValue(id);
    }
    query.exec();
}

int BaseComboModel::getIndex(int id)
{
    if (id == -1) {
        return 0;
    }

    QSqlQuery query;
    QString str = QString("SELECT " + mainColumn + " FROM " + mainTable + " WHERE id = %1").arg(id);
    query.exec(str);
    while (query.next()) {
        return query.value(0).toInt();
    }
}
