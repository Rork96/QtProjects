#ifndef CommandPrompt_H
#define CommandPrompt_H

#include <QMainWindow>
#include "PlaineEdit.h"

namespace Ui
{
class CommandPrompt;
}

class CommandPrompt: public QMainWindow
{
    Q_OBJECT

public:
    explicit CommandPrompt(QWidget *parent = nullptr);
    ~CommandPrompt();

private:
    Ui::CommandPrompt *ui;
    PlaineEdit *m_edit;
};

#endif //CommandPrompt_H
