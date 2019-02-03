#ifndef NotEditableDelegate_H
#define NotEditableDelegate_H

#include <QStyledItemDelegate>

class NotEditableDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    QWidget* createEditor(QWidget*, const QStyleOptionViewItem &, const QModelIndex &) const { return 0; }
protected:
    virtual void drawFocus(QPainter *, const QStyleOptionViewItem &, const QRect &) const { return; }
};

#endif // NotEditableDelegate_H