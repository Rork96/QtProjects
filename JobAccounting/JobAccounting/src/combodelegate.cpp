#include "combodelegate.h"

#include <QComboBox>
#include <QSqlQuery>

#include <QDebug>

ComboBoxDelegate::ComboBoxDelegate(QObject *parent, const QString &visualColumn, const QString &queryTail)
    :QStyledItemDelegate(parent)
{
    this->visualColumn = visualColumn;
    this->queryTail = queryTail;
    // "SELECT id, visualColumn FROM queryTail"
    // queryTail - tableName ( or tableName WHERE .... )
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
    auto *editor = new QComboBox(parent);
    QSqlQuery query;
    query.prepare( QString( "SELECT %1.id, %2 FROM %3" ).arg( queryTail.split( ' ' ).first() ).arg( visualColumn ).arg( queryTail ) );
    // I.e. query.prepare( "SELECT country.id, countryname || ' - ' || countrycode  FROM country" );
    query.exec();
    qDebug() << query.lastQuery();

    // query.value(1).toString() - text (data from visualColumn)
    // query.value(0) - userData (id from table)

    while (query.next()) {
        // Write query.value(1).toString() as displayed text
        // and query.value(0) as userData (Qt::UserRole)
        editor->addItem(query.value(1).toString(), query.value(0));
    }
    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto *comboBox = dynamic_cast<QComboBox*>(editor);
    // Get the index of the text in the combobox that matches the current value of the itenm
    QString currentText = index.data(Qt::EditRole).toString();
    int cbIndex = comboBox->findText(currentText);
    // If it is valid, adjust the combobox
    if (cbIndex >= 0)
        comboBox->setCurrentIndex(cbIndex);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (auto *comboBox = dynamic_cast<QComboBox*>(editor)) {
        // Save the id from Qt::UserRole of the combo box as the current value of the item
        QVariant modelData = comboBox->itemData(comboBox->currentIndex(), Qt::UserRole);    // Get id form Qt::UserRole
        model->setData(index, modelData.toString(), Qt::EditRole);
    }
    else
        QStyledItemDelegate::setModelData(editor, model, index);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);   // Set editor size by column size in TableWidget
}
