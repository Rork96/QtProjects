#include "clickelineedit.h"

#include <QColorDialog>
#include <QColor>

ClickeLineEdit::ClickeLineEdit(const QString &text, QWidget *parent)
        : QLineEdit(text, parent)
{
}

ClickeLineEdit::ClickeLineEdit(QWidget *parent)
        : QLineEdit(parent)
{
}

ClickeLineEdit::~ClickeLineEdit()
{
}

void ClickeLineEdit::mousePressEvent(QMouseEvent *event)
{
    QColor color = QColorDialog::getColor(text(), this);
    setText(color.name());

    QLineEdit::mousePressEvent(event);
}

void ClickeLineEdit::setText(const QString &text)
{
    if (QColor(text).isValid()) {
        setStyleSheet("ClickeLineEdit { background-color: " + text + ";} ");
    }

    QLineEdit::setText(text);
}
