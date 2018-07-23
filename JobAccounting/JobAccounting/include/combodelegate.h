#ifndef COMBODELEGATE_H
#define COMBODELEGATE_H

#include <QItemDelegate>
#include <QComboBox>

class QModelIndex;
class QWidget;
class QVariant;

class ComboBoxDelegate : public QItemDelegate
{
Q_OBJECT
public:
    ComboBoxDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor,
                       const QModelIndex &index,
                       const QString column,
                       const QString table,
                       const QString baseTable,
                       const QString baseColum) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // COMBODELEGATE_H