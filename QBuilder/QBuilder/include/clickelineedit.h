#ifndef CLICKELINEEDIT_H
#define CLICKELINEEDIT_H

#include <QWidget>
#include <QLineEdit>

class ClickeLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit ClickeLineEdit(QWidget *parent = Q_NULLPTR);
    explicit ClickeLineEdit(const QString &text, QWidget *parent = Q_NULLPTR);
    ~ClickeLineEdit();

protected:
    void mousePressEvent(QMouseEvent *event) override;

public Q_SLOTS:
    void setText(const QString &text);
};

#endif // CLICKELINEEDIT_H
