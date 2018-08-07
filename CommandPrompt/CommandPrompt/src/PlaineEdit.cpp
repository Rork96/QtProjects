#include "PlaineEdit.h"
#include <QTextBlock>
#include <CommandPrompt/include/PlaineEdit.h>


PlaineEdit::PlaineEdit(QWidget *parent) :
    QPlainTextEdit(parent)
{
    setStyleSheet("QPlainTextEdit { color: rgb(5, 185, 0); background-color: black; padding: 4px; "
                  "border: 1px solid rgb(63, 127, 191); border-radius: 5px; border-style: outset; "
                  "font: 9pt \"MS Shell Dlg 2\"; font-weight: bold; }");
}

void PlaineEdit::keyPressEvent(QKeyEvent *e)
{
    // Enter pressed
    if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {
        emit returnPressed();
    }
    QPlainTextEdit::keyPressEvent(e);
}

QString PlaineEdit::getLine() const
{
    // Return last line
    return textCursor().block().text().remove(placeholderText());
}

void PlaineEdit::setPlaceholderText(const QString &placeholderText)
{
    setPlainText(placeholderText);
    QPlainTextEdit::setPlaceholderText(placeholderText);
}

void PlaineEdit::setPlainText(const QString &text)
{
    QPlainTextEdit::setPlainText(text + placeholderText());
}
