#include "tablemodel.h"

#include <QTime>
#include <QColor>

TableModel::TableModel(QObject *parent) : QSqlRelationalTableModel(parent)
{

}

QVariant TableModel::data(const QModelIndex &idx, int role) const
{
    // Change color for row - light grey
    if (role == Qt::BackgroundColorRole) {
        if(QSqlTableModel::data(this->index(idx.row(), 8)).toTime() == QTime(0, 0, 0)) {
            return QColor(QColor(225, 225, 225));
        }
    }
    else if (role == Qt::DisplayRole) {
        return QSqlTableModel::data(idx);
    }

    return QVariant();
}
