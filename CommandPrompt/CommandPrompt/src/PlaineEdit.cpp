#include "PlaineEdit.h"
#include <QTextBlock>

PlaineEdit::PlaineEdit(QWidget *parent) :
    QPlainTextEdit(parent)
{
    m_process = new QProcess(parent);

    setWelcomeText("--> "); // Default

    setStyleSheet("QPlainTextEdit { color: rgb(5, 185, 0); background-color: black; padding: 4px; "
                  "border: 1px solid rgb(63, 127, 191); border-radius: 5px; border-style: outset; "
                  "font: 9pt \"MS Shell Dlg 2\"; font-weight: bold; }");

    // region Connections
    connect(m_process, &QProcess::readyReadStandardOutput, this, &PlaineEdit::viewCommandReturn);
    connect(m_process, &QProcess::readyReadStandardError, this, &PlaineEdit::viewCommandError);
    // endregion Connections
}

void PlaineEdit::keyPressEvent(QKeyEvent *e)
{
    if ((e->key() != Qt::Key_Return || e->key() != Qt::Key_Enter) && textCursor().position() < currentPos) {
        // WelcomeText modification is forbidden
        moveCursor(QTextCursor::End);
        return;
    }

    if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {  // Enter pressed
        if (textCursor().position() <= currentPos) {
            if (getLine() == QString()) {
                setPlainText("\n" + welcomeText);
            }
            return;
        }
        else {
            moveCursor(QTextCursor::End);
            currentPos = textCursor().position();
            execCommand();
        }
    }
    else if (e->key() == Qt::Key_Backspace) {   // Backspace pressed
        if (textCursor().position() <= currentPos) {
            return;
        }
    }
    else if (e->key() == Qt::Key_Delete) {  // Other keys
        if (textCursor().position() < currentPos) {
            return;
        }
    }
    QPlainTextEdit::keyPressEvent(e);
}

QString PlaineEdit::getLine() const
{
    // Return last line without welcomeText
    return textCursor().block().text().remove(welcomeText);
}

void PlaineEdit::setWelcomeText(const QString &text)
{
    welcomeText = text;
    setPlainText(QString());    // Show welcomeText
}

void PlaineEdit::setPlainText(const QString &text)
{
    if (text == ("\n" + welcomeText)) {
        QPlainTextEdit::setPlainText(toPlainText() + text);
    }
    else if (text == QString()) {
        QPlainTextEdit::setPlainText(welcomeText);
    }
    else {
        QPlainTextEdit::setPlainText(toPlainText() + text + "\n" + welcomeText);
    }
    moveCursor(QTextCursor::End);
    currentPos = textCursor().position();   // Save cursor position
}

const QString &PlaineEdit::getWelcomeText() const
{
    return welcomeText;
}

void PlaineEdit::viewCommandReturn()
{
    // View output
    QString outputStr;
    if(QSysInfo::productType() == "windows") {
        QTextCodec *codec = QTextCodec::codecForName("IBM 866");
        outputStr = codec->toUnicode(m_process->readAllStandardOutput());
    }
    else {
        outputStr = m_process->readAllStandardOutput();
    }
    // If empty string has been returned, show welcomeText, else show output
    setPlainText(outputStr == "\f" ? QString() : outputStr);
}

void PlaineEdit::execCommand()
{
    // Execute command
    QString strCommand;
    if(QSysInfo::productType() == "windows") {
        strCommand = "cmd /C ";
    }

    strCommand += getLine();

    // Attempt to open new command window
    if (strCommand == "cmd /C cmd") {
        strCommand = "cmd /C cls";  // Clear
    }
    else {
        strCommand = "";
    }

    // Execute command
    m_process->start(strCommand);
}

void PlaineEdit::viewCommandError()
{
    // View error
    QTextCodec *codec = QTextCodec::codecForName("IBM 866");
    setPlainText(codec->toUnicode(m_process->readAllStandardError()));
}
