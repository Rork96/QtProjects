#ifndef PlaneEdit_H
#define PlaneEdit_H

#include <QPlainTextEdit>
#include <QtCore>

namespace Ui {
class PlaineEdit;
}

class PlaineEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit PlaineEdit(QWidget *parent = Q_NULLPTR);
    void keyPressEvent(QKeyEvent *e) override;
    void setPlainText(const QString &text);
    QString getLine() const;                            // Return last line without prompt
    void setWelcomeText(const QString &text);           // Set command prompt text
    const QString &getWelcomeText() const;              // Get command prompt text
    void execCommand();                                 // Execute command
    void viewCommandReturn();                           // View output
    void viewCommandError();                            // View error

private:
    QProcess *m_process;
    QString prompt;                                     // Welcome text
    int currentPos;                                     // Cursor current position
};

#endif //PlaneEdit_H
