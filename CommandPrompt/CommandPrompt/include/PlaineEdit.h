#ifndef PlaneEdit_H
#define PlaneEdit_H

#include <QPlainTextEdit>

namespace Ui {
class PlaineEdit;
}

class PlaineEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit PlaineEdit(QWidget *parent = Q_NULLPTR);
    void keyPressEvent(QKeyEvent *e);                   // Enter pressed
    QString getLine() const;                            // Return last line
    void setPlaceholderText(const QString &placeholderText);
    void setPlainText(const QString &text);

private:
    QString placeHolderStr;

signals:
    void returnPressed();                               // Enter pressed
};

#endif //PlaneEdit_H
