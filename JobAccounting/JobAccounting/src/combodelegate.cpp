#include "combodelegate.h"

#include <QWidget>
#include <QModelIndex>
#include <QAbstractItemModel>

#include "basecombomodel.h"

ComboBoxDelegate::ComboBoxDelegate(QObject *parent)
    :QItemDelegate(parent)
{

}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
    QComboBox* editor = new QComboBox(parent);
    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index,
                                     const QString column,
                                     const QString table,
                                     const QString baseTable,
                                     const QString baseColumn) const
{
    QComboBox *comboBox = dynamic_cast<QComboBox*>(editor);
    //int value = index.model()->data(index, Qt::EditRole).toUInt();
    int value = index.data(Qt::EditRole).toInt();

    BaseComboModel *model = new BaseComboModel(column, table, nullptr, "", "");
    comboBox->setModel(model);
    comboBox->setCurrentIndex(value);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = dynamic_cast<QComboBox*>(editor);
    model->setData(index, comboBox->currentIndex(), Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
