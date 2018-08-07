#ifndef CommandPrompt_H
#define CommandPrompt_H

#include <QMainWindow>
#include <QtCore>
#include "PlaineEdit.h"

namespace Ui
{
class CommandPrompt;
}

class CommandPrompt: public QMainWindow
{
    Q_OBJECT

public:
    explicit CommandPrompt(QWidget *parent = 0);
    ~CommandPrompt();

public slots:
    void setStdout();
    void command();

private:
    Ui::CommandPrompt *ui;
    PlaineEdit *m_edit;
    QProcess *m_process;
};

#endif //CommandPrompt_H
