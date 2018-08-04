#ifndef TableModel_H
#define TableModel_H

#include <QObject>
#include <QSqlRelationalTableModel>

namespace Ui
{
class TableModel;
}

class TableModel: public QSqlRelationalTableModel
{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent = 0);
    QVariant data(const QModelIndex &idx, int role) const;
};

#endif // TableModel_H
