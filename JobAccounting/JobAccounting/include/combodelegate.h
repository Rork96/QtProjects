#ifndef COMBODELEGATE_H
#define COMBODELEGATE_H

#include <QStyledItemDelegate>

class ComboBoxDelegate : public QStyledItemDelegate
{
Q_OBJECT
public:
    ComboBoxDelegate(QObject *parent, const QString &visualColumn, const QString &queryTail);

    QString visualColumn;   // Displayed column from database table
    QString queryTail;      // query - database table name
    // "SELECT id, visualColumn FROM queryTail"
    // queryTail - tableName ( or tableName WHERE .... )

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // COMBODELEGATE_H