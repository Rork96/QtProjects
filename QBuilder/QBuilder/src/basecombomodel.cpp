#include "basecombomodel.h"
#include <QSqlQuery>

#include <QDebug>

namespace
{
    enum Columns // Depends with 'query.prepare( QString( "SELECT ... '
    {
        Id,
        Data,
    };
}

BaseComboModel::BaseComboModel( const QString &visualColumn, const QString &queryTail, QObject *parent,
        const QString &baseTable, const QString &baseColumn ) :
        QSqlQueryModel( parent ),
        mainTable(baseTable), mainColumn(baseColumn)
{
    selectionColumn = visualColumn;
    selectionTable = queryTail.mid(0, queryTail.indexOf(" "));
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

QVariant BaseComboModel::data(const QModelIndex &item, int role /* = Qt::DisplayRole */) const
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

void BaseComboModel::saveToDB(const int &comboId, const int &tableId)
{
    // Save data to databese
    /*
     * comboId - row id from table from which data loaded to comboBox
     * tableid - main table id
     *
     * Save to database:
     * comboBoxbModel->saveToDB(comboBox->itemData(comboBox->currentIndex(), Qt::UserRole).toInt(), id);
     *
     */
    QSqlQuery query;
    query.prepare( "UPDATE " + mainTable + " SET " + mainColumn + " = ? WHERE id = ?" );
    query.addBindValue(comboId);
    if (tableId == -1) {
        query.addBindValue(query.lastInsertId().toInt());
    }
    else {
        query.addBindValue(tableId);
    }
    query.exec();
}

QString BaseComboModel::getTextValue(const int &tableId)
{
    // Get text value from database to get correct index in comboBox
    /*
     * tableid - main table id
     *
     * Index in comboBox:
     * comboBox->setCurrentIndex(comboBox->findText(comboBoxModel->getTextValue(tableId)));
     */
    if (tableId == -1) return 0;

    QSqlQuery query;
    QString str = QString("SELECT " + mainColumn + " FROM " +  mainTable + " WHERE id = %1").arg(tableId);
    query.exec(str);
    query.next();

    str = QString("SELECT " + selectionColumn + " FROM " + selectionTable + " WHERE id = %1").arg(query.value(0).toInt());
    query.exec(str);
    query.next();

    return query.value(0).toString();
}
